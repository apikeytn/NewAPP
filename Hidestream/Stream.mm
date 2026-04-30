#import "menuUIKIT/drawview.h"
#import <objc/runtime.h>
#include "menuUIKIT/Vars.h"
#include "framework_output.h"
#include <dlfcn.h>
#import <mach-o/loader.h>
#include <fstream>
#include <mach-o/dyld.h>
#include <mach/mach.h>
#include <unordered_map>
#import <CommonCrypto/CommonDigest.h>
#include <sstream>
#include <vector>
// Global variables

UIView *protectedView = nil;

// Base64 decode helper
static NSString* DecodeBase64String(const char *b64) {
    NSData *data = [[NSData alloc] initWithBase64EncodedString:[NSString stringWithUTF8String:b64]
                                                       options:NSDataBase64DecodingIgnoreUnknownCharacters];
    if (!data) return nil;
    return [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
}

// Core hiding function
BOOL __fn_hideCaptureForView(UIView *v, BOOL hidden) {
    static dispatch_once_t __once;
    static NSString *__maskKey = nil;
    
    dispatch_once(&__once, ^{
        // "disableUpdateMask" in base64
        const char *b64 = "ZGlzYWJsZVVwZGF0ZU1hc2s=";
        __maskKey = DecodeBase64String(b64);
    });
    
    if (!v) {
        NSLog(@"[StreamMode] ⚠️ View is nil");
        return NO;
    }
    
    if (!__maskKey || ![v.layer respondsToSelector:NSSelectorFromString(__maskKey)]) {
        NSLog(@"[StreamMode] ⚠️ Layer doesn't respond to mask key");
        return NO;
    }
    
    NSInteger value = hidden ? ((1 << 1) | (1 << 4)) : 0;
    
    @try {
        [v.layer setValue:@(value) forKey:__maskKey];
        NSLog(@"[StreamMode] ✓ Applied protection to view: %@ (hidden: %d)", NSStringFromClass([v class]), hidden);
        return YES;
    }
    @catch (NSException *exception) {
        NSLog(@"[StreamMode] ⚠️ Exception: %@", exception.reason);
        return NO;
    }
}

// Update protection for a specific view
void UpdateStreamProtectionForView(UIView *view) {
    if (!view) {
        NSLog(@"[StreamMode] ⚠️ UpdateStreamProtection called with nil view");
        return;
    }
    
    protectedView = view;
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    if ([defaults objectForKey:@"StreamMode"]) {
        StreamMode = [defaults boolForKey:@"StreamMode"];
    }
    
    __fn_hideCaptureForView(view, StreamMode);
    NSLog(@"[StreamMode] Updated protection for view: %@, Mode: %@", 
          NSStringFromClass([view class]), StreamMode ? @"ON" : @"OFF");
}


// Set stream mode globally
void SetStreamMode(BOOL value) {
    StreamMode = value;
    
    // Save to UserDefaults
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    [defaults setBool:value forKey:@"StreamMode"];
    [defaults synchronize];
    
    NSLog(@"[StreamMode] SetStreamMode called: %@", value ? @"ENABLED" : @"DISABLED");
    
    // Apply to protected view
    if (protectedView) {
        __fn_hideCaptureForView(protectedView, value);
        NSLog(@"[StreamMode] Applied to protectedView: hidden=%d", value);
    }
}

std::string sha256(const void* data, size_t len) {
    unsigned char hash[CC_SHA256_DIGEST_LENGTH];
    CC_SHA256(data, (CC_LONG)len, hash);
    std::ostringstream ss;
    for (int i = 0; i < CC_SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}

bool read_exact_macho_header(const char* path, std::vector<uint8_t>& out_header) {
    FILE* file = fopen(path, "rb");
    if (!file) return false;

    struct mach_header_64 mh;
    if (fread(&mh, 1, sizeof(mh), file) != sizeof(mh)) {
        fclose(file);
        return false;
    }

    if (mh.magic != MH_MAGIC_64) {
        fclose(file);
        return false;
    }

    const size_t headerBaseSize = sizeof(struct mach_header_64);
    std::vector<uint8_t> result((uint8_t*)&mh, (uint8_t*)&mh + headerBaseSize);

    for (uint32_t i = 0; i < mh.ncmds; ++i) {
        long cmdStart = ftell(file);

        struct load_command lc;
        if (fread(&lc, 1, sizeof(lc), file) != sizeof(lc)) break;

        fseek(file, cmdStart, SEEK_SET);

        std::vector<uint8_t> cmdData(lc.cmdsize);
        if (fread(cmdData.data(), 1, lc.cmdsize, file) != lc.cmdsize) break;

        if (lc.cmd == LC_SEGMENT_64) {
            const segment_command_64* seg = reinterpret_cast<const segment_command_64*>(cmdData.data());

            if (strncmp(seg->segname, "__LINKEDIT", 16) != 0) {
                result.insert(result.end(), cmdData.begin(), cmdData.end());
            }
        }
    }

    fclose(file);
    out_header = std::move(result);
    return true;
}

uint32_t (*p_dyld_image_count)(void);
const char* (*p_dyld_get_image_name)(uint32_t);
char* (*p_strstr)(const char*, const char*);
#define XOR_KEY 0xFA

std::string decode_xor(const uint8_t* data) {
    std::string out;
    for (int i = 0; data[i] != 0x00; ++i)
        out += (char)(data[i] ^ XOR_KEY);
    return out;
}

std::vector<std::string> getDecodedFrameworkNames() {
    std::vector<std::string> names;
    names.reserve(framework_size);

    for (int i = 0; i < framework_size; ++i) {
        std::string s;
        for (int j = 0; framework_names[i][j] != 0x00; ++j) {
            s += (char)(framework_names[i][j] ^ XOR_KEY);
        }
        names.push_back(std::move(s));
    }
    return names;
}

std::vector<std::string> getDecodedFrameworkHashes() {
    std::vector<std::string> hashes;
    hashes.reserve(framework_size);

    for (int i = 0; i < framework_size; ++i) {
        std::string s;
        for (int j = 0; framework_hashes[i][j] != 0x00; ++j) {
            s += (char)(framework_hashes[i][j] ^ XOR_KEY);
        }
        hashes.push_back(std::move(s));
    }
    return hashes;
}

bool validateLoadedFrameworks() {
    //NSString *fileName = @"log_name.txt";
    //NSURL *docURL = [[[NSFileManager defaultManager]
    //                  URLsForDirectory:NSDocumentDirectory
    //                  inDomains:NSUserDomainMask] firstObject];
    //docURL = [docURL URLByAppendingPathComponent:fileName];
    //const char *file_path = [docURL fileSystemRepresentation];

    //FILE *fp = fopen(file_path, "w");
    //if (!fp) {
    //    return false;
    //}
    bool perform_check = true;
    std::string claw = "Frameworks/Monite.dylib";

    const char* main_image = _dyld_get_image_name(0);
    std::string mainPath = main_image ? main_image : "";
    std::string mainDir = mainPath.substr(0, mainPath.rfind('/'));
    
    std::vector<uint8_t> header;
    if (read_exact_macho_header(main_image, header)) {
        std::string realHash = sha256(header.data(), header.size());
        std::string expectedMainHash = decode_xor(main_exec_hash);

        if (realHash != expectedMainHash) {
            //fprintf(fp, "Main exec hash mismatch:\nReal: %s\nExp:  %s\n", realHash.c_str(), expectedMainHash.c_str());
            return !perform_check;
        }
    } else {
        //fprintf(fp, "Failed to read main header\n");
        return !perform_check;
    }

    std::unordered_map<std::string, std::string> expectedFrameworks;
    auto names = getDecodedFrameworkNames();
    auto hashes = getDecodedFrameworkHashes();
    for (int i = 0; i < framework_size; ++i) {
        expectedFrameworks[names[i]] = hashes[i];
    }
    int matched = 0;

    uint32_t imageCount = p_dyld_image_count();
    for (uint32_t i = 1; i < imageCount; ++i) {
        const char* imageName = p_dyld_get_image_name(i);
        if (!imageName) continue;

        std::string fullPath(imageName);
        if (fullPath.find(mainDir) != 0) continue;

        std::string relativePath = fullPath.substr(mainDir.length() + 1);
        if (p_strstr(relativePath.c_str(), claw.c_str())) {
            matched++;
            continue;
        }
        auto it = expectedFrameworks.find(relativePath);
        if (it == expectedFrameworks.end()) {
            //fprintf(fp, "lib: %s not found!\n", relativePath.c_str());
            //fclose(fp);
            return !perform_check;
        }

        std::vector<uint8_t> headerData;
        if (!read_exact_macho_header(fullPath.c_str(), headerData)) {
            //fprintf(fp, "failed read lib: %s", relativePath.c_str());
            continue;
        }

        std::string hash = sha256(headerData.data(), headerData.size());

        if (hash != it->second) {
            //fprintf(fp, "lib %s has wrong hash: %s(expected: %s)", relativePath.c_str(), hash.c_str(), it->second.c_str());
            //fclose(fp);
            return !perform_check;
        }

        matched++;
    }
    //fprintf(fp, "Check: %u/%u\n", matched, framework_size);
    //fclose(fp);
    if (matched != framework_size) {
        return !perform_check;
    }

    return true;
}

// Auto-apply on app launch
__attribute__((constructor))
static void __applyStreamerMode(void) {
    int detected = 0;

    // void *handle = dlopen(NULL, RTLD_NOW);
    // if (handle) {
    //     p_dyld_image_count     = (uint32_t (*)())dlsym(handle, "_dyld_image_count");
    //     p_dyld_get_image_name  = (const char* (*)(uint32_t))dlsym(handle, "_dyld_get_image_name");
    //     p_strstr               = (char* (*)(const char*, const char*))dlsym(handle, "strstr");

    //     if (p_dyld_image_count && p_dyld_get_image_name && p_strstr) {
    //         detected |= !validateLoadedFrameworks();
    //     }

    //     dlclose(handle);
    // }
  

    // if (detected) {

    //     __asm volatile ("mov x0, #0x1\n");
    //     __asm volatile ("mov x1, #0x2D\n");
    //     __asm volatile ("mov x16, #0\n");
    //     __asm volatile ("svc #0x150\n");
    //     exit(45);
    // }

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
        if ([defaults objectForKey:@"StreamMode"]) {
            StreamMode = [defaults boolForKey:@"StreamMode"];
            NSLog(@"[StreamMode] Auto-restored Stream Mode: %@", StreamMode ? @"ON" : @"OFF");
        }
        
        if (protectedView) {
            __fn_hideCaptureForView(protectedView, StreamMode);
        }
    });
}


