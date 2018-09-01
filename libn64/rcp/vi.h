//
// libn64/rcp/vi.h: Video interface helper functions.
//
// n64chain: A (free) open-source N64 development toolchain.
// Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#ifndef LIBN64_RCP_VI_H
#define LIBN64_RCP_VI_H

#include <mmio.h>

/* Video interface registers */
#define VI_BASE 0xA4400000 // $04400000..$04400037 Video Interface (VI) Base Register
#define VI_STATUS   IO_32(VI_BASE,0x00) // $04400000..$04400003 VI: Status/Control Register
#define VI_ORIGIN   IO_32(VI_BASE,0x04) // $04400004..$04400007 VI: Origin Register
#define VI_WIDTH    IO_32(VI_BASE,0x08) // $04400008..$0440000B VI: Width Register
#define VI_V_INTR   IO_32(VI_BASE,0x0C) // $0440000C..$0440000F VI: Vertical Interrupt Register
#define VI_V_CURRENT_LINE   IO_32(VI_BASE,0x10) // $04400010..$04400013 VI: Current Vertical Line Register
#define VI_TIMING   IO_32(VI_BASE,0x14) // $04400014..$04400017 VI: Video Timing Register
#define VI_V_SYNC   IO_32(VI_BASE,0x18) // $04400018..$0440001B VI: Vertical Sync Register
#define VI_H_SYNC   IO_32(VI_BASE,0x1C) // $0440001C..$0440001F VI: Horizontal Sync Register
#define VI_H_SYNC_LEAP  IO_32(VI_BASE,0x20) // $04400020..$04400023 VI: Horizontal Sync Leap Register
#define VI_H_VIDEO  IO_32(VI_BASE,0x24) // $04400024..$04400027 VI: Horizontal Video Register
#define VI_V_VIDEO  IO_32(VI_BASE,0x28) // $04400028..$0440002B VI: Vertical Video Register
#define VI_V_BURST  IO_32(VI_BASE,0x2C) // $0440002C..$0440002F VI: Vertical Burst Register
#define VI_X_SCALE  IO_32(VI_BASE,0x30) // $04400030..$04400033 VI: X-Scale Register
#define VI_Y_SCALE  IO_32(VI_BASE,0x34) // $04400034..$04400037 VI: Y-Scale Register

