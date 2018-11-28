#!/bin/bash

echo "IOS App analysis";
echo "sh run-ayalysis.sh binary ir_filename opt_ir_filename llvm_slicer_path report_filename rules_path";

$binary_file = $1;
#substr = ${binary_file%%.*};
$ir_file = ${binary_file}".ir";
$opt_ir_file = ${binary_file}"-opt.ir";
$llvm_slicer = $2;
$report_file = $3;
$rule_file = $4;

./build/bin/llvm-dec ${binary_file} -O1 -bc -o ${ir_file}
./build/bin/opt -instcombine -sroa -simplifycfg -constprop ${ir_file} -o ${opt_ir_file}
${llvm_slicer} -binary ${binary_file} -o /dev/null -r ${report_file} -rules ${rule_file}

