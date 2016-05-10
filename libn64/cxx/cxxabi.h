#ifndef LIBN64_CXX_CXXABI_H
#define LIBN64_CXX_CXXABI_H

#define ATEXIT_MAX_FUNCS 64

#ifdef __cplusplus
extern "C" {
#endif

typedef int uarch_t;

struct atexit_func_entry_t {
    void (*destructor_func)(void *);
    void *obj_ptr;
    void *dso_handle;
};

//int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);
//void __cxa_finalize(void *f);

#ifdef __cplusplus
}
#endif

#endif

