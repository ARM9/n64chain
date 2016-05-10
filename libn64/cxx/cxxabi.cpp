#include "cxx/cxxabi.h"

#ifdef __cplusplus
extern "C" {
#endif

void __cxa_pure_virtual() {
    volatile int sp;
    char m[] = "Error: __cxa_pure_virtual";
    char *p = (char*)&sp;
    for(unsigned i = 0; i < sizeof(m); i++)
        *p++ = m[i];
    while(1);
}

/*atexit_func_entry_t __atexit_funcs[ATEXIT_MAX_FUNCS];
uarch_t __atexit_func_count = 0;

void *__dso_handle = 0;

int __cxa_atexit(void (*f)(void *), void *objptr, void *dso) {
    if(__atexit_func_count >= ATEXIT_MAX_FUNCS) { return -1; }
    __atexit_funcs[__atexit_func_count].destructor_func = f;
    __atexit_funcs[__atexit_func_count].obj_ptr = objptr;
    __atexit_funcs[__atexit_func_count].dso_handle = dso;
    __atexit_func_count++;
    return 0;
}*/

/* do we even care about global destructors? */
/*void __cxa_finalize(void *f) {
    uarch_t i = __atexit_func_count;
    if(!f) {
        while(i--) {
            if(__atexit_funcs[i].destructor_func) {
                (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
            }
        }
        return;
    }
    for(; i >= 0; --i) {
        if((void*)__atexit_funcs[i].destructor_func == f) {
            (*__atexit_funcs[i].destructor_func)(__atexit_funcs[i].obj_ptr);
             __atexit_funcs[i].destructor_func = 0;
        }
    }
}*/

#ifdef __cplusplus
}
#endif

