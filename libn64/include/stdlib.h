#ifndef LIBN64_STDLIB_H
#define LIBN64_STDLIB_H
#include <stddef.h>

static inline int abs(int n) {
    int a, dummy;
    __asm__ __volatile__(
        "sra %1,%2,31\n\t"
        "xor %2,%2,%1\n\t"
        "sub %0,%2,%1\n\t"
        :"=r" (a), "=r" (dummy)
        :"r" (n)
        :);
    return a;
}

#endif
