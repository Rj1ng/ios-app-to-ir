# FIXME

## tzhuaTaiZLMobile

```text
intrinsic not handled
UNREACHABLE executed at /Users/ring/Documents/pwnzen/Project-ios/ios-analysis-dagger/lib/Target/AArch64/DC/AArch64InstrSema.cpp:2687!
0  llvm-dec                 0x000000010de5e51e llvm::sys::PrintStackTrace(llvm::raw_ostream&) + 46
1  llvm-dec                 0x000000010de5fed9 PrintStackTraceSignalHandler(void*) + 25
2  llvm-dec                 0x000000010de5c649 llvm::sys::RunSignalHandlers() + 425
3  llvm-dec                 0x000000010de60202 SignalHandler(int) + 354
4  libsystem_platform.dylib 0x00007fff6f602b3d _sigtramp + 29
5  libsystem_platform.dylib 0x0000000110226bc6 _sigtramp + 2697085094
6  llvm-dec                 0x000000010de5fefb raise + 27
7  llvm-dec                 0x000000010de5ffa2 abort + 18
8  llvm-dec                 0x000000010ddd93d0 LLVMInstallFatalErrorHandler + 0
9  llvm-dec                 0x000000010d2bef59 llvm::AArch64InstrSema::translateTargetIntrinsic(unsigned int) + 121
10 llvm-dec                 0x000000010d408da2 llvm::DCInstrSema::translateOpcode(unsigned int) + 18562
11 llvm-dec                 0x000000010d40447b llvm::DCInstrSema::translateInst(llvm::MCDecodedInst const&, llvm::DCTranslatedInst&) + 603
12 llvm-dec                 0x000000010d4250e2 llvm::DCTranslator::translateFunction(llvm::MCFunction*, std::__1::vector<unsigned long long, std::__1::allocator<unsigned long long> > const&) + 3250
13 llvm-dec                 0x000000010d424367 llvm::DCTranslator::translateAllKnownFunctions() + 487
14 llvm-dec                 0x000000010d15d9e6 main + 8614
15 libdyld.dylib            0x00007fff6f419085 start + 1
Stack dump:
0.	Program arguments: ./llvm-dec /Users/ring/Downloads/Bins/tztHuaTaiZLMobile -o tzhuaTaiZLMobile-ir.txt
1.	DC: Translating Function at address 100C29E8C
2.	DC: Translating Basic Block at address 100C2AFFC
[1]    38450 illegal hardware instruction  ./llvm-dec ~/Downloads/Bins/tztHuaTaiZLMobile -o tzhuaTaiZLMobile-ir.txt
```

aarch64 decode failed
status: solved?

---

```text
BugID: tzhuaTai_100C2C8B4
100C2C8B4                 FRECPE          V2.4S, V1.4S
 <MCInst 675 <MCOperand Reg:106> <MCOperand Reg:105>> at 0x100C2C8B4
[+]switch: 74
intrinsic not handled
UNREACHABLE executed at /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/lib/Target/AArch64/DC/AArch64InstrSema.cpp:2827!
status: unsure

BugID: tzhuaTai_100C2C8B8
100C2C8B8                 FRECPS          V1.4S, V1.4S, V2.4S
 <MCInst 680 <MCOperand Reg:105> <MCOperand Reg:105> <MCOperand Reg:106>> at 0x100C2C8B8
[+]switch: 75
intrinsic not handled
status: unsure

BugID: tzhuaTai_100C392A4
100C392A4                 FMAXP           V0.2S, V0.2S, V2.2S
 <MCInst 575 <MCOperand Reg:40> <MCOperand Reg:40> <MCOperand Reg:42>> at 0x100C392A4
[+]switch: 65
intrinsic not handled
status: unsure

BugID: tzhuaTai_1012FBF28
1012FBF28                 UQSHRN          V0.8B, V3.8H, #8
 <MCInst 2443 <MCOperand Reg:40> <MCOperand Reg:107> <MCOperand Imm:8>> at 0x1012FBF28
[+]switch: 173
intrinsic not handled

BugID: tzhuaTai_1012FC820
1012FC820                 UQRSHRN         V0.8B, V16.8H, #2
 <MCInst 2412 <MCOperand Reg:40> <MCOperand Reg:120> <MCOperand Imm:2>> at 0x1012FC820
[+]switch: 171
intrinsic not handled
```

