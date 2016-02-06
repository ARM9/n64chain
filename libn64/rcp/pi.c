#include <rcp/pi.h>

/* dma_cart_to_dram
 *  dest = rdram addr, must be 8 byte aligned
 *  src  = cart addr, must be 2 byte aligned
 *  size = size in bytes, must be multiple of 8
 */
void dma_rom_to_dram(void *dest, const void *src, uint32_t size) {
    pi_wait();
    *PI_DRAM_ADDR = (uint32_t)dest & 0x7FFFFF;
    /* TODO maybe OR cart domain in src argument for generic cart dma.
     * Might be suboptimal, investigate pi timing registers
     */
    *PI_CART_ADDR = CART_DOM1_ROM | ((uint32_t)src & 0x3FFFFFF);
    *PI_WR_LEN = size-1;
}

