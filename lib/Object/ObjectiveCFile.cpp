#include <llvm/ADT/StringExtras.h>
#include <llvm/Object/ObjectiveCFile.h>
#include "llvm/Object/ObjectiveCFile.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/LEB128.h"

using namespace llvm;
using namespace object;


void ObjectiveCFile::resolveMethods() {
    for(section_iterator S_it = MachO->section_begin(); S_it != MachO->section_end(); ++S_it){
        StringRef SectionName;
        S_it->getName(SectionName);
        if (SectionName == "__objc_classlist") {
            ObjcClasslistAddress = S_it->getAddress();
            StringRef ObjcClasslistContent;
            S_it->getContents(ObjcClasslistContent);
            ObjcClasslistData = ArrayRef<uint8_t>((uint8_t*)ObjcClasslistContent.data(), ObjcClasslistContent.size());
        } else if (SectionName == "__objc_data") {
            ObjcDataAddress = S_it->getAddress();
            StringRef ObjcDataContent;
            S_it->getContents(ObjcDataContent);
            ObjcDataData = ArrayRef<uint8_t>((uint8_t*)ObjcDataContent.data(), ObjcDataContent.size());
        } else if (SectionName == "__objc_const") {
            ObjcConstAddress = S_it->getAddress();
            StringRef ObjcConstContent;
            S_it->getContents(ObjcConstContent);
            ObjcConstData = ArrayRef<uint8_t>((uint8_t*)ObjcConstContent.data(), ObjcConstContent.size());
        } else if (SectionName == "__objc_classname") {
            ObjcClassnamesAddress = S_it->getAddress();
            StringRef ObjcClassnamesContent;
            S_it->getContents(ObjcClassnamesContent);
            ObjcClassnamesData = ArrayRef<uint8_t>((uint8_t*)ObjcClassnamesContent.data(), ObjcClassnamesContent.size());
        } else if (SectionName == "__objc_methname") {
            ObjcMethodnamesAddress = S_it->getAddress();
            StringRef ObjcMethodnamesContent;
            S_it->getContents(ObjcMethodnamesContent);
            ObjcMethodnamesData = ArrayRef<uint8_t>((uint8_t*)ObjcMethodnamesContent.data(), ObjcMethodnamesContent.size());
        } else if (SectionName == "__objc_catlist") {
            ObjcCatlistAddress = S_it->getAddress();
            StringRef ObjcCatlistContent;
            S_it->getContents(ObjcCatlistContent);
            ObjcCatlistData = ArrayRef<uint8_t>((uint8_t*)ObjcCatlistContent.data(), ObjcCatlistContent.size());
        }
    }

    if (!(ObjcClasslistAddress && ObjcClasslistData.size())) {
        return;
    }

    assert(ObjcClasslistAddress && ObjcClasslistData.size());
    assert(ObjcDataAddress && ObjcDataData.size());
    assert(ObjcConstAddress && ObjcConstData.size());
    assert(ObjcClassnamesAddress && ObjcClassnamesData.size());
    assert(ObjcMethodnamesAddress && ObjcMethodnamesData.size());
    assert(ObjcCatlistAddress && ObjcCatlistData.size());

    for (unsigned ClasslistIdx = 0; ClasslistIdx < ObjcClasslistData.size(); ClasslistIdx += sizeof(uint64_t)) {
        uint64_t ClassRef = *((uint64_t*)ObjcClasslistData.slice(ClasslistIdx).data());

        assert(ObjcDataAddress <= ClassRef && ClassRef <= ObjcDataAddress + ObjcDataData.size());

        ObjcDataStruct_t *ClassData = (ObjcDataStruct_t*)ObjcDataData.slice(ClassRef - ObjcDataAddress).data();


        assert(ObjcConstAddress <= ClassData->Data && ClassData->Data <= ObjcConstAddress + ObjcConstData.size());

        ObjcClassInfoStruct_t *ClassInfo = (ObjcClassInfoStruct_t*)ObjcConstData.slice(ClassData->Data - ObjcConstAddress).data();
        resolveMethods(ClassInfo, false);

        if (ClassData->ISA) {
            ObjcDataStruct_t *ISAData = (ObjcDataStruct_t *) ObjcDataData.slice(ClassData->ISA - ObjcDataAddress).data();
            errs() << "ISA: " << utohexstr(ISAData->ISA) << "\n";

            ObjcClassInfoStruct_t *ISAClassInfo = (ObjcClassInfoStruct_t*)ObjcConstData.slice(ISAData->Data - ObjcConstAddress).data();
            errs() << utohexstr(ISAClassInfo->BaseMethods) << "\n";
            errs() << getClassName(ObjcClassnamesData, ObjcClassnamesAddress, ISAClassInfo->Name) << "\n";
            resolveMethods(ISAClassInfo, true);
        }
    }

    for (unsigned CatlistIdx = 0; CatlistIdx < ObjcCatlistData.size(); CatlistIdx += sizeof(uint64_t)) {
        uint64_t CatRef = *((uint64_t*)ObjcCatlistData.slice(CatlistIdx).data());

        assert(ObjcConstAddress <= CatRef && CatRef <= ObjcConstAddress + ObjcConstData.size());

        ObjcCatInfoStruct_t *catInfo = (ObjcCatInfoStruct_t*)ObjcConstData.slice(CatRef - ObjcConstAddress).data();
        ObjcDataStruct_t *ClassData = nullptr;
        ObjcClassInfoStruct_t *ClassInfo = nullptr;
        if (catInfo->Class) {
            ClassData = (ObjcDataStruct_t *) ObjcDataData.slice(catInfo->Class - ObjcDataAddress).data();
            ClassInfo = (ObjcClassInfoStruct_t*)ObjcConstData.slice(ClassData->Data - ObjcConstAddress).data();
        }
        resolveMethods(catInfo, true, CatRef, ClassInfo);
    }
}


