#ifndef LIBN64_STDLIB_H
#define LIBN64_STDLIB_H
#include <stddef.h>

char * itoa (int value, char * buf, int base);

static inline int abs(int n) {
    return __builtin_abs(n);
}

#endif
