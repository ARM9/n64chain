#
# libn64/crt0.S: C runtime library initialization.
#
# n64chain: A (free) open-source N64 development toolchain.
# Copyright 2014 Tyler J. Stachecki <tstache1@binghamton.edu>
#
# This file is subject to the terms and conditions defined in
# 'LICENSE', which is part of this source code package.
#

#
# Initialize the system, eventually invoke main().
#
.section .ipl_handoff, "ax", @progbits

.align 5
.global __ipl_handoff
.type   __ipl_handoff, @function
__ipl_handoff:

.set noat
.set noreorder

    # Prevent the PIF from resetting the console.
    addiu $a0, $zero, 8
    lui $at, 0xBFC0
    sw $a0, 0x7FC($at)

    # Setup a stack at the top of cached RAM.
    lui $at, 0x8000
    lw $at, 0x318($at)
    lui $sp, 0x8000
    daddu $sp, $sp, $at

    # Set the global pointer reference value.
    la $gp, _gp

    # Set CP0/1 usable, disable interrupts
    # and enable 64-bit modes for k/s/u.
    li $v0, 0x300004E0 | 1<<26
    mtc0 $v0, $12

    jal __init_sections
    nop
    # Clear out cause bits and jump to main.
    jal main
    mtc0 $zero, $13

    # We shouldn't get here, but just in case...
__ipl_handoff_spin:
    j __ipl_handoff_spin
    nop

__init_sections:
    la $a0, __bss_start-4
    la $a1, __bss_end
0:
    addiu $a0, 4
    bnel $a0, $a1, 0b
    sw $0, 0($a0)
    // TODO align __sbss2_end in rom.ld?
    la $a0, __sbss2_start-1
    la $a1, __sbss2_end
0:
    addiu $a0, 1
    bnel $a0, $a1, 0b
    sb $0, 0($a0)

    jr $ra
    nop

.set at
.set reorder

.size __ipl_handoff,.-__ipl_handoff

