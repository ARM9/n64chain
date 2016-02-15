//
// cubedemo/src/main.c: Rotating cube demo (entry point).
//
// n64chain: A (free) open-source N64 development toolchain.
// Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#include "src/graphics.h"

#include <stddef.h>
#include <stdint.h>

#include <rcp/mi.h>
#include <rcp/rsp.h>
#include <rcp/vi.h>
#include <vr4300/cp0.h>

//
// Application layout:
//
// Bank 1: 0x0000 0000 -> 0x000F FFFF ( ROM CODE/DATA )
// Bank 2: 0x0010 0000 -> 0x001F FFFF ( FRAMEBUFFER A )
// Bank 3: 0x0020 0000 -> 0x002F FFFF ( FRAMEBUFFER B )
// Bank 4: 0x0030 0000 -> 0x003F FFFF (STACK/MISC DATA)
//

// Application entry point.
int main() {
  uintptr_t ucode_addr;

  // Put RSP into a known state.
  while (rsp_is_dma_pending());

  rsp_set_status(
    RSP_STATUS_SET_HALT |
    RSP_STATUS_CLEAR_BROKE |
    RSP_STATUS_CLEAR_INTR |
    RSP_STATUS_CLEAR_SSTEP |
    RSP_STATUS_SET_INTR_ON_BREAK |
    RSP_STATUS_CLEAR_SIGNAL_0 |
    RSP_STATUS_CLEAR_SIGNAL_1 |
    RSP_STATUS_CLEAR_SIGNAL_2 |
    RSP_STATUS_CLEAR_SIGNAL_3 |
    RSP_STATUS_CLEAR_SIGNAL_4 |
    RSP_STATUS_CLEAR_SIGNAL_5 |
    RSP_STATUS_CLEAR_SIGNAL_6 |
    RSP_STATUS_CLEAR_SIGNAL_7
  );

  // DMA the ucode into the RSP.
  ucode_addr = (uintptr_t) &rsp_ucode & 0x03EFFFFF;

  rsp_issue_dma_to_rsp(ucode_addr + 0x0000, 0x0000, 0x1000 - 0x1);
  while (rsp_is_dma_pending());

  rsp_issue_dma_to_rsp(ucode_addr + 0x1000, 0x1000, 0x1000 - 0x1);
  while (rsp_is_dma_pending());

  vi_state_t vi_state;
  vi_setup_res(VI_RES_320x240, &vi_state);
  vi_state.status |= (VI_BPP16 | GAMMA_DITHER_EN | GAMMA_EN | INTERLACE | AA_MODE_2);
  vi_state.origin = 0x00100000;

  // Enable the VI.
  vi_flush_state(&vi_state);

  // Start the RSP.
  rsp_set_pc(0x0000);
  rsp_set_status(RSP_STATUS_CLEAR_HALT);

  // Configure and enable interrupts.
  mi_set_intr_mask(
    MI_INTR_CLEAR_SP |
    MI_INTR_CLEAR_SI |
    MI_INTR_CLEAR_AI |
    MI_INTR_CLEAR_PI |
    MI_INTR_CLEAR_DP |
    MI_INTR_SET_VI
  );

  vr4300_install_interrupt_handler((uintptr_t) &__interrupt_handler);
  vr4300_cp0_enable_interrupts();

  // We'll just spin indefinitely after returning...
  //
  // Occasionally, a VI interrupt will be raised, and
  // __interrupt_handler in src/graphics.S will be
  // invoked... but other than that, we're done.
  return 0;
}

