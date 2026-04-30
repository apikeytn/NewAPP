#import <Foundation/Foundation.h>
#import <mach-o/dyld.h>
#import <dlfcn.h>
#import <sys/stat.h>
#import <substrate.h>

// ============================================
// DYLIB HIDER - HIDE OUR TWEAK FROM DETECTION
// ============================================

static NSArray *hiddenDylibs = nil;
static NSArray *hiddenPaths = nil;

__attribute__((constructor))
static void initHiddenDylibs() {
    // List of dylibs/paths to hide
    hiddenDylibs = @[
        @"Fluck",                // Your tweak name
        @"fluck",                // lowercase
        @"OffsetMonitor",        // Monitor tweak
        @"UniversalMonitor",     // Universal monitor
        @"substrate",            // Substrate
        @"substitute",           // Substitute
        @"CydiaSubstrate",       // Cydia Substrate
        @"libhooker",            // libhooker
        @"rocketbootstrap",      // RocketBootstrap
        @"PreferenceLoader",     // PreferenceLoader
        @"MobileSubstrate",      // Mobile Substrate
        @"patcherplus",          // Any custom tweaks
    ];
    
    hiddenPaths = @[
        @"/Library/MobileSubstrate",
        @"/usr/lib/TweakInject",
        @"/Library/Frameworks/CydiaSubstrate.framework",
        @"/Library/Frameworks/Fluck.dylib",
        @"/usr/lib/substrate",
        @"/usr/lib/substitute",
        @"/var/mobile/Library",
    ];
}

// Check if image should be hidden
static BOOL shouldHideImage(const char* imageName) {
    if (!imageName) return NO;
    
    NSString *name = [NSString stringWithUTF8String:imageName];
    
    // Check against hidden dylib names
    for (NSString *hidden in hiddenDylibs) {
        if ([name rangeOfString:hidden options:NSCaseInsensitiveSearch].location != NSNotFound) {
            return YES;
        }
    }
    
    // Check against hidden paths
    for (NSString *path in hiddenPaths) {
        if ([name rangeOfString:path options:NSCaseInsensitiveSearch].location != NSNotFound) {
            return YES;
        }
    }
    
    return NO;
}

// ============================================
// HOOK _dyld_image_count
// ============================================
static uint32_t (*orig_dyld_image_count)(void);

static uint32_t hook_dyld_image_count(void) {
    uint32_t realCount = orig_dyld_image_count();
    uint32_t hiddenCount = 0;
    
    // Count how many images should be hidden
    for (uint32_t i = 0; i < realCount; i++) {
        const char* imageName = _dyld_get_image_name(i);
        if (shouldHideImage(imageName)) {
            hiddenCount++;
        }
    }
    
    uint32_t fakeCount = realCount - hiddenCount;
    
    NSLog(@"[DylibHider] 🔍 _dyld_image_count: Real=%d, Hidden=%d, Returned=%d", 
          realCount, hiddenCount, fakeCount);
    
    return fakeCount;
}

// ============================================
// HOOK _dyld_get_image_name
// ============================================
static const char* (*orig_dyld_get_image_name)(uint32_t image_index);

static const char* hook_dyld_get_image_name(uint32_t image_index) {
    const char* imageName = orig_dyld_get_image_name(image_index);
    
    if (shouldHideImage(imageName)) {
        // Return a fake system library instead
        const char* fakeLib = "/System/Library/Frameworks/Foundation.framework/Foundation";
        NSLog(@"[DylibHider] 🎭 Hiding: %s → %s", imageName, fakeLib);
        return fakeLib;
    }
    
    return imageName;
}

// ============================================
// HOOK _dyld_get_image_header
// ============================================
static const struct mach_header* (*orig_dyld_get_image_header)(uint32_t image_index);

static const struct mach_header* hook_dyld_get_image_header(uint32_t image_index) {
    const char* imageName = _dyld_get_image_name(image_index);
    
    if (shouldHideImage(imageName)) {
        // Return Foundation's header instead
        const struct mach_header* fakeHeader = orig_dyld_get_image_header(0);
        NSLog(@"[DylibHider] 🎭 Hiding header for: %s", imageName);
        return fakeHeader;
    }
    
    return orig_dyld_get_image_header(image_index);
}

// ============================================
// HOOK _dyld_get_image_vmaddr_slide
// ============================================
static intptr_t (*orig_dyld_get_image_vmaddr_slide)(uint32_t image_index);

static intptr_t hook_dyld_get_image_vmaddr_slide(uint32_t image_index) {
    const char* imageName = _dyld_get_image_name(image_index);
    
    if (shouldHideImage(imageName)) {
        NSLog(@"[DylibHider] 🎭 Hiding slide for: %s", imageName);
        return 0;
    }
    
    return orig_dyld_get_image_vmaddr_slide(image_index);
}

// ============================================
// HOOK dlopen - Prevent loading detection
// ============================================
static void* (*orig_dlopen)(const char* path, int mode);

static void* hook_dlopen(const char* path, int mode) {
    if (path && shouldHideImage(path)) {
        NSLog(@"[DylibHider] 🚫 Blocked dlopen: %s", path);
        return NULL; // Pretend it doesn't exist
    }
    
    return orig_dlopen(path, mode);
}

