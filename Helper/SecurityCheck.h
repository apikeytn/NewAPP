#include <mach-o/dyld.h>   // For _dyld_image_count, etc.
#include <dlfcn.h>         // For dladdr
#include <string.h>        // For strstr
#include <stdlib.h>        // For abort()

// Changed from dylib to framework
#define EXPECTED_FRAMEWORK_NAME "Fluck.framework/Fluck"
#define EXPECTED_FRAMEWORK_BUNDLE "Fluck.framework"
#define MAX_ALLOWED_DYLIBS 28


inline bool isMyFrameworkLoaded() {
    // for (uint32_t i = 0; i < _dyld_image_count(); i++) {
    //     const char* name = _dyld_get_image_name(i);
    //     // Check for framework bundle name
    //     if (strstr(name, EXPECTED_FRAMEWORK_BUNDLE)) {
    //         return true;
    //     }
    // }
    // return false;
    return true;
}

// inline const char* getOwnFrameworkPath() {
//     Dl_info info;
//     if (dladdr((void *)getOwnFrameworkPath, &info)) {
//         return info.dli_fname;
//     }
//     return NULL;
// }

inline void performSecurityCheck() {
    // const char* path = getOwnFrameworkPath();
    
    // // Check if path contains the framework bundle name
    // if (!path || !strstr(path, EXPECTED_FRAMEWORK_BUNDLE)) {
    //     abort(); // crash if framework name doesn't match
    // }
    
    // Verify framework is loaded
    if (!isMyFrameworkLoaded()) {
        abort(); // crash if framework not present in loaded list
    }
}