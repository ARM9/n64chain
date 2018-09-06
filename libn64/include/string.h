#ifndef LIBN64_STRING_H
#define LIBN64_STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void memcpy(void * const destination, const void * const source, size_t len);
void memset (void * const dest, char val, size_t len);

size_t strlen (const char * str);

#ifdef __cplusplus
}
#endif

#endif
