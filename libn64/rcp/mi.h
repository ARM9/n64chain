//
// libn64/rcp/mi.h: MI helper functions.
//
// n64chain: A (free) open-source N64 development toolchain.
// Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef LIBN64_RCP_MI_H
#define LIBN64_RCP_MI_H
#include <mmio.h>

#define MI_BASE 0xA4300000 // $04300000..$0430000F MIPS Interface (MI) Base Register
#define MI_INIT_MODE    IO_32(MI_BASE,0x00) // $04300000..$04300003 MI: Init Mode Register
#define MI_VERSION      IO_32(MI_BASE,0x04) // $04300004..$04300007 MI: Version Register
#define MI_INTR         IO_32(MI_BASE,0x08) // $04300008..$0430000B MI: Interrupt Register
#define MI_INTR_MASK    IO_32(MI_BASE,0x0C) // $0430000C..$0430000F MI: Interrupt Mask Register

#define MI_INTR_CLEAR_SP                    (1 <<  0)
#define MI_INTR_SET_SP                      (1 <<  1)
#define MI_INTR_CLEAR_SI                    (1 <<  2)
#define MI_INTR_SET_SI                      (1 <<  3)
#define MI_INTR_CLEAR_AI                    (1 <<  4)
#define MI_INTR_SET_AI                      (1 <<  5)
#define MI_INTR_CLEAR_VI                    (1 <<  6)
#define MI_INTR_SET_VI                      (1 <<  7)
#define MI_INTR_CLEAR_PI                    (1 <<  8)
#define MI_INTR_SET_PI                      (1 <<  9)
#define MI_INTR_CLEAR_DP                    (1 << 10)
#define MI_INTR_SET_DP                      (1 << 11)

#ifndef __LANGUAGE_ASSEMBLY
#include <stddef.h>
#include <stdint.h>
//
// Sets the MI_INTR_MASK_REG bits.
//
// (see MI_INTR_CLEAR_* and MI_INTR_SET_*)
//
static inline void mi_set_intr_mask(uint32_t mask) {
  *MI_INTR_MASK = mask;
}
#endif

#endif

