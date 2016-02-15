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
