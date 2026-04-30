#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <sys/stat.h>
#import <dlfcn.h>
#import <dirent.h>
#import <spawn.h>
#import <substrate.h>

// ============================================
// JAILBREAK HIDER - HIDE ALL JB TRACES
// ============================================

// Common jailbreak detection paths
static NSArray *jailbreakPaths = nil;
static NSArray *jailbreakStrings = nil;

__attribute__((constructor))
static void initJailbreakPaths() {
    jailbreakPaths = @[
        // Jailbreak tools
        @"/Applications/Cydia.app",
        @"/Applications/Sileo.app",
        @"/Applications/Zebra.app",
        @"/Applications/Installer.app",
        @"/Applications/Filza.app",
        @"/Applications/checkra1n.app",
        @"/Applications/unc0ver.app",
        @"/Applications/Taurine.app",
        
        // System files
        @"/Library/MobileSubstrate",
        @"/usr/libexec/cydia",
        @"/usr/bin/cycript",
        @"/usr/local/bin/cycript",
        @"/usr/lib/libcycript.dylib",
        @"/usr/bin/ssh",
        @"/usr/bin/sshd",
        @"/usr/sbin/sshd",
        @"/etc/apt",
        @"/private/var/lib/apt",
        @"/private/var/lib/cydia",
        @"/private/var/tmp/cydia.log",
        @"/private/var/log/syslog",
        
        // Tweak injection
        @"/usr/lib/TweakInject",
        @"/Library/TweakInject",
        @"/usr/lib/substrate",
        @"/usr/lib/substitute",
        
        // Bootstrap
        @"/var/jb",
        @"/var/binpack",
        @"/.installed_dopamine",
        @"/.installed_unc0ver",
        @"/taurine",
        @"/chimera",
        @"/electra",
        @"/odyssey",
        
        // Common write locations
        @"/private/jailbreak.txt",
        @"/private/test.txt",
        @"/private/var/mobile/test.txt",
    ];
    
    jailbreakStrings = @[
        @"cydia",
        @"substrate",
        @"substitute",
        @"jailbreak",
        @"jail",
        @"sileo",
        @"zebra",
        @"filza",
        @"checkra1n",
        @"unc0ver",
        @"taurine",
        @"chimera",
        @"electra",
        @"odyssey",
        @"libhooker",
        @"frida",
        @"cycript",
    ];
}

// Check if path is jailbreak-related
static BOOL isJailbreakPath(const char* path) {
    if (!path) return NO;
    
    NSString *pathStr = [NSString stringWithUTF8String:path];
    pathStr = [pathStr lowercaseString];
    
    for (NSString *jbPath in jailbreakPaths) {
        if ([pathStr containsString:[jbPath lowercaseString]]) {
            return YES;
        }
    }
    
    for (NSString *jbString in jailbreakStrings) {
        if ([pathStr containsString:jbString]) {
            return YES;
        }
    }
    
    return NO;
}

// ============================================
// HOOK stat/lstat/fstat - Hide files
// ============================================
static int (*orig_stat)(const char* path, struct stat* buf);
static int (*orig_lstat)(const char* path, struct stat* buf);
static int (*orig_fstat)(int fd, struct stat* buf);

static int hook_stat(const char* path, struct stat* buf) {
    if (isJailbreakPath(path)) {
        NSLog(@"[JBHider] 🚫 Blocked stat: %s", path);
        errno = ENOENT;
        return -1;
    }
    return orig_stat(path, buf);
}

static int hook_lstat(const char* path, struct stat* buf) {
    if (isJailbreakPath(path)) {
        NSLog(@"[JBHider] 🚫 Blocked lstat: %s", path);
        errno = ENOENT;
        return -1;
    }
    return orig_lstat(path, buf);
}

static int hook_fstat(int fd, struct stat* buf) {
    return orig_fstat(fd, buf);
}

