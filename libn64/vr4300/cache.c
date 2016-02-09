#include <stdint.h>
#include <rcp/ri.h>
#include <vr4300/cache.h>

void writeback_dcache_all(void) {
    uint32_t start = KSEG0(RDRAM);
    uint32_t end = start + DCACHE_SIZE - DCACHE_LINE_SIZE;
    for(uint32_t line = start; line <= end; line += DCACHE_LINE_SIZE) {
        __builtin_mips_cache(CACHE_PD|CACHE_IWBINV, (void *)line);
    }
}