StringRef ObjectiveCFile::getClassName(ArrayRef<uint8_t> &ObjcClassnames, uint64_t ObjcClassNamesAddress,
                                         uint64_t Address) {
    if(!(ObjcClassNamesAddress <= Address && Address <= ObjcClassNamesAddress + ObjcClassnames.size())){
        erro() << "[+] assert failed:\n\tObjcClassNamesAddress: 0x" << utohexstr(ObjcClassnamesAddress) 
            << "\n\tObjcClassNames size: 0x" << utohexstr(ObjcClassnames.size()) << "\n\tAddress: 0x" << utohexstr(Address);
    }
    StringRef s((char*)ObjcClassnames.slice(Address - ObjcClassNamesAddress).data());
    return s;
}

StringRef ObjectiveCFile::getMethodName(ArrayRef<uint8_t> &ObjcMethodnames, uint64_t ObjcMethodnamesAddress,
                                          uint64_t Address) {
    assert(ObjcMethodnamesAddress <= Address && Address <= ObjcMethodnamesAddress + ObjcMethodnames.size());
    StringRef s((char*)ObjcMethodnames.slice(Address - ObjcMethodnamesAddress).data());
    return s;
}

void ObjectiveCFile::resolveMethods(ObjcClassInfoStruct_t *ClassInfo, bool ClassMethods) {
    if (!ClassInfo->BaseMethods){
        return;
    }
    StringRef ClassName = getClassName(ObjcClassnamesData, ObjcClassnamesAddress, ClassInfo->Name);
    if (ClassName == "LastPassModel") {
        assert(true);
    }
    ObjcMethodListHeader_t *MethodlistHeader = (ObjcMethodListHeader_t*)ObjcConstData.slice(ClassInfo->BaseMethods - ObjcConstAddress).data();
    ObjcMethodListEntry_t *MethodlistEntry = (ObjcMethodListEntry_t*)ObjcConstData.slice(ClassInfo->BaseMethods - ObjcConstAddress + sizeof(ObjcMethodListHeader_t)).data();
    for (unsigned MethodIdx = 0; MethodIdx < MethodlistHeader->Count; ++MethodIdx) {
        if (!MethodlistEntry[MethodIdx].Implementation)
            continue;
        StringRef Methodname = getMethodName(ObjcMethodnamesData, ObjcMethodnamesAddress, MethodlistEntry[MethodIdx].Name);
        if (Methodname == "notifyInAppPurchasingEnabledChanged") {
            assert(true);
        }
        std::string N = ((ClassMethods ? "+[" : "-[") + ClassName + " " + Methodname + "]").str();
        errs() << utohexstr(MethodlistEntry[MethodIdx].Implementation) << ": " << N << "\n";
                FunctionNames.insert(std::pair<uint64_t, std::string>(MethodlistEntry[MethodIdx].Implementation, N));
    }
}