## vlc

```text
VLCGoogleDriveTableViewController
Assertion failed: (ObjcClassNamesAddress <= Address && Address <= ObjcClassNamesAddress + ObjcClassnames.size()), function getClassName, file /Users/ring/Documents/pwnzen/Project-ios/ios-analysis-dagger/lib/Object/ObjectiveCFile.cpp, line 103.
0  llvm-dec                 0x000000010e3fc51e llvm::sys::PrintStackTrace(llvm::raw_ostream&) + 46
1  llvm-dec                 0x000000010e3fded9 PrintStackTraceSignalHandler(void*) + 25
2  llvm-dec                 0x000000010e3fa649 llvm::sys::RunSignalHandlers() + 425
3  llvm-dec                 0x000000010e3fe202 SignalHandler(int) + 354
4  libsystem_platform.dylib 0x00007fff6f602b3d _sigtramp + 29
5  libdyld.dylib            0x00007fff6f404f4e dyld_stub_binder + 282
6  llvm-dec                 0x000000010e3fdefb raise + 27
7  llvm-dec                 0x000000010e3fdfa2 abort + 18
8  llvm-dec                 0x000000010e3fdf8e __assert_rtn + 126
9  llvm-dec                 0x000000010dec1a7d llvm::ObjectiveCFile::getClassName(llvm::ArrayRef<unsigned char>&, unsigned long long, unsigned long long) + 141
10 llvm-dec                 0x000000010dec1258 llvm::ObjectiveCFile::resolveMethods(llvm::ObjectiveCFile::ObjcClassInfoStruct_t*, bool) + 120
11 llvm-dec                 0x000000010dec0d39 llvm::ObjectiveCFile::resolveMethods() + 3065
12 llvm-dec                 0x000000010d70bbca llvm::ObjectiveCFile::ObjectiveCFile(llvm::object::MachOObjectFile*) + 234
13 llvm-dec                 0x000000010d706a1d llvm::ObjectiveCFile::ObjectiveCFile(llvm::object::MachOObjectFile*) + 29
14 llvm-dec                 0x000000010d972687 llvm::MCObjectDisassembler::MCObjectDisassembler(llvm::object::ObjectFile const&, llvm::MCDisassembler const&, llvm::MCInstrAnalysis const&) + 887
15 llvm-dec                 0x000000010d972a7d llvm::MCObjectDisassembler::MCObjectDisassembler(llvm::object::ObjectFile const&, llvm::MCDisassembler const&, llvm::MCInstrAnalysis const&) + 45
16 llvm-dec                 0x000000010d6faf4a main + 5898
17 libdyld.dylib            0x00007fff6f419085 start + 1
18 libdyld.dylib            0x0000000000000004 start + 2428399488
Stack dump:
0.	Program arguments: ./llvm-dec /Users/ring/Downloads/Bins/vlc-arm64 -o vlc-ir.txt
[1]    39225 illegal hardware instruction  ./llvm-dec ~/Downloads/Bins/vlc-arm64 -o vlc-ir.txt
```

Mach-O Swift class resolve failed.
status: solved

---

