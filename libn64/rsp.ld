/*
 * ld script for RSP.
 */

OUTPUT_FORMAT("elf32-bigmips")
OUTPUT_ARCH(mips)

EXTERN(_start)
ENTRY(_start)

MEMORY {
    iram : ORIGIN = 0x0000, LENGTH = 0x1000
    dram : ORIGIN = 0x1000, LENGTH = 0x1000
}

SECTIONS {
    . = ORIGIN(iram);
    __text_start = .;
    .text (ALIGN(4)) : {
        *(.text)
        *(.text.*)
        . = 0x1000;
        __text_end = .;
    } > iram
    . = ALIGN(16);

    . = ORIGIN(dram);
    __data_start = .;
    .data : {
        *(.data)
        *(.data.*)
    } > dram
    .sdata : {
        *(.sdata)
        *(.sdata.*)
    } > dram
    .lit8 : {
        *(.lit8)
    } > dram
    .lit4 : {
        *(.lit4)
    } > dram
    __data_end = .;

    __bss_start = .;
    .sbss : {
        *(.sbss .sbss.*)
        *(.scommon)
    } > dram
    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } > dram
    . = ALIGN(16);
    __bss_end = .;

    _end = .;

    /DISCARD/ : { *(.MIPS.abiflags) }
}