void ObjectiveCFile::resolveMethods(ObjcCatInfoStruct_t *CatInfo, bool ClassMethods, uint64_t CatInfoAddress, ObjcClassInfoStruct_t *ClassInfo) {
    StringRef ClassName;
    if (CatInfoAddress == 0x1003a28d0) {
        assert(true);
    }
    if (CatInfo->Class) {
        assert(ClassInfo && ClassInfo->Name);
        ClassName = getClassName(ObjcClassnamesData, ObjcClassnamesAddress, ClassInfo->Name);
    } else {
        //Pointer do function name is not set yet -> binding info
        ClassName = getClassName(CatInfoAddress + 8);
        if (ClassName.startswith("_OBJC_CLASS_$_")) {
            ClassName = ClassName.substr(strlen("_OBJC_CLASS_$_"));
        }
    }

    if (CatInfo->InstaceMethods) {
        ObjcMethodListHeader_t *MethodlistHeader = (ObjcMethodListHeader_t *) ObjcConstData.slice(
                CatInfo->InstaceMethods - ObjcConstAddress).data();
        ObjcMethodListEntry_t *MethodlistEntry = (ObjcMethodListEntry_t *) ObjcConstData.slice(
                CatInfo->InstaceMethods - ObjcConstAddress + sizeof(ObjcMethodListHeader_t)).data();
        for (unsigned MethodIdx = 0; MethodIdx < MethodlistHeader->Count; ++MethodIdx) {
            if (!MethodlistEntry[MethodIdx].Implementation)
                continue;
            StringRef Methodname = getMethodName(ObjcMethodnamesData, ObjcMethodnamesAddress,
                                                 MethodlistEntry[MethodIdx].Name);
            StringRef N = ("-[" + ClassName + " " + Methodname + "]").str();
            errs() << utohexstr(MethodlistEntry[MethodIdx].Implementation) << ": " << N << "\n";
            FunctionNames.insert(std::pair<uint64_t, std::string>(MethodlistEntry[MethodIdx].Implementation, N.str()));
        }
    }

    if (CatInfo->ClassMethods) {
        ObjcMethodListHeader_t *MethodlistHeader = (ObjcMethodListHeader_t *) ObjcConstData.slice(
                CatInfo->ClassMethods - ObjcConstAddress).data();
        ObjcMethodListEntry_t *MethodlistEntry = (ObjcMethodListEntry_t *) ObjcConstData.slice(
                CatInfo->ClassMethods - ObjcConstAddress + sizeof(ObjcMethodListHeader_t)).data();
        for (unsigned MethodIdx = 0; MethodIdx < MethodlistHeader->Count; ++MethodIdx) {
            if (!MethodlistEntry[MethodIdx].Implementation)
                continue;
            StringRef Methodname = getMethodName(ObjcMethodnamesData, ObjcMethodnamesAddress,
                                                 MethodlistEntry[MethodIdx].Name);
            StringRef N = ("+[" + ClassName + " " + Methodname + "]").str();
            errs() << utohexstr(MethodlistEntry[MethodIdx].Implementation) << ": " << N << "\n";
            FunctionNames.insert(std::pair<uint64_t, std::string>(MethodlistEntry[MethodIdx].Implementation, N.str()));
        }
    }
}

