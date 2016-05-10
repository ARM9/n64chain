//
// libn64/rcp/rsp.h: RSP helper functions.
//
// n64chain: A (free) open-source N64 development toolchain.
// Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef LIBN64_RCP_RSP_H
#define LIBN64_RCP_RSP_H

#include <mmio.h>

#define RSP_MEM_BASE     0xA4000000 // $04000000..$04000FFF SP MEM Base Register
#define RSP_DMEM         IO_32(RSP_MEM_BASE,0x0000) // $04000000..$04000FFF SP: RSP DMEM (4096 Bytes)
#define RSP_IMEM         IO_32(RSP_MEM_BASE,0x1000) // $04001000..$04001FFF SP: RSP IMEM (4096 Bytes)

#define RSP_BASE         0xA4040000 // $04040000..$0404001F SP Base Register
#define RSP_MEM_ADDR     IO_32(RSP_BASE,0x00) // $04040000..$04040003 SP: Master, SP Memory Address Register
#define RSP_DRAM_ADDR    IO_32(RSP_BASE,0x04) // $04040004..$04040007 SP: Slave, SP DRAM DMA Address Register
#define RSP_RD_LEN       IO_32(RSP_BASE,0x08) // $04040008..$0404000B SP: Read DMA Length Register
#define RSP_WR_LEN       IO_32(RSP_BASE,0x0C) // $0404000C..$0404000F SP: Write DMA Length Register
#define RSP_STATUS       IO_32(RSP_BASE,0x10) // $04040010..$04040013 SP: Status Register
#define RSP_DMA_FULL     IO_32(RSP_BASE,0x14) // $04040014..$04040017 SP: DMA Full Register
#define RSP_DMA_BUSY     IO_32(RSP_BASE,0x18) // $04040018..$0404001B SP: DMA Busy Register
#define RSP_SEMAPHORE    IO_32(RSP_BASE,0x1C) // $0404001C..$0404001F SP: Semaphore Register

#define RSP_PC_BASE      0xA4080000 // $04080000..$04080007 SP PC Base Register
#define RSP_PC           IO_32(RSP_PC_BASE,0x00) // $04080000..$04080003 SP: PC Register
#define RSP_IBIST_REG    IO_32(RSP_PC_BASE,0x04) // $04080004..$04080007 SP: IMEM BIST Register

#define RSP_STATUS_CLEAR_HALT               (1 <<  0)
#define RSP_STATUS_SET_HALT                 (1 <<  1)
#define RSP_STATUS_CLEAR_BROKE              (1 <<  2)
#define RSP_STATUS_CLEAR_INTR               (1 <<  3)
#define RSP_STATUS_SET_INTR                 (1 <<  4)
#define RSP_STATUS_CLEAR_SSTEP              (1 <<  5)
#define RSP_STATUS_SET_SSTEP                (1 <<  6)
#define RSP_STATUS_CLEAR_INTR_ON_BREAK      (1 <<  7)
#define RSP_STATUS_SET_INTR_ON_BREAK        (1 <<  8)
#define RSP_STATUS_CLEAR_SIGNAL_0           (1 <<  9)
#define RSP_STATUS_SET_SIGNAL_0             (1 << 10)
#define RSP_STATUS_CLEAR_SIGNAL_1           (1 << 11)
#define RSP_STATUS_SET_SIGNAL_1             (1 << 12)
#define RSP_STATUS_CLEAR_SIGNAL_2           (1 << 13)
#define RSP_STATUS_SET_SIGNAL_2             (1 << 14)
#define RSP_STATUS_CLEAR_SIGNAL_3           (1 << 15)
#define RSP_STATUS_SET_SIGNAL_3             (1 << 16)
#define RSP_STATUS_CLEAR_SIGNAL_4           (1 << 17)
#define RSP_STATUS_SET_SIGNAL_4             (1 << 18)
#define RSP_STATUS_CLEAR_SIGNAL_5           (1 << 19)
#define RSP_STATUS_SET_SIGNAL_5             (1 << 20)
#define RSP_STATUS_CLEAR_SIGNAL_6           (1 << 21)
#define RSP_STATUS_SET_SIGNAL_6             (1 << 22)
#define RSP_STATUS_CLEAR_SIGNAL_7           (1 << 23)
#define RSP_STATUS_SET_SIGNAL_7             (1 << 24)

#ifndef __LANGUAGE_ASSEMBLY
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//
// Issues a DMA to the RSP.
//
// Does NOT perform any checks. Be sure that you grab the
// semaphore as needed, adjust the length (subtract one from
// the amount you actually want copied), etc.
//
static inline void rsp_issue_dma_to_rsp(
  uint32_t paddr, uint32_t sp_addr, size_t len) {
  __asm__ __volatile__(
    "sw %[sp_addr], 0x00(%[sp_region])\n\t"
    "sw %[paddr], 0x04(%[sp_region])\n\t"
    "sw %[len], 0x08(%[sp_region])\n\t"

    :: [paddr] "r" (paddr), [sp_addr] "r" (sp_addr), [len] "r" (len),
       [sp_region] "r" (RSP_BASE)
  );
}

//
// Checks for a pending RSP DMA.
//
// Returns 1 if a DMA is pending, 0 otherwise.
//
static inline uint32_t rsp_is_dma_pending(void) {
  return *RSP_DMA_BUSY;
}

//
// Sets the RSP PC register.
//
static inline void rsp_set_pc(uint32_t pc) {
  *RSP_PC = pc;
}

//
// Updates the RSP status flags according to mask.
//
// (see RSP_STATUS_CLEAR_* and RSP_STATUS_SET_*)
//
static inline void rsp_set_status(uint32_t mask) {
  *RSP_STATUS = mask;
}

#ifdef __cplusplus
}
#endif

#endif

#endif

