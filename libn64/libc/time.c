#include <time.h>

clock_t get_ticks_ms(void) {
    return clock() / (CLOCKS_PER_SEC / 1000L);
}

clock_t get_ticks_us(void) {
    return clock() / (CLOCKS_PER_SEC / 1000000L);
}

