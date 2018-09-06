#ifndef LIBN64_STDLIB_H
#define LIBN64_STDLIB_H
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

char * itoa (int value, char * buf, int base);
char * lltoa (int64_t value, char * buf, int base);

static inline int abs(int n) {
    return __builtin_abs(n);
}

#ifdef __cplusplus
}
#endif

#endif