#define VI_BPP0     0x0000 // VI Status/Control: Color Depth Blank (No Data Or Sync) (Bit 0..1)
#define VI_BPP16    0x0002 // VI Status/Control: Color Depth 16BPP R5/G5/B5/A1 (Bit 0..1)
#define VI_BPP32    0x0003 // VI Status/Control: Color Depth 32BPP R8/G8/B8/A8 (Bit 0..1)
#define GAMMA_DITHER_EN 0x00004 // VI Status/Control: Gamma Dither Enable (Requires: Gamma Enable) (Bit 2)
#define GAMMA_EN    0x00008 // VI Status/Control: Gamma Enable (Gamma Boost For YUV Images) (Bit 3)
#define DIVOT_EN    0x00010 // VI Status/Control: Divot Enable (Used With Anti-alias) (Bit 4)
#define VBUS_CLK_EN 0x00020 // VI Status/Control: Video Bus Clock Enable (Bit 5)
#define INTERLACE   0x00040 // VI Status/Control: Interlace/Serrate (Used With Interlaced Display) (Bit 6)
#define TST_MODE    0x00080 // VI Status/Control: Test Mode (Bit 7)
#define AA_MODE_0   0x00000 // VI Status/Control: AA Mode 0 = Anti­-alias & Resample (Always Fetch Extra Lines) (Bit 8..9)
#define AA_MODE_1   0x00100 // VI Status/Control: AA Mode 1 = Anti­-alias & Resample (Fetch Extra Lines When Needed) (Bit 8..9)
#define AA_MODE_2   0x00200 // VI Status/Control: AA Mode 2 = Resample Only (Bit 8..9)
#define AA_MODE_3   0x00300 // VI Status/Control: AA Mode 3 = Replicate Pixels & No Interpolation (Bit 8..9)
#define DIAG_0      0x00400 // VI Status/Control: Diagnostic 0 (Bit 10..11)
#define DIAG_1      0x00800 // VI Status/Control: Diagnostic 1 (Bit 10..11)
#define PIXEL_ADV_0 0x00000 // VI Status/Control: Pixel Advance 0 (Bit 12..15)
#define PIXEL_ADV_1 0x01000 // VI Status/Control: Pixel Advance 1 (Bit 12..15)
#define PIXEL_ADV_2 0x02000 // VI Status/Control: Pixel Advance 2 (Bit 12..15)
#define PIXEL_ADV_3 0x03000 // VI Status/Control: Pixel Advance 3 (Bit 12..15)
#define PIXEL_ADV_4 0x04000 // VI Status/Control: Pixel Advance 4 (Bit 12..15)
#define PIXEL_ADV_5 0x05000 // VI Status/Control: Pixel Advance 5 (Bit 12..15)
#define PIXEL_ADV_6 0x06000 // VI Status/Control: Pixel Advance 6 (Bit 12..15)
#define PIXEL_ADV_7 0x07000 // VI Status/Control: Pixel Advance 7 (Bit 12..15)
#define PIXEL_ADV_8 0x08000 // VI Status/Control: Pixel Advance 8 (Bit 12..15)
#define PIXEL_ADV_9 0x09000 // VI Status/Control: Pixel Advance 9 (Bit 12..15)
#define PIXEL_ADV_A 0x0A000 // VI Status/Control: Pixel Advance A (Bit 12..15)
#define PIXEL_ADV_B 0x0B000 // VI Status/Control: Pixel Advance B (Bit 12..15)
#define PIXEL_ADV_C 0x0C000 // VI Status/Control: Pixel Advance C (Bit 12..15)
#define PIXEL_ADV_D 0x0D000 // VI Status/Control: Pixel Advance D (Bit 12..15)
#define PIXEL_ADV_E 0x0E000 // VI Status/Control: Pixel Advance E (Bit 12..15)
#define PIXEL_ADV_F 0x0F000 // VI Status/Control: Pixel Advance F (Bit 12..15)
#define DITHER_FILTER_EN 0x10000 // VI Status/Control: Dither Filter Enable (Used With 16BPP Display) (Bit 16)

#define VI_NTSC_CLOCK   48681812 // NTSC: Hz = 48.681812 MHz
#define VI_PAL_CLOCK    49656530 // PAL:  Hz = 49.656530 MHz
#define VI_MPAL_CLOCK   48628316 // MPAL: Hz = 48.628316 MHz

#ifndef __LANGUAGE_ASSEMBLY
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vi_state_t {
	uint32_t status;   // Status and control register
	uint32_t origin;   // Pointer to uncached buffer in memory to rasterize
	uint32_t width;    // Width of the buffer in pixels
	uint32_t intr;     // Vertical interrupt control register
	uint32_t current;  // Current vertical line counter
	uint32_t burst;    // Timing generation register for PAL/NTSC
	uint32_t v_sync;   // Number of lines per frame
	uint32_t h_sync;   // Number of pixels in the line
	uint32_t leap;     // Leap pattern (used by PAL)
	uint32_t h_start;  // Beginning of video horizontally
	uint32_t v_start;  // Beginning of video vertically
	uint32_t v_burst;  // Beginning of color burst in vertical lines
	uint32_t x_scale;  // Horizontal scaling factor from buffer to screen
	uint32_t y_scale;  // Vertical scaling factor from buffer to screen
} vi_state_t __attribute__ ((aligned (8)));

//
// Flushes the register data to hardware registers.
//
// - Caller is responsible for disabling interrupts.
// - state _must_ pointed to cached memory (mapped or not).
//
static inline void vi_flush_state(const vi_state_t *state) {
  uint32_t vi_region = VI_BASE;
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

//
// Pre-defined video modes for NTSC, PAL, and MPAL
//
typedef enum
{
    VI_RES_320x240,
    VI_RES_640x480,
    VI_RES_256x240,
    VI_RES_512x480
} vi_resolution_t;

//
// Sets the register data for a given resolution
//
// Will select the appropriate settings based on detected TV mode
//
void vi_setup_res(vi_resolution_t res, vi_state_t *out);

void vi_wait_scanline (unsigned line);

#ifdef __cplusplus
}
#endif

#endif

#endif

