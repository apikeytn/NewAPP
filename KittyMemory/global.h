// global.h
#pragma once

#include "KittyMemory/KittyMemory.hpp"
#include "KittyMemory/MemoryPatch.hpp"
#import "Helper/Mem.h"
#include "Helper/Obfuscate.h"
#ifndef kNO_KEYSTONE
#include "KittyMemory/KittyArm64.hpp"
#endif

namespace Memory {



    // Patch raw bytes at VA
inline bool Patch(uintptr_t va, const std::string& rawBytes) {
    std::vector<uint8_t> byteVec(rawBytes.begin(), rawBytes.end());
    MemoryPatch patch(va, byteVec);
    return patch.isValid() && patch.Modify();
}
    // Patch using Keystone assembly
inline bool PatchAsm(uintptr_t va, const std::string& asmCode) {
#ifndef kNO_KEYSTONE
    MemoryPatch patch = MemoryPatch::createWithAsm(va, MP_ASM_ARM64, asmCode);
    return patch.isValid() && patch.Modify();
#else
    return false;
#endif
}

    // Patch with a single RET instruction (C0 03 5F D6)
    inline bool Ret(uintptr_t va) {
        return Patch(va, "\xC0\x03\x5F\xD6");
    }

    // Patch with MOV X0, #0; RET (return false/nil)
    inline bool RetFalse(uintptr_t va) {
        return Patch(va, "\x00\x00\x80\xD2\xC0\x03\x5F\xD6");
    }

    // Patch with MOV X0, #1; RET (return true/1)
    inline bool RetTrue(uintptr_t va) {
        return Patch(va, "\x20\x00\x80\xD2\xC0\x03\x5F\xD6");
    }

    // Patch encrypted offset with raw bytes
    inline bool PatchEncrypted(const char* encOffset, const std::string& hexBytes) {
        uintptr_t va = getRealOffset(ENCRYPTOFFSET(encOffset));
        return Patch(va, hexBytes);
    }

    // Patch encrypted offset with RET
    inline bool RetEncrypted(const char* encOffset) {
        return PatchEncrypted(encOffset, "\xC0\x03\x5F\xD6");
    }

    // Patch encrypted offset with MOV X0, #0; RET
    inline bool RetFalseEncrypted(const char* encOffset) {
        return PatchEncrypted(encOffset, "\x00\x00\x80\xD2\xC0\x03\x5F\xD6");
    }

    // Patch encrypted offset with MOV X0, #1; RET
    inline bool RetTrueEncrypted(const char* encOffset) {
        return PatchEncrypted(encOffset, "\x20\x00\x80\xD2\xC0\x03\x5F\xD6");
    }

    // Patch encrypted offset with Keystone ASM
    inline bool PatchAsmEncrypted(const char* encOffset, const std::string& asmCode) {
    #ifndef kNO_KEYSTONE
        uintptr_t va = getRealOffset(ENCRYPTOFFSET(encOffset));
        return PatchAsm(va, asmCode);
    #else
        return false;
    #endif
    }
}