// ============================================
// HOOK dlsym - Hide symbols
// ============================================
static void* (*orig_dlsym)(void* handle, const char* symbol);

static void* hook_dlsym(void* handle, const char* symbol) {
    if (symbol) {
        NSString *sym = [NSString stringWithUTF8String:symbol];
        
        // Hide substrate/hooking symbols
        if ([sym containsString:@"substrate"] ||
            [sym containsString:@"MSHook"] ||
            [sym containsString:@"substitute"] ||
            [sym containsString:@"fishhook"] ||
            [sym containsString:@"dobby"]) {
            NSLog(@"[DylibHider] 🚫 Hiding symbol: %s", symbol);
            return NULL;
        }
    }
    
    return orig_dlsym(handle, symbol);
}

// ============================================
// HOOK dladdr - Hide dylib info
// ============================================
static int (*orig_dladdr)(const void* addr, Dl_info* info);

static int hook_dladdr(const void* addr, Dl_info* info) {
    int result = orig_dladdr(addr, info);
    
    if (result && info && info->dli_fname) {
        if (shouldHideImage(info->dli_fname)) {
            // Replace with fake system library
            info->dli_fname = "/System/Library/Frameworks/Foundation.framework/Foundation";
            info->dli_fbase = (void*)0x100000000;
            info->dli_sname = NULL;
            info->dli_saddr = NULL;
            NSLog(@"[DylibHider] 🎭 Faked dladdr info");
        }
    }
    
    return result;
}

// ============================================
// HOOK stat/access - Hide files
// ============================================
static int (*orig_stat)(const char* path, struct stat* buf);
static int (*orig_access)(const char* path, int mode);

static int hook_stat(const char* path, struct stat* buf) {
    if (path && shouldHideImage(path)) {
        NSLog(@"[DylibHider] 🚫 Hiding stat: %s", path);
        errno = ENOENT; // File not found
        return -1;
    }
    return orig_stat(path, buf);
}

static int hook_access(const char* path, int mode) {
    if (path && shouldHideImage(path)) {
        NSLog(@"[DylibHider] 🚫 Hiding access: %s", path);
        errno = ENOENT;
        return -1;
    }
    return orig_access(path, mode);
}

// ============================================
// HOOK fopen - Hide file opening
// ============================================
static FILE* (*orig_fopen)(const char* path, const char* mode);

static FILE* hook_fopen(const char* path, const char* mode) {
    if (path && shouldHideImage(path)) {
        NSLog(@"[DylibHider] 🚫 Hiding fopen: %s", path);
        return NULL;
    }
    return orig_fopen(path, mode);
}

// ============================================
// INITIALIZE HOOKS
// ============================================
__attribute__((constructor))
static void initializeDylibHider() {
    NSLog(@"[DylibHider] 🎭 Initializing Dylib Hider...");
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        NSLog(@"\n[DylibHider] 🚀 Installing hiding hooks...\n");
        
        // Hook dyld functions
        MSHookFunction((void*)_dyld_image_count, (void*)hook_dyld_image_count, (void**)&orig_dyld_image_count);
        MSHookFunction((void*)_dyld_get_image_name, (void*)hook_dyld_get_image_name, (void**)&orig_dyld_get_image_name);
        MSHookFunction((void*)_dyld_get_image_header, (void*)hook_dyld_get_image_header, (void**)&orig_dyld_get_image_header);
        MSHookFunction((void*)_dyld_get_image_vmaddr_slide, (void*)hook_dyld_get_image_vmaddr_slide, (void**)&orig_dyld_get_image_vmaddr_slide);
        NSLog(@"[DylibHider] ✅ Hooked dyld image functions");
        
        // Hook dl functions
        MSHookFunction((void*)dlopen, (void*)hook_dlopen, (void**)&orig_dlopen);
        MSHookFunction((void*)dlsym, (void*)hook_dlsym, (void**)&orig_dlsym);
        MSHookFunction((void*)dladdr, (void*)hook_dladdr, (void**)&orig_dladdr);
        NSLog(@"[DylibHider] ✅ Hooked dl functions");
        
        // Hook file system functions
        MSHookFunction((void*)stat, (void*)hook_stat, (void**)&orig_stat);
        MSHookFunction((void*)access, (void*)hook_access, (void**)&orig_access);
        MSHookFunction((void*)fopen, (void*)hook_fopen, (void**)&orig_fopen);
        NSLog(@"[DylibHider] ✅ Hooked file system functions");
        
        NSLog(@"\n╔═══════════════════════════════════════════════════════╗");
        NSLog(@"║        ✅ DYLIB HIDER ACTIVE! ✅                     ║");
        NSLog(@"╚═══════════════════════════════════════════════════════╝");
        NSLog(@"[DylibHider] 🎭 Hiding %lu dylib names", (unsigned long)[hiddenDylibs count]);
        NSLog(@"[DylibHider] 📁 Hiding %lu paths", (unsigned long)[hiddenPaths count]);
        NSLog(@"[DylibHider] 🔍 Image count will be reduced");
        NSLog(@"[DylibHider] 🎭 Dylib names will be faked\n");
    });
}