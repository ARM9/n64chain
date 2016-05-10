#ifndef LIBN64_STDLIB_H
#define LIBN64_STDLIB_H
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline int abs(int n) {
    return __builtin_abs(n);
}

#ifdef __cplusplus
}
#endif

#endif
