#include <stdlib.h>
#include <stddef.h>

void *operator new(size_t size) {
    //return malloc(size);
    return NULL;
}

void *operator new[](size_t size) {
    //return malloc(size);
    return NULL;
}

void operator delete(void *p) {
    //free(p);
}

void operator delete[](void *p) {
    //free(p);
}