// ============================================
// HOOK access - Pretend files don't exist
// ============================================
static int (*orig_access)(const char* path, int mode);

static int hook_access(const char* path, int mode) {
    if (isJailbreakPath(path)) {
        NSLog(@"[JBHider] 🚫 Blocked access: %s", path);
        errno = ENOENT;
        return -1;
    }
    return orig_access(path, mode);
}

// ============================================
// HOOK fopen - Block file opening
// ============================================
static FILE* (*orig_fopen)(const char* path, const char* mode);

static FILE* hook_fopen(const char* path, const char* mode) {
    if (isJailbreakPath(path)) {
        NSLog(@"[JBHider] 🚫 Blocked fopen: %s", path);
        return NULL;
    }
    return orig_fopen(path, mode);
}

// ============================================
// HOOK opendir - Block directory listing
// ============================================
static DIR* (*orig_opendir)(const char* path);

static DIR* hook_opendir(const char* path) {
    if (isJailbreakPath(path)) {
        NSLog(@"[JBHider] 🚫 Blocked opendir: %s", path);
        return NULL;
    }
    return orig_opendir(path);
}

// ============================================
// HOOK posix_spawn - Block process spawning
// ============================================
static int (*orig_posix_spawn)(pid_t* pid, const char* path, const posix_spawn_file_actions_t* file_actions, const posix_spawnattr_t* attrp, char* const argv[], char* const envp[]);

static int hook_posix_spawn(pid_t* pid, const char* path, const posix_spawn_file_actions_t* file_actions, const posix_spawnattr_t* attrp, char* const argv[], char* const envp[]) {
    if (path && isJailbreakPath(path)) {
        NSLog(@"[JBHider] 🚫 Blocked posix_spawn: %s", path);
        return -1;
    }
    
    if (argv && argv[0]) {
        NSString *cmd = [NSString stringWithUTF8String:argv[0]];
        if ([cmd containsString:@"cydia"] || 
            [cmd containsString:@"apt"] ||
            [cmd containsString:@"dpkg"]) {
            NSLog(@"[JBHider] 🚫 Blocked posix_spawn command: %s", argv[0]);
            return -1;
        }
    }
    
    return orig_posix_spawn(pid, path, file_actions, attrp, argv, envp);
}

// ============================================
// HOOK fork/vfork - Block process creation
// ============================================
static pid_t (*orig_fork)(void);
static pid_t (*orig_vfork)(void);

static pid_t hook_fork(void) {
    NSLog(@"[JBHider] 🚫 Blocked fork()");
    errno = ENOSYS;
    return -1;
}

static pid_t hook_vfork(void) {
    NSLog(@"[JBHider] 🚫 Blocked vfork()");
    errno = ENOSYS;
    return -1;
}

// ============================================
// HOOK getenv - Hide environment variables
// ============================================
static char* (*orig_getenv)(const char* name);

static char* hook_getenv(const char* name) {
    if (name) {
        NSString *envName = [NSString stringWithUTF8String:name];
        if ([envName containsString:@"DYLD"] ||
            [envName containsString:@"SUBSTRATE"] ||
            [envName containsString:@"SUBSTITUTE"]) {
            NSLog(@"[JBHider] 🚫 Blocked getenv: %s", name);
            return NULL;
        }
    }
    return orig_getenv(name);
}

// ============================================
// HOOK UIApplication canOpenURL
// ============================================
static BOOL (*orig_canOpenURL)(id self, SEL _cmd, NSURL* url);

static BOOL hook_canOpenURL(id self, SEL _cmd, NSURL* url) {
    if (url) {
        NSString *urlStr = [[url absoluteString] lowercaseString];
        if ([urlStr containsString:@"cydia"] ||
            [urlStr containsString:@"sileo"] ||
            [urlStr containsString:@"zbra"] ||
            [urlStr containsString:@"filza"]) {
            NSLog(@"[JBHider] 🚫 Blocked canOpenURL: %@", url);
            return NO;
        }
    }
    return orig_canOpenURL(self, _cmd, url);
}

