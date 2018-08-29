//
// libn64/vr4300/cache.h: CPU cache helper functions and macros.
// TODO probably merge with other cpu control stuff.
//
#ifndef LIBN64_VR4300_CACHE_H
#define LIBN64_VR4300_CACHE_H

/* Data cache */
#define DCACHE_SIZE         0x2000
#define DCACHE_LINE_SIZE    16
/* Instruction cache */
#define ICACHE_SIZE         0x4000
#define ICACHE_LINE_SIZE    32

/* Cache specifiers for cache instruction */
#define CACHE_PI  0 // Primary instruction cache
#define CACHE_PD  1 // Primary data cache
#define CACHE_SI  2 // Secondary instruction cache
#define CACHE_SD  3 // Secondary data cache
/* Cache operations for cache instruction */
#define CACHE_IINV      0x0  // Index invalidate (PI, SI)
#define CACHE_IWBINV    0x0  // Index writeback invalidate (PD, SD)
#define CACHE_ILT       0x4  // Index load tag (all)
#define CACHE_IST       0x8  // Index store tag (all)
#define CACHE_CDX       0xC  // Create dirty exclusive (PD, SD)
#define CACHE_HINV      0x10 // Hit invalidate (all)
#define CACHE_HWBINV    0x14 // Hit writeback invalidate (PD, SD)
#define CACHE_FILL      0x14 // Fill (PI)
#define CACHE_HWB       0x18 // Hit writeback (PD, SD, PI)
#define CACHE_HSV       0x1C // Hit set virtual (SI, SD)

#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>

/*static inline void __cache_op(uint8_t op, void *base, int16_t offset) {
    __asm__ __volatile__ (
        "cache %[op], %[offset](%[base])\n\t"
        :: [op] "i" (op), [base] "r" (base), [offset] "i" (offset)
    );
}*/

#ifdef __cplusplus
extern "C" {
#endif

void writeback_dcache_all(void);

#ifdef __cplusplus
}
#endif

#endif

#endif