```text
Not implemented
UNREACHABLE executed at /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/lib/Target/AArch64/DC/AArch64InstrSema.cpp:2350!
0  llvm-dec                 0x00000001108af42e llvm::sys::PrintStackTrace(llvm::raw_ostream&) + 46
1  llvm-dec                 0x00000001108b12a9 PrintStackTraceSignalHandler(void*) + 25
2  llvm-dec                 0x00000001108ad439 llvm::sys::RunSignalHandlers() + 425
3  llvm-dec                 0x00000001108b1641 SignalHandler(int) + 465
4  libsystem_platform.dylib 0x00007fff6ad66b3d _sigtramp + 29
5  libsystem_platform.dylib 000000000000000000 _sigtramp + 2502530272
6  llvm-dec                 0x00000001108b12cb raise + 27
7  llvm-dec                 0x00000001108b1372 abort + 18
8  llvm-dec                 0x0000000110822400 LLVMInstallFatalErrorHandler + 0
9  llvm-dec                 0x000000010fc07807 llvm::AArch64InstrSema::translateTargetOpcode() + 52903
10 llvm-dec                 0x000000010fd89c9d llvm::DCInstrSema::translateOpcode(unsigned int) + 157
11 llvm-dec                 0x000000010fd89b5b llvm::DCInstrSema::translateInst(llvm::MCDecodedInst const&, llvm::DCTranslatedInst&) + 603
12 llvm-dec                 0x000000010fdada77 llvm::DCTranslator::translateFunction(llvm::MCFunction*, std::__1::vector<unsigned long long, std::__1::allocator<unsigned long long> > const&) + 3767
13 llvm-dec                 0x000000010fdacab6 llvm::DCTranslator::translateAllKnownFunctions() + 566
14 llvm-dec                 0x000000010fa7bcb6 main + 10646
15 libdyld.dylib            0x00007fff6ab7d08d start + 1
16 libdyld.dylib            0x0000000000000002 start + 2504535926
Stack dump:
0.	Program arguments: ./bin/llvm-dec /Users/ring/Downloads/Bins/vlc-arm64
1.	DC: Translating Function at address 1004DCAB4
2.	DC: Translating Basic Block at address 1004DCC10
[1]    17217 illegal hardware instruction  ./bin/llvm-dec ~/Downloads/Bins/vlc-arm64
```

DCInstrSema::translateTargetOpcode failed, not implemented
status: solved

---

```text
TBLv16i8One not handled yet!
Address = 0x00000001004df344    TBL V0.16B, {V1.16B-V2.16B}, V5.16B

"NOT" Not implemented
UNREACHABLE executed at /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/lib/Target/AArch64/DC/AArch64InstrSema.cpp:2461!
1.	DC: Translating Function at address 10063D160
2.	DC: Translating Basic Block at address 10063D26C
```

status: solved

---

```text
Translating instruction:
 <MCInst 1953 <MCOperand Reg:200> <MCOperand Reg:108> <MCOperand Imm:0> <MCOperand Reg:200> <MCOperand Reg:7>> at 0x1006D93E4
[+]isValid: 1	isReg: 0	isImm: 1	isFPImm: 0	isExpr: 0	isInst: 0
Assertion failed: (isReg() && "This is not a register operand!"), function getReg, file /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/include/llvm/MC/MCInst.h, line 64.
0  llvm-dec                 0x000000010aa9535e llvm::sys::PrintStackTrace(llvm::raw_ostream&) + 46
1  llvm-dec                 0x000000010aa971d9 PrintStackTraceSignalHandler(void*) + 25
2  llvm-dec                 0x000000010aa93369 llvm::sys::RunSignalHandlers() + 425
3  llvm-dec                 0x000000010aa97571 SignalHandler(int) + 465
4  libsystem_platform.dylib 0x00007fff61a47b3d _sigtramp + 29
5  libsystem_platform.dylib 000000000000000000 _sigtramp + 2656797920
6  llvm-dec                 0x000000010aa971fb raise + 27
7  llvm-dec                 0x000000010aa972a2 abort + 18
8  llvm-dec                 0x000000010aa9728e __assert_rtn + 126
9  llvm-dec                 0x0000000109d8d5d8 llvm::MCOperand::getReg() const + 104
10 llvm-dec                 0x0000000109dcbbf9 llvm::AArch64InstrSema::translateTargetInst() + 6553
11 llvm-dec                 0x0000000109f6f9b8 llvm::DCInstrSema::translateInst(llvm::MCDecodedInst const&, llvm::DCTranslatedInst&) + 504
12 llvm-dec                 0x0000000109f93988 llvm::DCTranslator::translateFunction(llvm::MCFunction*, std::__1::vector<unsigned long long, std::__1::allocator<unsigned long long> > const&) + 3784
13 llvm-dec                 0x0000000109f929b6 llvm::DCTranslator::translateAllKnownFunctions() + 566
14 llvm-dec                 0x0000000109c60706 main + 10646
15 libdyld.dylib            0x00007fff6185e08d start + 1
Stack dump:
0.	Program arguments: ./bin/llvm-dec /Users/ring/Downloads/Bins/vlc-arm64
1.	DC: Translating Function at address 1006D9368
2.	DC: Translating Basic Block at address 1006D93D0
[1]    43114 illegal hardware instruction  ./bin/llvm-dec ~/Downloads/Bins/vlc-arm64
```

