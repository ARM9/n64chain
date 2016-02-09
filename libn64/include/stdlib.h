#ifndef LIBN64_STDLIB_H
#define LIBN64_STDLIB_H
#include <stddef.h>

static inline int abs(int n) {
    return __builtin_abs(n);
}

#endif
