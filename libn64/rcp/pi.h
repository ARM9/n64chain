#ifndef LIBN64_RCP_PI_H
#define LIBN64_RCP_PI_H

#include <mmio.h>

#define PI_BASE 0xA4600000 // $04600000..$04600033 Peripheral Interface (PI) Base Register
#define PI_DRAM_ADDR    IO_32(PI_BASE,0x00) // $04600000..$04600003 PI: DRAM Address Register
#define PI_CART_ADDR    IO_32(PI_BASE,0x04) // $04600004..$04600007 PI: Pbus (Cartridge) Address Register
#define PI_RD_LEN       IO_32(PI_BASE,0x08) // $04600008..$0460000B PI: Read Length Register
#define PI_WR_LEN       IO_32(PI_BASE,0x0C) // $0460000C..$0460000F PI: Write length register
#define PI_STATUS       IO_32(PI_BASE,0x10) // $04600010..$04600013 PI: Status Register
#define PI_BSD_DOM1_LAT IO_32(PI_BASE,0x14) // $04600014..$04600017 PI: Domain 1 Latency Register
#define PI_BSD_DOM1_PWD IO_32(PI_BASE,0x18) // $04600018..$0460001B PI: Domain 1 Pulse Width Register
#define PI_BSD_DOM1_PGS IO_32(PI_BASE,0x1C) // $0460001C..$0460001F PI: Domain 1 Page Size Register
#define PI_BSD_DOM1_RLS IO_32(PI_BASE,0x20) // $04600020..$04600023 PI: Domain 1 Release Register
#define PI_BSD_DOM2_LAT IO_32(PI_BASE,0x24) // $04600024..$04600027 PI: Domain 2 Latency Register
#define PI_BSD_DOM2_PWD IO_32(PI_BASE,0x28) // $04600028..$0460002B PI: Domain 2 Pulse Width Register
#define PI_BSD_DOM2_PGS IO_32(PI_BASE,0x2C) // $0460002C..$0460002F PI: Domain 2 Page Size Register
#define PI_BSD_DOM2_RLS IO_32(PI_BASE,0x30) // $04600030..$04600033 PI: Domain 2 Release Register

// Status read flags
#define PI_DMA_BUSY 1
#define PI_IO_BUSY  2
#define PI_ERROR    4
#define PI_IRQ      8
// Status write flags
#define PI_RESET            1
#define PI_CLEAR_INTERRUPT  2

#define CART_DOM2_ADDR1 0x05000000 // $05000000..$0507FFFF Cartridge Domain 2(Address 1) SRAM
#define CART_DOM1_ADDR1 0x06000000 // $06000000..$07FFFFFF Cartridge Domain 1(Address 1) 64DD
#define CART_DOM2_ADDR2 0x08000000 // $08000000..$0FFFFFFF Cartridge Domain 2(Address 2) SRAM
#define CART_DOM1_ROM   0x10000000 // Cart domain 1 address 2
#define CART_DOM1_ADDR2 0x10000000 // $10000000..$18000803 Cartridge Domain 1(Address 2) ROM
#define CART_DOM1_ADDR3 0x1FD00000 // $1FD00000..$7FFFFFFF Cartridge Domain 1 (Address 3)

#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>

/* Call before writing any PI register (except PI_STATUS) */
static inline void pi_wait() {
    while(*PI_STATUS & (PI_IO_BUSY|PI_DMA_BUSY)) {}
}

void dma_rom_to_dram(void *dest, const void *src, uint32_t size);

#endif

#endif