status: solved

---

```text
<MCInst 778 <MCOperand Reg:40> <MCOperand Reg:210>> at 0x1006D938C
[+]Idx: 0
Registers not handled
```

status: solved

---

```text
Translating instruction:
 <MCInst 781 <MCOperand Reg:203> <MCOperand Reg:106> <MCOperand Reg:203> <MCOperand Reg:7>> at 0x1006D9394
[+]Idx: 0
Registers not handled
```

status: solved

---

```text
Translating instruction:
 <MCInst 780 <MCOperand Reg:109> <MCOperand Reg:210>> at 0x1006D9430
[+]Idx: 0
Registers not handled
```

status: solved

---

```text
Translating instruction:
 <MCInst 37 <MCOperand Reg:40> <MCOperand Reg:104> <MCOperand Reg:105>> at 0x1007B25C0
Assertion failed: ((i >= FTy->getNumParams() || FTy->getParamType(i) == Args[i]->getType()) && "Calling a function with a bad signature!"), function init, file /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/lib/IR/Instructions.cpp, line 242.
0  llvm-dec                 0x0000000105d5e39e llvm::sys::PrintStackTrace(llvm::raw_ostream&) + 46
1  llvm-dec                 0x0000000105d60219 PrintStackTraceSignalHandler(void*) + 25
2  llvm-dec                 0x0000000105d5c3a9 llvm::sys::RunSignalHandlers() + 425
3  llvm-dec                 0x0000000105d605b1 SignalHandler(int) + 465
4  libsystem_platform.dylib 0x00007fff6b622b3d _sigtramp + 29
5  libsystem_platform.dylib 0x0000000000000002 _sigtramp + 2493371618
6  llvm-dec                 0x0000000105d6023b raise + 27
7  llvm-dec                 0x0000000105d602e2 abort + 18
8  llvm-dec                 0x0000000105d602ce __assert_rtn + 126
9  llvm-dec                 0x0000000105ac393e llvm::CallInst::init(llvm::FunctionType*, llvm::Value*, llvm::ArrayRef<llvm::Value*>, llvm::Twine const&) + 638
10 llvm-dec                 0x0000000105ae2719 llvm::CallInst::CallInst(llvm::FunctionType*, llvm::Value*, llvm::ArrayRef<llvm::Value*>, llvm::Twine const&, llvm::Instruction*) + 249
11 llvm-dec                 0x0000000105ae260b llvm::CallInst::CallInst(llvm::FunctionType*, llvm::Value*, llvm::ArrayRef<llvm::Value*>, llvm::Twine const&, llvm::Instruction*) + 91
12 llvm-dec                 0x0000000105ae256e llvm::CallInst::Create(llvm::FunctionType*, llvm::Value*, llvm::ArrayRef<llvm::Value*>, llvm::Twine const&, llvm::Instruction*) + 158
13 llvm-dec                 0x000000010524694d llvm::IRBuilder<true, llvm::NoFolder, llvm::IRBuilderDefaultInserter<true> >::CreateCall(llvm::FunctionType*, llvm::Value*, llvm::ArrayRef<llvm::Value*>, llvm::Twine const&) + 125
14 llvm-dec                 0x0000000105235757 llvm::IRBuilder<true, llvm::NoFolder, llvm::IRBuilderDefaultInserter<true> >::CreateCall(llvm::Function*, llvm::ArrayRef<llvm::Value*>, llvm::Twine const&) + 103
15 llvm-dec                 0x00000001050c3a67 llvm::AArch64InstrSema::translateTargetIntrinsic(unsigned int) + 41383
16 llvm-dec                 0x000000010523d6d6 llvm::DCInstrSema::translateOpcode(unsigned int) + 19174
17 llvm-dec                 0x0000000105238b41 llvm::DCInstrSema::translateInst(llvm::MCDecodedInst const&, llvm::DCTranslatedInst&) + 833
18 llvm-dec                 0x000000010525ca78 llvm::DCTranslator::translateFunction(llvm::MCFunction*, std::__1::vector<unsigned long long, std::__1::allocator<unsigned long long> > const&) + 3784
19 llvm-dec                 0x000000010525baa6 llvm::DCTranslator::translateAllKnownFunctions() + 566
20 llvm-dec                 0x0000000104f288d6 main + 10646
21 libdyld.dylib            0x00007fff6b43908d start + 1
22 libdyld.dylib            0x0000000000000002 start + 2495377270
Stack dump:
0.	Program arguments: ./bin/llvm-dec /Users/ring/Downloads/Bins/vlc-arm64
1.	DC: Translating Function at address 1007B2220
2.	DC: Translating Basic Block at address 1007B25A8
[1]    49562 illegal hardware instruction  ./bin/llvm-dec ~/Downloads/Bins/vlc-arm64
```

