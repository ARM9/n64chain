//
// libn64/rcp/vi.h: VI helper functions.
//
// n64chain: A (free) open-source N64 development toolchain.
// Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef LIBN64_RCP_VI_H
#define LIBN64_RCP_VI_H
#include <stddef.h>
#include <stdint.h>

typedef struct vi_state_t {
	uint32_t status;
	uint32_t origin;
	uint32_t width;
	uint32_t intr;
	uint32_t current;
	uint32_t burst;
	uint32_t v_sync;
	uint32_t h_sync;
	uint32_t leap;
	uint32_t h_start;
	uint32_t v_start;
	uint32_t v_burst;
	uint32_t x_scale;
	uint32_t y_scale;
} vi_state_t __attribute__ ((aligned (8)));

//
// Flushes the register data to hardware registers.
//
// - Caller is responsible for disabling interrupts.
// - state _must_ pointed to cached memory (mapped or not).
//
static inline void vi_flush_state(const vi_state_t *state) {
  uint32_t vi_region = 0xA4400000U;
  uint32_t data, end_ptr;

  __asm__ __volatile__(
    ".set noreorder\n\t"
    "addiu %[end_ptr], %[vi_region], 0x30\n"

    "1:\n\t"
    "ld %[data], 0x30(%[state])\n\t"
    "addiu %[state], %[state], -0x8\n\t"
    "sw %[data], 0x4(%[end_ptr])\n\t"
    "dsrl32 %[data], %[data], 0x0\n\t"
    "sw %[data], 0x0(%[end_ptr])\n\t"
    "bne %[vi_region], %[end_ptr], 1b\n\t"
    "addiu %[end_ptr], %[end_ptr], -0x8\n\t"
    ".set reorder\n\t"

    : [state] "=&r" (state), [data] "=&r" (data),
      [end_ptr] "=&r" (end_ptr), [vi_region] "=&r" (vi_region)
    : "0" (state), "3" (vi_region)
  );
}

#endif

