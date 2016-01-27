//
// libn64/include/time.h: libc time
//
// N64Tool: A (free) open-source N64 development toolchain.
// Copyright 2014 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef LIBN64_TIME_H
#define LIBN64_TIME_H

#include "vr4300/cp0.h"

typedef long time_t;
typedef unsigned long clock_t;

#define CLOCKS_PER_SEC (93750000/2)

/*struct timespec {
    time_t  tv_sec;
    nseconds_t tv_nsec;
};*/

struct timeval {
    time_t tv_sec;
    time_t tv_usec;
};

static inline clock_t clock(void) {
    clock_t count;
    __asm__ __volatile__(
        "mfc0 %0, "COP0_COUNT
        :"=r" (count)::);
    return count;
}

clock_t get_ticks(void);

clock_t get_ticks_ms(void);

clock_t get_ticks_us(void);

#endif
