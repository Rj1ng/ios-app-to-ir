#!/bin/bash

echo "IOS App analysis";

binary_file = $1;
#substr = ${binary_file%%.*}
ir_file = ${binary_file}".ir"
opt_ir_file = ${binary_file}"-opt.ir"



