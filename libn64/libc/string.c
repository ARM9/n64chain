#include <string.h>

void memcpy(void * const destination, const void * const source, size_t len)
{
    char * const a = destination;
    const char * const b = source;
    for ( size_t i = 0; i < len; i++ )
    {
        a[i] = b[i];
    }
}

void memset (void * const dest, char val, size_t len) {
    size_t i = 0;

    int * const buf_i = dest;
    int slab = (val<<24) | (val<<16) | (val<<8) | val;
    while (len > 16) {
        buf_i[i++] = slab;
        buf_i[i++] = slab;
        buf_i[i++] = slab;
        buf_i[i++] = slab;
        len -= 16;
    }

    char * const buf = dest;
    while (len--) {
        buf[i++] = val;
    }
}

size_t strlen (const char * str) {
    size_t len = 0;
    while (*str++) len++;
    return len;
}

