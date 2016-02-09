#
# cubedemo/src/graphics.S: RSP microcode for cubedemo.
#
# n64chain: A (free) open-source N64 development toolchain.
# Copyright 2014 Tyler J. Stachecki <tstache1@binghamton.edu>
#
# This file is subject to the terms and conditions defined in
# 'LICENSE', which is part of this source code package.
#

#include "vr4300/cp0.h"
#include "rcp/mi.h"
#include "rcp/vi.h"

#define MI_INTR_VI 0x08

.file "src/graphics.S"
.section .rodata
.align 3

.global rsp_ucode
.type rsp_ucode, @object

rsp_ucode:
.incbin "src/graphics.bin"
.size rsp_ucode,.-rsp_ucode

#
# Invoked on interrupt.
#
.text
.set noreorder
.global __interrupt_handler
.type __interrupt_handler, @function
__interrupt_handler:

  # TODO Preserve registers

  mfc0 $k0, CP0_CAUSE
  andi $k1, $k0, CP0_CAUSE_EXCEPTION
  beqz $k1, __interrupt_handler_maybe_pre_nmi_interrupt
  nop

  # TODO Critical Exception Failure
  nop

__interrupt_handler_maybe_pre_nmi_interrupt:
  andi $k1, $k0, CP0_CAUSE_PRENMI
  beqz $k1, __interrupt_handler_maybe_count_interrupt
  nop

  # TODO Pre-Reset Interrupt Handler
  nop

__interrupt_handler_maybe_count_interrupt:
  andi $k1, $k0, CP0_CAUSE_TIMER
  beqzl $k1, __interrupt_handler_maybe_vi_interrupt
  mtc0 $0, CP0_COMPARE

  # TODO Timer Interrupt Handler
  nop

__interrupt_handler_maybe_vi_interrupt:
  # Determine interrupt reason.
  #
  # If MI status VI interrupt bit is set, swap the framebuffer.
  # If MI status VI interrupt bit is not set, just clear the exception.
  li $k0, MI_BASE
  lw $k1, MI_INTR($k0)
  andi $k1, $k1, MI_INTR_VI
  beqz $k1, __interrupt_handler_finish
  nop

__interrupt_handler_determine_framebuffer:
  # Set VI origin to the second frame.
  #
  # If VI_ORIGIN_REG is 0x0010 0000, set it to 0x0020 0000.
  # If VI_ORIGIN_REG is 0x0020 0000, set it to 0x0010 0000.
  li $k0, VI_BASE
  lw $k1, VI_ORIGIN($k0)
  srl $k1, $k1, 0x15

  beql $k1, $0, __interrupt_handler_set_framebuffer
  ori $k1, $0, 0x2

__interrupt_handler_set_framebuffer:
  sll $k1, $k1, 0x14
  sw $k1, VI_ORIGIN($k0)

  # Clear the pending VI interrupt.
  sw $0, VI_V_CURRENT_LINE($k0)

__interrupt_handler_finish:
  # Clear exception level and return.
  mfc0 $k0, CP0_STATUS
  xor $k0, $k0, CP0_STATUS_EXCEPTION
  mtc0 $k0, CP0_STATUS
  eret

.set reorder

.size __interrupt_handler,.-__interrupt_handler

