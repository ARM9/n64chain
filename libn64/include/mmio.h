#ifndef LIBN64_MMIO_H
#define LIBN64_MMIO_H

/* IO abstraction (C and asm compatible)
 * IO_X(base,offset) returns a volatile pointer in C, just the offset in asm
 */
#ifdef __LANGUAGE_ASSEMBLY
/* only use offset in assembly definitions because of this pattern:
 *  li $t0, BASE_ADDR
 *  sw $a0, SOME_OFFSET($t0)
 *  lw $a1, SOME_OFFSET2($t0) etc.
 */
#   define IO_8(b,o)  (o)
#   define IO_16(b,o) (o)
#   define IO_32(b,o) (o)
#   define IO_64(b,o) (o)
#else
#include <stdint.h>
#   define IO_8(b,o)  ((volatile uint8_t*)((b)+(o)))
#   define IO_16(b,o) ((volatile uint16_t*)((b)+(o)))
#   define IO_32(b,o) ((volatile uint32_t*)((b)+(o)))
#   define IO_64(b,o) ((volatile uint64_t*)((b)+(o)))
#endif

#endif
