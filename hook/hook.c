/*
 * 🔥 Zexis Inline Hook System 🔥
 * Created by Zexis (Telegram: @zexisyy)
 * Respect the creator — please give credit.
 */

#include "hook.h"
#include "mach_excServer.h"
#include <CoreFoundation/CoreFoundation.h>
#include <dlfcn.h>
#include <mach-o/dyld_images.h>
#include <mach-o/nlist.h>
#include <mach/mach.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <string.h>

#define ZEXIS_PROTECT_SIG 0x5A45584953594F59  
static const uint64_t zexis_sig = ZEXIS_PROTECT_SIG;

__attribute__((constructor))
static void zexis_init_protect() {
    if (zexis_sig != ZEXIS_PROTECT_SIG) {
        abort(); 
    }
}

mach_port_t server;

struct hook {
    uintptr_t address;
    uintptr_t function;
};
static struct hook hooks[16];
static int active_hooks;

kern_return_t catch_mach_exception_raise(
    mach_port_t exception_port,
    mach_port_t thread,
    mach_port_t task,
    exception_type_t exception,
    mach_exception_data_t code,
    mach_msg_type_number_t codeCnt) {
    abort();
}

kern_return_t catch_mach_exception_raise_state_identity(
    mach_port_t exception_port,
    mach_port_t thread,
    mach_port_t task,
    exception_type_t exception,
    mach_exception_data_t code,
    mach_msg_type_number_t codeCnt,
    int *flavor,
    thread_state_t old_state,
    mach_msg_type_number_t old_stateCnt,
    thread_state_t new_state,
    mach_msg_type_number_t *new_stateCnt) {
    abort();
}

kern_return_t catch_mach_exception_raise_state(
    mach_port_t exception_port,
    exception_type_t exception,
    const mach_exception_data_t code,
    mach_msg_type_number_t codeCnt,
    int *flavor,
    const thread_state_t old_state,
    mach_msg_type_number_t old_stateCnt,
    thread_state_t new_state,
    mach_msg_type_number_t *new_stateCnt) {
    
    arm_thread_state64_t *address = (arm_thread_state64_t *)old_state;
    arm_thread_state64_t *function = (arm_thread_state64_t *)new_state;

    for (int i = 0; i < active_hooks; ++i) {
        if (hooks[i].address == arm_thread_state64_get_pc(*address)) {
            *function = *address;
            *new_stateCnt = old_stateCnt;
            arm_thread_state64_set_pc_fptr(*function, hooks[i].function);
            return KERN_SUCCESS;
        }
    }

    return KERN_FAILURE;
}

void *exception_handler(void *unused) {
    mach_msg_server(mach_exc_server, sizeof(union __RequestUnion__catch_mach_exc_subsystem), server, MACH_MSG_OPTION_NONE);
    abort();
}

bool Zexis(void *address[], void *function[], int count) {
    if (count > 6) return false;

    static bool initialized = false;
    static int breakpoints = 6;

    if (!initialized) {
        size_t size = sizeof(breakpoints);
        sysctlbyname("hw.optional.breakpoint", &breakpoints, &size, NULL, 0);
        mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &server);
        mach_port_insert_right(mach_task_self(), server, server, MACH_MSG_TYPE_MAKE_SEND);
        task_set_exception_ports(mach_task_self(), EXC_MASK_BREAKPOINT, server, EXCEPTION_STATE | MACH_EXCEPTION_CODES, ARM_THREAD_STATE64);
        pthread_t thread;
        pthread_create(&thread, NULL, exception_handler, NULL);
        initialized = true;
    }

    if (count > breakpoints) return false;

    arm_debug_state64_t state = {};
    for (int i = 0; i < count; i++) {
        state.__bvr[i] = (uintptr_t)address[i];
        state.__bcr[i] = 0x1e5;
        hooks[i] = (struct hook){(uintptr_t)address[i], (uintptr_t)function[i]};
    }
    active_hooks = count;

    if (task_set_state(mach_task_self(), ARM_DEBUG_STATE64, (thread_state_t)&state, ARM_DEBUG_STATE64_COUNT) != KERN_SUCCESS)
        return false;

    thread_act_array_t threads;
    mach_msg_type_number_t thread_count = ARM_DEBUG_STATE64_COUNT;
    task_threads(mach_task_self(), &threads, &thread_count);

    bool success = true;
    for (int i = 0; i < thread_count; ++i)
        if (thread_set_state(threads[i], ARM_DEBUG_STATE64, (thread_state_t)&state, ARM_DEBUG_STATE64_COUNT) != KERN_SUCCESS)
            success = false;

    for (int i = 0; i < thread_count; ++i)
        mach_port_deallocate(mach_task_self(), threads[i]);
    vm_deallocate(mach_task_self(), (vm_address_t)threads, thread_count * sizeof(*threads));

    return success;
}

bool ZexisUnhook(void *address) {
    arm_debug_state64_t state = {};
    int newCount = 0;
    struct hook newHooks[16] = {};

    for (int i = 0; i < active_hooks; ++i) {
        if ((void*)hooks[i].address != address) {
            newHooks[newCount] = hooks[i];
            state.__bvr[newCount] = hooks[i].address;
            state.__bcr[newCount] = 0x1e5;
            newCount++;
        }
    }

    active_hooks = newCount;
    memcpy(hooks, newHooks, sizeof(newHooks));

    if (task_set_state(mach_task_self(), ARM_DEBUG_STATE64, (thread_state_t)&state, ARM_DEBUG_STATE64_COUNT) != KERN_SUCCESS)
        return false;

    thread_act_array_t threads;
    mach_msg_type_number_t thread_count = ARM_DEBUG_STATE64_COUNT;
    task_threads(mach_task_self(), &threads, &thread_count);

    bool success = true;
    for (int i = 0; i < thread_count; ++i)
        if (thread_set_state(threads[i], ARM_DEBUG_STATE64, (thread_state_t)&state, ARM_DEBUG_STATE64_COUNT) != KERN_SUCCESS)
            success = false;

    for (int i = 0; i < thread_count; ++i)
        mach_port_deallocate(mach_task_self(), threads[i]);
    vm_deallocate(mach_task_self(), (vm_address_t)threads, thread_count * sizeof(*threads));

    return success;
}
