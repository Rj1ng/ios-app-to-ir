# BUGS

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
status: unsolved

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

Swift class resolve failed.
status: solved

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

unkonwn error
status: unsolved

## koubei

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

unkonwn error
status: unsolved