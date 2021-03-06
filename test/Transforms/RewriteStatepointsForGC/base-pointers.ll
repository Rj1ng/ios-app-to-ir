; RUN: opt %s -rewrite-statepoints-for-gc -S 2>&1 | FileCheck %s

declare i64 addrspace(1)* @generate_obj()
declare void @use_obj(i64 addrspace(1)*)

; The rewriting needs to make %obj loop variant by inserting a phi 
; of the original value and it's relocation.
define void @def_use_safepoint() gc "statepoint-example" {
; CHECK-LABEL: def_use_safepoint
entry:
  %obj = call i64 addrspace(1)* @generate_obj()
  br label %loop

loop:
; CHECK: phi i64 addrspace(1)* 
; CHECK-DAG: [ %obj.relocated.casted, %loop ]
; CHECK-DAG: [ %obj, %entry ]
  call void @use_obj(i64 addrspace(1)* %obj)
  %safepoint_token = call i32 (i64, i32, void ()*, i32, i32, ...) @llvm.experimental.gc.statepoint.p0f_isVoidf(i64 0, i32 0, void ()* @do_safepoint, i32 0, i32 0, i32 0, i32 5, i32 0, i32 -1, i32 0, i32 0, i32 0)
  br label %loop
}

declare void @do_safepoint()

declare void @parse_point(i64 addrspace(1)*)

define i64 addrspace(1)* @test1(i32 %caller, i8 addrspace(1)* %a, i8 addrspace(1)* %b, i32 %unknown) gc "statepoint-example" {
; CHECK-LABEL: test1
 entry:
  br i1 undef, label %left, label %right

 left:
  %a.cast = bitcast i8 addrspace(1)* %a to i64 addrspace(1)*
; CHECK: left:
; CHECK-NEXT: %a.cast = bitcast i8 addrspace(1)* %a to i64 addrspace(1)*
; CHECK-NEXT: [[CAST_L:%.*]] = bitcast i8 addrspace(1)* %a to i64 addrspace(1)*

; Our safepoint placement pass calls removeUnreachableBlocks, which does a bunch
; of simplifications to branch instructions.  This bug is visible only when
; there are multiple branches into the same block from the same predecessor, and
; the following ceremony is to make that artefact survive a call to 
; removeUnreachableBlocks.  As an example, "br i1 undef, label %merge, label %merge"
; will get simplified to "br label %merge" by removeUnreachableBlocks.
  switch i32 %unknown, label %right [ i32 0, label %merge
                                      i32 1, label %merge
                                      i32 5, label %merge
                                      i32 3, label %right ]

 right:
  %b.cast = bitcast i8 addrspace(1)* %b to i64 addrspace(1)*
  br label %merge
; CHECK: right:
; CHECK-NEXT: %b.cast = bitcast i8 addrspace(1)* %b to i64 addrspace(1)*
; CHECK-NEXT: [[CAST_R:%.*]] = bitcast i8 addrspace(1)* %b to i64 addrspace(1)*

 merge:
; CHECK: merge:
; CHECK-NEXT: %value.base = phi i64 addrspace(1)* [ [[CAST_L]], %left ], [ [[CAST_L]], %left ], [ [[CAST_L]], %left ], [ [[CAST_R]], %right ], !is_base_value !0
  %value = phi i64 addrspace(1)* [ %a.cast, %left], [ %a.cast, %left], [ %a.cast, %left], [ %b.cast, %right]
  %safepoint_token = call i32 (i64, i32, void (i64 addrspace(1)*)*, i32, i32, ...) @llvm.experimental.gc.statepoint.p0f_isVoidp1i64f(i64 0, i32 0, void (i64 addrspace(1)*)* @parse_point, i32 1, i32 0, i64 addrspace(1)* %value, i32 0, i32 5, i32 0, i32 0, i32 0, i32 0, i32 0)

  ret i64 addrspace(1)* %value
}

;; The purpose of this test is to ensure that when two live values share a
;;  base defining value with inherent conflicts, we end up with a *single*
;;  base phi/select per such node.  This is testing an optimization, not a
;;  fundemental correctness criteria
define void @test2(i1 %cnd, i64 addrspace(1)* %base_obj, i64 addrspace(1)* %base_arg2)  gc "statepoint-example" {
; CHECK-LABEL: @test2
entry:
  %obj = getelementptr i64, i64 addrspace(1)* %base_obj, i32 1
  br label %loop

loop:                                             ; preds = %loop, %entry
; CHECK-LABEL: loop
; CHECK:   %current.base = phi i64 addrspace(1)*
; CHECK-DAG: [ %base_obj, %entry ]
; Given the two selects are equivelent, so are their base phis - ideally,
; we'd have commoned these, but that's a missed optimization, not correctness.
; CHECK-DAG: [ [[DISCARD:%.*.base.relocated.casted]], %loop ]
; CHECK-NOT: extra.base
; CHECK: next = select
; CHECK: extra2.base = select
; CHECK: extra2 = select
; CHECK: statepoint
;; Both 'next' and 'extra2' are live across the backedge safepoint...
  %current = phi i64 addrspace(1)* [ %obj, %entry ], [ %next, %loop ]
  %extra = phi i64 addrspace(1)* [ %obj, %entry ], [ %extra2, %loop ]
  %nexta = getelementptr i64, i64 addrspace(1)* %current, i32 1
  %next = select i1 %cnd, i64 addrspace(1)* %nexta, i64 addrspace(1)* %base_arg2
  %extra2 = select i1 %cnd, i64 addrspace(1)* %nexta, i64 addrspace(1)* %base_arg2
  %safepoint_token = call i32 (i64, i32, void ()*, i32, i32, ...) @llvm.experimental.gc.statepoint.p0f_isVoidf(i64 0, i32 0, void ()* @foo, i32 0, i32 0, i32 0, i32 5, i32 0, i32 -1, i32 0, i32 0, i32 0)
  br label %loop
}

define i64 addrspace(1)* @test3(i1 %cnd, i64 addrspace(1)* %obj, 
                                i64 addrspace(1)* %obj2)
    gc "statepoint-example" {
; CHECK-LABEL: @test3
entry:
  br i1 %cnd, label %merge, label %taken
taken:
  br label %merge
merge:
; CHECK-LABEL: merge:
; CHECK-NEXT: %bdv = phi
; CHECK-NEXT: gc.statepoint
  %bdv = phi i64 addrspace(1)* [ %obj, %entry ], [ %obj2, %taken ]
  %safepoint_token = call i32 (i64, i32, void ()*, i32, i32, ...) @llvm.experimental.gc.statepoint.p0f_isVoidf(i64 0, i32 0, void ()* @foo, i32 0, i32 0, i32 0, i32 5, i32 0, i32 -1, i32 0, i32 0, i32 0)
  ret i64 addrspace(1)* %bdv
}


declare void @foo()
declare i32 @llvm.experimental.gc.statepoint.p0f_isVoidf(i64, i32, void ()*, i32, i32, ...)
declare i32 @llvm.experimental.gc.statepoint.p0f_isVoidp1i64f(i64, i32, void (i64 addrspace(1)*)*, i32, i32, ...)
