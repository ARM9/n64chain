#include <time.h>

clock_t clock(void) {
    clock_t count;
    __asm__ __volatile__(
        "mfc0 %0,$9"
        :"=r" (count)::);
    return count;
}

clock_t get_ticks_ms(void) {
    return clock() / (CLOCKS_PER_SEC / 1000L);
}

clock_t get_ticks_us(void) {
    return clock() / (CLOCKS_PER_SEC / 1000000L);
}