---

```text
10080181C SSHR
```
status: solved

---

```text
 <MCInst 1693 <MCOperand Reg:111> <MCOperand Reg:110> <MCOperand Reg:108>> at 0x10080160C
intrinsic not handled
UNREACHABLE executed at /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/lib/Target/AArch64/DC/AArch64InstrSema.cpp:2761!
```
status: unsure

---

```text
Translating instruction:
 <MCInst 1828 <MCOperand Reg:42> <MCOperand Reg:42> <MCOperand Imm:15>> at 0x100801948
Not a vector MVT!
UNREACHABLE executed at /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/include/llvm/CodeGen/MachineValueType.h:333!
status: unsure
```

---

```text
 <MCInst 203 <MCOperand Reg:105> <MCOperand Reg:105> <MCOperand Reg:104>> at 0x10089E8F0
Not implemented
staus: unsure
```

---

```text
BugID: vlc_100B1E8C4
 <MCInst 524 <MCOperand Reg:104> <MCOperand Reg:104> <MCOperand Imm:16>> at 0x100B1E8C4
Assertion failed: ((i >= FTy->getNumParams() || FTy->getParamType(i) == Args[i]->getType()) && "Calling a function with a bad signature!"), function init, file /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/lib/IR/Instructions.cpp, line 242.
status: unsure
```

---

```text
BugID: vlc_100C5447C
100C5447C                 SQSHRUN         V0.8B, V1.8H, #5
 <MCInst 1776 <MCOperand Reg:40> <MCOperand Reg:105> <MCOperand Imm:5>> at 0x100C5447C
[+]switch: 129
intrinsic not handled
status: unsure
```

---