// ============================================
// HOOK exit/abort - Prevent anti-jb kills
// ============================================
static void (*orig_exit)(int status);
static void (*orig_abort)(void);

static void hook_exit(int status) {
    NSLog(@"[JBHider] 🛡️ Intercepted exit(%d) - Ignoring!", status);
    // Don't actually exit
}

static void hook_abort(void) {
    NSLog(@"[JBHider] 🛡️ Intercepted abort() - Ignoring!");
    // Don't actually abort
}

// ============================================
// HOOK NSFileManager
// ============================================
static BOOL (*orig_fileExistsAtPath)(id self, SEL _cmd, NSString* path);

static BOOL hook_fileExistsAtPath(id self, SEL _cmd, NSString* path) {
    if (path && isJailbreakPath([path UTF8String])) {
        NSLog(@"[JBHider] 🚫 Blocked fileExistsAtPath: %@", path);
        return NO;
    }
    return orig_fileExistsAtPath(self, _cmd, path);
}

// ============================================
// HOOK syscall
// ============================================
#include <sys/syscall.h>
static long (*orig_syscall)(long number, ...);

static long hook_syscall(long number, ...) {
    if (number == SYS_ptrace) {
        NSLog(@"[JBHider] 🚫 Blocked ptrace syscall");
        return -1;
    }
    
    if (number == SYS_sysctl) {
        NSLog(@"[JBHider] 🚫 Blocked sysctl syscall");
        return -1;
    }
    
    va_list args;
    va_start(args, number);
    long arg1 = va_arg(args, long);
    long arg2 = va_arg(args, long);
    long arg3 = va_arg(args, long);
    long arg4 = va_arg(args, long);
    long arg5 = va_arg(args, long);
    long arg6 = va_arg(args, long);
    va_end(args);
    
    return orig_syscall(number, arg1, arg2, arg3, arg4, arg5, arg6);
}

// ============================================
// HOOK sysctl
// ============================================
#include <sys/sysctl.h>
static int (*orig_sysctl)(int* name, u_int namelen, void* oldp, size_t* oldlenp, void* newp, size_t newlen);

static int hook_sysctl(int* name, u_int namelen, void* oldp, size_t* oldlenp, void* newp, size_t newlen) {
    if (name && namelen > 0) {
        if (name[0] == CTL_KERN && name[1] == KERN_PROC) {
            NSLog(@"[JBHider] 🚫 Blocked sysctl KERN_PROC");
            errno = EINVAL;
            return -1;
        }
    }
    
    return orig_sysctl(name, namelen, oldp, oldlenp, newp, newlen);
}

// ============================================
// HOOK dlsym
// ============================================
static void* (*orig_dlsym)(void* handle, const char* symbol);

static void* hook_dlsym(void* handle, const char* symbol) {
    if (symbol) {
        NSString *sym = [NSString stringWithUTF8String:symbol];
        NSString *lowerSym = [sym lowercaseString];
        
        for (NSString *jbStr in jailbreakStrings) {
            if ([lowerSym containsString:jbStr]) {
                NSLog(@"[JBHider] 🚫 Hiding symbol: %s", symbol);
                return NULL;
            }
        }
    }
    
    return orig_dlsym(handle, symbol);
}

// ============================================
// HOOK task_info
// ============================================
#include <mach/mach.h>
static kern_return_t (*orig_task_info)(task_t target_task, task_flavor_t flavor, task_info_t task_info_out, mach_msg_type_number_t* task_info_outCnt);

static kern_return_t hook_task_info(task_t target_task, task_flavor_t flavor, task_info_t task_info_out, mach_msg_type_number_t* task_info_outCnt) {
    kern_return_t result = orig_task_info(target_task, flavor, task_info_out, task_info_outCnt);
    
    if (flavor == TASK_DYLD_INFO) {
        NSLog(@"[JBHider] 🛡️ Blocked TASK_DYLD_INFO query");
        return KERN_FAILURE;
    }
    
    return result;
}

