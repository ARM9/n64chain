/*
 * Linker script for RSP.
 */

OUTPUT_FORMAT("elf32-bigmips")
OUTPUT_ARCH(mips)

EXTERN(_start)
ENTRY(_start)

MEMORY {
    dram : ORIGIN = 0x0000, LENGTH = 0x1000
    iram : ORIGIN = 0x1000, LENGTH = 0x1000
}

SECTIONS {
    . = ORIGIN(iram);

    __text_start = .;
    .text : {
        *(.text)
        *(.text.*)
        /* limits size to 0x1000 but also pads to 0x1000 */
        /*. = 0x1000;*/
    } > iram
    __text_end = .;
    
    __iram_lma_start = LOADADDR (.text);
    __iram_lma_end = LOADADDR (.text) + SIZEOF (.text);

    /* there's no read only memory */
    /DISCARD/ : { *(.rodata .rodata.* .rdata .rdata.*) }

    . = ORIGIN(dram);

    __data_start = .;
    .data : AT (ADDR (.text) + SIZEOF (.text)) {
        *(.data)
        *(.data.*)
        /**(.rodata .rodata.* .rdata .rdata.*)*/
    } > dram
    .sdata : AT (ADDR (.data) + SIZEOF (.data)) {
        *(.sdata)
        *(.sdata.*)
    } > dram
    __data_end = .;

    __bss_start = .;
    .sbss NOLOAD : {
        *(.sbss .sbss.*)
        *(.scommon)
    } > dram
    .bss NOLOAD : {
        *(.bss .bss.*)
        *(COMMON)
    } > dram
    . = ALIGN(16);
    __bss_end = .;

    __dram_lma_start = LOADADDR (.data);
    __dram_lma_end = LOADADDR (.data) + __data_end - __data_start;

    ucode_end = __dram_lma_end;

    /DISCARD/ : { *(.MIPS.abiflags) }
}