```text
BugID: vlc_100C58700
100C58700                 SUBHN           V18.4H, V20.4S, V18.4S
 <MCInst 2124 <MCOperand Reg:58> <MCOperand Reg:124> <MCOperand Reg:122>> at 0x100C58700
[+]switch: 146
intrinsic not handled
```

---

```text
BugID: vlc_100C6C104
100C6C104                 SQSHL           V16.8H, V16.8H, V17.8H
 <MCInst 1755 <MCOperand Reg:120> <MCOperand Reg:120> <MCOperand Reg:121>> at 0x100C6C104
[+]switch: 126
intrinsic not handled
```

---

```text
BugID: vlc_100C6C330
100C6C330                 URSHR           V2.8H, V0.8H, #3
 <MCInst 2486 <MCOperand Reg:106> <MCOperand Reg:104> <MCOperand Imm:3>> at 0x100C6C330
Not implemented
status: unsure

BugID: vlc_0x100C6D7D0
100C6D7D0                 REV16           V1.16B, V0.16B
 <MCInst 1347 <MCOperand Reg:105> <MCOperand Reg:104>> at 0x100C6D7D0
Not implemented
status: unsure

BugID: vlc_100DFAB6C
100DFAB6C                 CMN             W8, W0,SXTH
 <MCInst 52 <MCOperand Reg:6> <MCOperand Reg:176> <MCOperand Reg:168> <MCOperand Imm:40>> at 0x100DFAB6C
Operand not implemented
status: unsure
```

---

```text
so many in /Users/ring/Documents/pwnzen/Project-ios/ios-app-to-ir/tools/llvm-dec/FunctionNamePass.cpp;
line 100;
Can't convert int:
```

## koubei

```text
0: OPC_ExtractField(26, 3): 5
3: OPC_FilterValue(2, 1582): FAIL: continuing at 1589
1589: OPC_FilterValue(3, 28707): FAIL: continuing at 30300
30300: OPC_FilterValue(4, 447): FAIL: continuing at 30751
30751: OPC_FilterValue(5, 477): PASS: continuing at 30755
30755: OPC_ExtractField(29, 3): 1
30758: OPC_FilterValue(0, 4): FAIL: continuing at 30766
30766: OPC_FilterValue(1, 39): PASS: continuing at 30770
30770: OPC_ExtractField(24, 2): 2
30773: OPC_FilterValue(0, 5): FAIL: continuing at 30782
30782: OPC_FilterValue(1, 5): FAIL: continuing at 30791
30791: OPC_FilterValue(2, 5): PASS: continuing at 30795
30795: OPC_Decode: opcode 2202, using decoder 212: PASS
Found branch to 100736D48!
Found terminator!
Looking for block at 1076ECE10
LLVM ERROR: No suitable region for disassembly at 0x1076ECE10

MCObjectDisassembler::disassembleFunctionAt failed, No suitable region for disassembly at 0x1076ECE10

status: unsolved, continue
```

---

```text
BugID: koubei_1003D3150
1003D3150                 UHSUB           V26.16B, V26.16B, V22.16B
 <MCInst 2305 <MCOperand Reg:130> <MCOperand Reg:130> <MCOperand Reg:126>> at 0x1003D3150
[+]switch: 161
intrinsic not handled

* status: unsure
```

---

```text
BugID: koubei_10073EAB0
10073EAB0                 SQDMULL         V25.2D, V26.2S, V26.S[3]
 <MCInst 1642 <MCOperand Reg:129> <MCOperand Reg:66> <MCOperand Reg:130> <MCOperand Imm:3>> at 0x10073EAB0
[+]switch: 119
intrinsic not handled

status: unsure
```

---

```text
BugID: koubei_100745578
100745578                 SABDL2          V5.2D, V16.4S, V31.4S
 <MCInst 1391 <MCOperand Reg:109> <MCOperand Reg:120> <MCOperand Reg:135>> at 0x100745578
Unknown opcode found in semantics: 107

```

## df