StringRef ObjectiveCFile::getClassName(uint64_t Pointer) {
    ArrayRef<uint8_t> BindOpcodes = MachO->getDyldInfoBindOpcodes();

    uint64_t SegmentNo = 0;
    int64_t Offset = 0;
    StringRef SymbolName;

    for (unsigned Idx = 0; Idx < BindOpcodes.size();) {
        if (Idx == 283) {
            assert(true);
        }
        unsigned Opcode = *BindOpcodes.slice(Idx).data();

        if ((Opcode & ~0xF) == MachO::BIND_OPCODE_SET_DYLIB_ORDINAL_IMM) {
            unsigned Imm = Opcode & 0xF;
            Idx++;
        } else if ((Opcode & ~0xF) == MachO::BIND_OPCODE_SET_SYMBOL_TRAILING_FLAGS_IMM) {
            Idx++;
            SymbolName = (const char*)BindOpcodes.slice(Idx).data();
            Idx += SymbolName.size() + 1;
        } else if (Opcode == (MachO::BIND_OPCODE_SET_TYPE_IMM | 0x1)) {
            //Set type pointer
            Idx++;
        } else if ((Opcode & ~0xF) == MachO::BIND_OPCODE_SET_SEGMENT_AND_OFFSET_ULEB) {
            SegmentNo = Opcode & 0xF;
            Idx++;
            unsigned n;
            Offset = decodeULEB128(BindOpcodes.slice(Idx).data(), &n);
            Idx += n;
        } else if (Opcode == MachO::BIND_OPCODE_DO_BIND) {
            MachO::segment_command_64 Segment = getSegment(SegmentNo);
            if (Segment.vmaddr + Offset == Pointer) {
                return SymbolName;
            }
            //FIXME: is this add correct???
            Offset += 8;
            Idx++;
        } else if (Opcode == MachO::BIND_OPCODE_ADD_ADDR_ULEB) {
            Idx++;
            unsigned n;
            Offset += decodeULEB128(BindOpcodes.slice(Idx).data(), &n);
            Idx += n;
        } else if ((Opcode & ~0xF) == MachO::BIND_OPCODE_DO_BIND_ADD_ADDR_IMM_SCALED) {
            unsigned Scaled = (Opcode & 0xF) * 8;
            if (getSegment(SegmentNo).vmaddr + Offset == Pointer) {
                return SymbolName;
            }
//            addClass(SymbolName, getSegment(SegmentNo).vmaddr + Offset);
            //FIXME: again the add of 8
            Offset += Scaled + 8;
            Idx++;
        } else if (Opcode == MachO::BIND_OPCODE_DO_BIND_ULEB_TIMES_SKIPPING_ULEB) {
            //TODO:
            Idx++;
            unsigned n;
            uint64_t Count = decodeULEB128(BindOpcodes.slice(Idx).data(), &n);
            Idx += n;
            n = 0;
            uint64_t Skip = decodeULEB128(BindOpcodes.slice(Idx).data(), &n);
            for (unsigned i = 0; i < Count; ++i) {
//                addClass(SymbolName, getSegment(SegmentNo).vmaddr + Offset);
                if (getSegment(SegmentNo).vmaddr + Offset == Pointer) {
                    return SymbolName;
                }
                Offset += 8 + Skip;
            }
            Idx += n;
        } else if (Opcode == MachO::BIND_OPCODE_DO_BIND_ADD_ADDR_ULEB) {
//            addClass(SymbolName, getSegment(SegmentNo).vmaddr + Offset);
            if (getSegment(SegmentNo).vmaddr + Offset == Pointer) {
                return SymbolName;
            }
            Idx++;
            unsigned n;
            Offset += decodeULEB128(BindOpcodes.slice(Idx).data(), &n) + 8;
            Idx += n;
        } else if (Opcode == MachO::BIND_OPCODE_DONE) {
            break;
        } else if (Opcode == MachO::BIND_OPCODE_SET_DYLIB_ORDINAL_ULEB) {
            Idx++;
            unsigned n;
            uint64_t dylib = decodeULEB128(BindOpcodes.slice(Idx).data(), &n) + 8;
            Idx += n;
        } else if (Opcode == MachO::BIND_OPCODE_SET_ADDEND_SLEB) {
            Idx++;
            unsigned n;
            uint64_t addend = decodeSLEB128(BindOpcodes.slice(Idx).data(), &n);
            Idx += n;
        } else {
            errs() << "0X" << utohexstr(Idx) << "\n";
            errs() << "0x" << utohexstr(Opcode) << "\n";
            assert(false);
        }
    }
    llvm_unreachable("");
}

MachO::segment_command_64 ObjectiveCFile::getSegment(uint64_t SegmentNo) {
    uint64_t Idx = 0;
    for(object::MachOObjectFile::load_command_iterator L_it = MachO->begin_load_commands();
        L_it != MachO->end_load_commands(); ++L_it) {
        if (L_it->C.cmd == MachO::LC_SEGMENT_64) {
            if (Idx == SegmentNo) {
                return MachO->getSegment64LoadCommand(*L_it);
            } else {
                Idx++;
            }
        }
    }
    llvm_unreachable("Cant find segment");
};