// ============================================
// INITIALIZE ALL HOOKS
// ============================================
__attribute__((constructor))
static void initializeJailbreakHider() {
    NSLog(@"[JBHider] 🛡️ Initializing Jailbreak Hider...");
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 2 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
        NSLog(@"\n[JBHider] 🚀 Installing jailbreak hiding hooks...\n");
        
        // File system hooks
        MSHookFunction((void*)stat, (void*)hook_stat, (void**)&orig_stat);
        MSHookFunction((void*)lstat, (void*)hook_lstat, (void**)&orig_lstat);
        MSHookFunction((void*)fstat, (void*)hook_fstat, (void**)&orig_fstat);
        MSHookFunction((void*)access, (void*)hook_access, (void**)&orig_access);
        MSHookFunction((void*)fopen, (void*)hook_fopen, (void**)&orig_fopen);
        MSHookFunction((void*)opendir, (void*)hook_opendir, (void**)&orig_opendir);
        NSLog(@"[JBHider] ✅ Hooked file system functions");
        
        // Process/system hooks
        MSHookFunction((void*)posix_spawn, (void*)hook_posix_spawn, (void**)&orig_posix_spawn);
        MSHookFunction((void*)fork, (void*)hook_fork, (void**)&orig_fork);
        MSHookFunction((void*)vfork, (void*)hook_vfork, (void**)&orig_vfork);
        MSHookFunction((void*)getenv, (void*)hook_getenv, (void**)&orig_getenv);
        MSHookFunction((void*)exit, (void*)hook_exit, (void**)&orig_exit);
        MSHookFunction((void*)abort, (void*)hook_abort, (void**)&orig_abort);
        NSLog(@"[JBHider] ✅ Hooked process functions");
        
        // Advanced hooks
        MSHookFunction((void*)syscall, (void*)hook_syscall, (void**)&orig_syscall);
        MSHookFunction((void*)sysctl, (void*)hook_sysctl, (void**)&orig_sysctl);
        MSHookFunction((void*)dlsym, (void*)hook_dlsym, (void**)&orig_dlsym);
        MSHookFunction((void*)task_info, (void*)hook_task_info, (void**)&orig_task_info);
        NSLog(@"[JBHider] ✅ Hooked advanced detection functions");
        
        // ObjC hooks
        Class fileManager = NSClassFromString(@"NSFileManager");
        if (fileManager) {
            MSHookMessageEx(fileManager, 
                          @selector(fileExistsAtPath:),
                          (IMP)hook_fileExistsAtPath,
                          (IMP*)&orig_fileExistsAtPath);
            NSLog(@"[JBHider] ✅ Hooked NSFileManager");
        }
        
        Class uiApp = NSClassFromString(@"UIApplication");
        if (uiApp) {
            MSHookMessageEx(uiApp,
                          @selector(canOpenURL:),
                          (IMP)hook_canOpenURL,
                          (IMP*)&orig_canOpenURL);
            NSLog(@"[JBHider] ✅ Hooked UIApplication");
        }
        
        NSLog(@"\n╔═══════════════════════════════════════════════════════╗");
        NSLog(@"║       ✅ JAILBREAK HIDER ACTIVE! ✅                  ║");
        NSLog(@"╚═══════════════════════════════════════════════════════╝");
        NSLog(@"[JBHider] 🛡️ Hiding %lu jailbreak paths", (unsigned long)[jailbreakPaths count]);
        NSLog(@"[JBHider] 🚫 Blocking file access checks");
        NSLog(@"[JBHider] 🚫 Blocking fork/exec");
        NSLog(@"[JBHider] 🚫 Blocking URL scheme checks");
        NSLog(@"[JBHider] 🛡️ Intercepting exit/abort\n");
    });
}