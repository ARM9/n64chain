//
// libn64/rcp/rdp.h: RDP macros and functions.
//
#ifndef LIBN64_RCP_RDP_H
#define LIBN64_RCP_RDP_H

#include <bitfield.h>
#include <mmio.h>

/* RDP registers */
#define DPC_BASE        0xA4100000
#define DPC_START       IO_32(DPC_BASE,0x0)
#define DPC_END         IO_32(DPC_BASE,0x4)
#define DPC_CURRENT     IO_32(DPC_BASE,0x08) // $04100008..$0410000B DPC: CMD DMA Current Register
#define DPC_STATUS      IO_32(DPC_BASE,0x0C) // $0410000C..$0410000F DPC: CMD Status Register
#define DPC_CLOCK       IO_32(DPC_BASE,0x10) // $04100010..$04100013 DPC: Clock Counter Register
#define DPC_BUFBUSY     IO_32(DPC_BASE,0x14) // $04100014..$04100017 DPC: Buffer Busy Counter Register
#define DPC_PIPEBUSY    IO_32(DPC_BASE,0x18) // $04100018..$0410001B DPC: Pipe Busy Counter Register
#define DPC_TMEM        IO_32(DPC_BASE,0x1C) // $0410001C..$0410001F DPC: TMEM Load Counter Register

#define DPS_BASE            0xA4200000 // $04200000..$0420000F DP Span (DPS) Base Register
#define DPS_TBIST           IO_32(DPS_BASE,0x00) // $04200000..$04200003 DPS: Tmem Bist Register
#define DPS_TEST_MODE       IO_32(DPS_BASE,0x04) // $04200004..$04200007 DPS: Span Test Mode Register
#define DPS_BUFTEST_ADDR    IO_32(DPS_BASE,0x08) // $04200008..$0420000B DPS: Span Buffer Test Address Register
#define DPS_BUFTEST_DATA    IO_32(DPS_BASE,0x0C) // $0420000C..$0420000F DPS: Span Buffer Test Data Register

/* RDP command macros (C and assembly compatible) */
#define set_scissor(xh, yh, f, xl, yl) 0x2D00000000000000 \
    | SetField(xh,55,44)|SetField(yh,43,32) \
    | SetField(f,25,24) \
    | SetField(xl,23,12)|SetField(yl,11,0)
#define SCISSOR_EVEN_LINES      2
#define SCISSOR_ODD_LINES       3

#define set_convert(k0, k1, k2, k3, k4, k5) 0x2C00000000000000 \
    | SetField(k0,53,45)|SetField(k1,44,36)|SetField(k2,35,27) \
    | SetField(k3,26,18)|SetField(k4,17,9)|SetField(k5,8,0)

#define set_color_image(fmt, size, width, adr) 0x3F00000000000000 \
    | SetField(fmt,55,53)|SetField(size,52,51) \
    | SetField(width,41,32)|SetField(adr,25,0)

#define IMAGE_DATA_FORMAT_RGBA  0x0
#define SIZE_OF_PIXEL_16B       0x2

#define set_blend_color(rgba) 0x3900000000000000 \
    | SetField(rgba,31,0)

#define set_env_color(r,g,b,a) 0x3B00000000000000 \
    | SetField(r,31,24)|SetField(g,23,16)|SetField(b,15,8)|SetField(a,7,0)

#define set_fill_color(c) 0x3700000000000000 | SetField(c,31,0)

#define set_fog_color(r,g,b,a) 0x3800000000000000 \
    | SetField(r,31,24)|SetField(g,23,16)|SetField(b,15,8)|SetField(a,7,0)

#define set_prim_color(min,lodf,g,b,a) 0x3A00000000000000 \
    | SetField(min,44,40)|SetField(lodf,39,32) \
    | SetField(g,23,16)|SetField(b,15,8)|SetField(a,7,0)

#define set_prim_depth(z,dz) 0x2E00000000000000 \
    | SetField(z,31,16)|SetField(dz,15,0)

#define set_texture_image(fmt,size,width,adr) 0x3D00000000000000 \
    | SetField(fmt,55,53)|SetField(size,52,51)|SetField(width,41,32) \
    | SetField(adr,25,0)

#define set_tile(fmt,size,line,tadr,tile,pal,cfg1,maskT,shiftT,cfg2,maskS,shiftS) \
    0x3500000000000000 | SetField(fmt,55,53)|SetField(size,52,51) \
    | SetField(line,49,41)|SetField(tadr,40,32)|SetField(tile,26,24) \
    | SetField(pal,23,20)|SetField(cfg1,19,18)|SetField(maskT,17,14) \
    | SetField(shiftT,13,10)|SetField(cfg2,9,8)|SetField(maskS,7,4) \
    | SetField(shiftS,3,0)

#define set_tile_size(sl,tl,tile,sh,th) 0x3200000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(th,11,0)

#define set_z_image(adr) 0x3E00000000000000 \
    | SetField(adr,25,0)

#define set_key_r(wr,cr,sr) 0x2B00000000000000 \
    | SetField(wr,27,16)|SetField(cr,15,8)|SetField(sr,7,0)

#define set_key_gb(wg,wb,cg,sg,cb,sb) 0x2A00000000000000 \
    | SetField(wg,55,44)|SetField(wb,43,32)|SetField(cg,31,24) \
    | SetField(sg,23,16)|SetField(cb,15,8)|SetField(sb,7,0)

// TODO use flags instead?
#define set_combine_mode(sub_ar0, mulr0, sub_aa0, mula0, sub_ar1, mulr1, sub_br0, sub_br1, sub_aa1, mula1, addr0, sub_ba0, adda0, addR1, sub_ba1, adda1) \
    0x3C00000000000000 | SetField(sub_ar0,55,52)|SetField(mulr0,51,47) \
    | SetField(sub_aa0,46,44)|SetField(mula0,43,41)|SetField(sub_ar1,40,37) \
    | SetField(mulr1,36,32)|SetField(sub_br0,31,28)|SetField(sub_br1,27,24) \
    | SetField(sub_aa1,23,21)|SetField(mula1,20,18)|SetField(addr0,17,15) \
    | SetField(sub_ba0,14,12)|SetField(adda0,11,9)|SetField(addR1,8,6) \
    | SetField(sub_ba1,5,3)|SetField(adda1,2,0)

#define set_other_modes(m) 0x2F00000000000000 | SetField(m,55,0)
#define ALPHA_DITHER_SEL_PATTERN 0x00000000000000   // Set_Other_Modes V1: Alpha Dither Selection Pattern (Bit 36..37)
#define ALPHA_DITHER_SEL_PATTERNB 0x00001000000000  // Set_Other_Modes V1: Alpha Dither Selection ~Pattern (Bit 36..37)
#define ALPHA_DITHER_SEL_NOISE 0x00002000000000     // Set_Other_Modes V1: Alpha Dither Selection Noise (Bit 36..37)
#define ALPHA_DITHER_SEL_NO_DITHER 0x00003000000000 // Set_Other_Modes V1: Alpha Dither Selection No Dither (Bit 36..37)
#define RGB_DITHER_SEL_MAGIC_SQUARE_MATRIX 0x00000000000000   // Set_Other_Modes V2: RGB Dither Selection Magic Square Matrix (Preferred If Filtered) (Bit 38..39)
#define RGB_DITHER_SEL_STANDARD_BAYER_MATRIX 0x00004000000000 // Set_Other_Modes V2: RGB Dither Selection Standard Bayer Matrix (Preferred If Not Filtered) (Bit 38..39)
#define RGB_DITHER_SEL_NOISE 0x00008000000000                 // Set_Other_Modes V2: RGB Dither Selection Noise (As Before) (Bit 38..39)
#define RGB_DITHER_SEL_NO_DITHER 0x0000C000000000             // Set_Other_Modes V2: RGB Dither Selection No Dither (Bit 38..39)
#define KEY_EN 0x00010000000000 // Set_Other_Modes W: Enables Chroma Keying (Bit 40)
#define CONVERT_ONE 0x00020000000000 // Set_Other_Modes X: Color Convert Texel That Was The Ouput Of The Texture Filter On Cycle0, Used To Qualify BI_LERP_1 (Bit 41)
#define BI_LERP_1 0x00040000000000 // Set_Other_Modes Y: 1=BI_LERP, 0=Color Convert Operation In Texture Filter. Used In Cycle 1 (Bit 42)
#define BI_LERP_0 0x00080000000000 // Set_Other_Modes Z: 1=BI_LERP, 0=Color Convert Operation In Texture Filter. Used In Cycle 0 (Bit 43)
#define MID_TEXEL 0x00100000000000 // Set_Other_Modes a: Indicates Texture Filter Should Do A 2x2 Half Texel Interpolation, Primarily Used For MPEG Motion Compensation Processing (Bit 44)
#define SAMPLE_TYPE 0x00200000000000 // Set_Other_Modes b: Determines How Textures Are Sampled: 0=1x1 (Point Sample), 1=2x2. Note That Copy (Point Sample 4 Horizontally Adjacent Texels) Mode Is Indicated By CYCLE_TYPE (Bit 45)
#define TLUT_TYPE 0x00400000000000   // Set_Other_Modes c: Type Of Texels In Table, 0=16b RGBA(5/5/5/1), 1=IA(8/8) (Bit 46)
#define EN_TLUT 0x00800000000000     // Set_Other_Modes d: Enable Lookup Of Texel Values From TLUT. Meaningful If Texture Type Is Index, Tile Is In Low TMEM, TLUT Is In High TMEM, And Color Image Is RGB (Bit 47)
#define TEX_LOD_EN 0x01000000000000  // Set_Other_Modes e: Enable Texture Level Of Detail (LOD) (Bit 48)
#define SHARPEN_TEX_EN 0x02000000000000 // Set_Other_Modes f: Enable Sharpened Texture (Bit 49)
#define DETAIL_TEX_EN 0x04000000000000  // Set_Other_Modes g: Enable Detail Texture (Bit 50)
#define PERSP_TEX_EN 0x08000000000000   // Set_Other_Modes h: Enable Perspective Correction On Texture (Bit 51)
#define CYCLE_TYPE_1_CYCLE 0x00000000000000 // Set_Other_Modes i: Display Pipeline Cycle Control Mode 1 Cycle (Bit 52..53)
#define CYCLE_TYPE_2_CYCLE 0x10000000000000 // Set_Other_Modes i: Display Pipeline Cycle Control Mode 2 Cycle (Bit 52..53)
#define CYCLE_TYPE_COPY 0x20000000000000    // Set_Other_Modes i: Display Pipeline Cycle Control Mode Copy (Bit 52..53)
#define CYCLE_TYPE_FILL 0x30000000000000    // Set_Other_Modes i: Display Pipeline Cycle Control Mode Fill (Bit 52..53)

#define load_block(sl,tl,tile,sh,dxt) 0x3300000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(dxt,11,0)

#define load_tile(sl,tl,tile,sh,th) 0x3400000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(th,11,0)

#define load_tlut(sl,tl,tile,sh,th) 0x3000000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(th,11,0)

#define sync_load   0x2600000000000000
#define sync_pipe   0x2700000000000000
#define sync_tile   0x2800000000000000
#define sync_full   0x2900000000000000
#define no_op       0x0000000000000000

/* Triangle coefficient commands */
#define edge_coefficients(command,mf,miplvl,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf) \
    SetField(command,61,56) \
    | SetField(mf,55,55)|SetField(miplvl,53,51)|SetField(tile,50,48) \
    | SetField(yl,45,32)|SetField(ym,29,16)|SetField(yh,13,0) \
    , SetField(xl,63,48)|SetField(xlf,47,32)|SetField(dxldy,31,16) \
    | SetField(dxldyf,15,0) \
    , SetField(xh,63,48)|SetField(xhf,47,32)|SetField(dxhdy,31,16) \
    | SetField(dxhdyf,15,0) \
    , SetField(xm,63,48)|SetField(xmf,47,32) \
    | SetField(dxmdy,31,16)|SetField(dxmdyf,15,0)

// TODO
#define shade_coefficients()
#define texture_coefficients()
#define zbuffer_coefficients()

/* Triangle raster commands */
#define fill_triangle(mf,miplvl,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf,xh,xhf,dxhdy,dxhdyf,xm,xmf,dxmdy,dxmdyf) \
    edge_coefficients(0x08,mf,miplvl,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf, xh,xhf,dxhdy,dxhdyf, xm,xmf,dxmdy,dxmdyf)
// #define TRIANGLE_BIT    0x08
// #define SHADED_BIT      0x04
// #define TEXTURED_BIT    0x02
// #define ZBUFF_BIT       0x01
//#define fill_shaded_triangle(bla) \
//    edge_coefficients(0x0C,) \
//    , shade_coefficients()
//
//#define fill_textured_triangle(bla) \
//    edge_coefficients(0x0A,) \
//    , texture_coefficients()
//
//#define fill_shaded_textured_triangle(bla) \
//    edge_coefficients(0x0E,) \
//    , shade_coefficients() \
//    , texture_coefficients()
//
//#define fill_zbuff_triangle(bla) \
//    edge_coefficients(0x09,) \
//    , zbuffer_coefficients()
//
//#define fill_shaded_zbuff_triangle(bla) \
//    edge_coefficients(0x0D,) \
//    , shade_coefficients() \
//    , zbuffer_coefficients()
//
//#define fill_textured_zbuff_triangle(bla) \
//    edge_coefficients(0x0B,) \
//    , texture_coefficients() \
//    , zbuffer_coefficients()
//
//#define fill_shaded_textured_zbuff_triangle(bla) \
//    edge_coefficients(0x0F,) \
//    , shade_coefficients() \
//    , texture_coefficients() \
//    , zbuffer_coefficients()

#define LEFT_MAJOR  0
#define RIGHT_MAJOR 1

#define fill_rectangle(x0, y0, x1, y1) 0x3600000000000000 \
    | SetField(x1,55,44)|SetField(y1,43,32) \
    | SetField(x0,23,12)|SetField(y0,11,0)

// TODO WARNING mixed info on this
#define texture_rectangle(xh,yh,tile,xl,yl,s,t,dsdx,dtdy) 0x2400000000000000 \
    | SetField(xh,55,44)|SetField(yh,43,32)|SetField(tile,26,24) \
    | SetField(xl,23,12)|SetField(yl,11,0) \
    , SetField(s,63,48)|SetField(t,47,32) \
    | SetField(dsdx,31,16)|SetField(dtdy,15,0)

#define texture_rectangle_flip(xh,yh,tile,xl,yl,s,t,dsdx,dtdy) \
    0x2500000000000000 \
    | SetField(xh,55,44)|SetField(yh,43,32)|SetField(tile,26,24) \
    | SetField(xl,23,12)|SetField(yl,11,0) \
    , SetField(s,63,48)|SetField(t,47,32) \
    | SetField(dsdx,31,16)|SetField(dtdy,15,0)

// TODO flags could be organized a bit better...
/* Flags lifted from PeterLemon/N64 */
#define ALPHA_COMPARE_EN 0x00000000000001 // Set_Other_Modes A: Conditional Color Write On Alpha Compare (Bit 0)
#define DITHER_ALPHA_EN 0x00000000000002  // Set_Other_Modes B: Use Random Noise In Alpha Compare, Otherwise Use Blend Alpha In Alpha Compare (Bit 1)
#define Z_SOURCE_SEL 0x00000000000004 // Set_Other_Modes C: Choose Between Primitive Z And Pixel Z (Bit 2)
#define ANTIALIAS_EN 0x00000000000008 // Set_Other_Modes D: If Not Force Blend, Allow Blend Enable - Use CVG Bits (Bit 3)
#define Z_COMPARE_EN 0x00000000000010 // Set_Other_Modes E: Conditional Color Write Enable On Depth Comparison (Bit 4)
#define Z_UPDATE_EN 0x00000000000020  // Set_Other_Modes F: Enable Writing Of Z If Color Write Enabled (Bit 5)
#define IMAGE_READ_EN 0x00000000000040 // Set_Other_Modes G: Enable Color/CVG Read/Modify/Write Memory Access (Bit 6)
#define COLOR_ON_CVG 0x00000000000080  // Set_Other_Modes H: Only Update Color On Coverage Overflow (Transparent Surfaces) (Bit 7)
#define CVG_DEST_CLAMP 0x00000000000000 // Set_Other_Modes I: CVG Destination Clamp (Normal) (Bit 8..9)
#define CVG_DEST_WRAP 0x00000000000100  // Set_Other_Modes I: CVG Destination Wrap (WAS Assume Full CVG) (Bit 8..9)
#define CVG_DEST_ZAP 0x00000000000200   // Set_Other_Modes I: CVG Destination Zap (Force To Full CVG) (Bit 8..9)
#define CVG_DEST_SAVE 0x00000000000300  // Set_Other_Modes I: CVG Destination Save (Don't Overwrite Memory CVG) (Bit 8..9)
#define Z_MODE_OPAQUE 0x00000000000000           // Set_Other_Modes J: Z Mode Opaque (Bit 10..11)
#define Z_MODE_INTERPENETRATING 0x00000000000400 // Set_Other_Modes J: Z Mode Interpenetrating (Bit 10..11)
#define Z_MODE_TRANSPARENT 0x00000000000800      // Set_Other_Modes J: Z Mode Transparent (Bit 10..11)
#define Z_MODE_DECAL 0x00000000000C00            // Set_Other_Modes J: Z Mode Decal (Bit 10..11)
#define CVG_TIMES_ALPHA 0x00000000001000  // Set_Other_Modes K: Use CVG Times Alpha For Pixel Alpha And Coverage (Bit 12)
#define ALPHA_CVG_SELECT 0x00000000002000 // Set_Other_Modes L: Use CVG (Or CVG*Alpha) For Pixel Alpha (Bit 13)
#define FORCE_BLEND 0x00000000004000 // Set_Other_Modes M: Force Blend Enable (Bit 14)
#define B_M2B_1_0 0x00000000000000 // Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 0, Cycle 1 (Bit 16..17)
#define B_M2B_1_1 0x00000000010000 // Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 1, Cycle 1 (Bit 16..17)
#define B_M2B_1_2 0x00000000020000 // Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 2, Cycle 1 (Bit 16..17)
#define B_M2B_1_3 0x00000000030000 // Set_Other_Modes O: Blend Modeword, Multiply 2b Input Select 3, Cycle 1 (Bit 16..17)
#define B_M2B_0_0 0x00000000000000 // Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 0, Cycle 0 (Bit 18..19)
#define B_M2B_0_1 0x00000000040000 // Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 1, Cycle 0 (Bit 18..19)
#define B_M2B_0_2 0x00000000080000 // Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 2, Cycle 0 (Bit 18..19)
#define B_M2B_0_3 0x000000000C0000 // Set_Other_Modes P: Blend Modeword, Multiply 2b Input Select 3, Cycle 0 (Bit 18..19)
#define B_M2A_1_0 0x00000000000000 // Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 0, Cycle 1 (Bit 20..21)
#define B_M2A_1_1 0x00000000100000 // Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 1, Cycle 1 (Bit 20..21)
#define B_M2A_1_2 0x00000000200000 // Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 2, Cycle 1 (Bit 20..21)
#define B_M2A_1_3 0x00000000300000 // Set_Other_Modes Q: Blend Modeword, Multiply 2a Input Select 3, Cycle 1 (Bit 20..21)
#define B_M2A_0_0 0x00000000000000 // Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 0, Cycle 0 (Bit 22..23)
#define B_M2A_0_1 0x00000000400000 // Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 1, Cycle 0 (Bit 22..23)
#define B_M2A_0_2 0x00000000800000 // Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 2, Cycle 0 (Bit 22..23)
#define B_M2A_0_3 0x00000000C00000 // Set_Other_Modes R: Blend Modeword, Multiply 2a Input Select 3, Cycle 0 (Bit 22..23)
#define B_M1B_1_0 0x00000000000000 // Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 0, Cycle 1 (Bit 24..25)
#define B_M1B_1_1 0x00000001000000 // Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 1, Cycle 1 (Bit 24..25)
#define B_M1B_1_2 0x00000002000000 // Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 2, Cycle 1 (Bit 24..25)
#define B_M1B_1_3 0x00000003000000 // Set_Other_Modes S: Blend Modeword, Multiply 1b Input Select 3, Cycle 1 (Bit 24..25)
#define B_M1B_0_0 0x00000000000000 // Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 0, Cycle 0 (Bit 26..27)
#define B_M1B_0_1 0x00000004000000 // Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 1, Cycle 0 (Bit 26..27)
#define B_M1B_0_2 0x00000008000000 // Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 2, Cycle 0 (Bit 26..27)
#define B_M1B_0_3 0x0000000C000000 // Set_Other_Modes T: Blend Modeword, Multiply 1b Input Select 3, Cycle 0 (Bit 26..27)
#define B_M1A_1_0 0x00000000000000 // Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 0, Cycle 1 (Bit 28..29)
#define B_M1A_1_1 0x00000010000000 // Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 1, Cycle 1 (Bit 28..29)
#define B_M1A_1_2 0x00000020000000 // Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 2, Cycle 1 (Bit 28..29)
#define B_M1A_1_3 0x00000030000000 // Set_Other_Modes U: Blend Modeword, Multiply 1a Input Select 3, Cycle 1 (Bit 28..29)
#define B_M1A_0_0 0x00000000000000 // Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 0, Cycle 0 (Bit 30..31)
#define B_M1A_0_1 0x00000040000000 // Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 1, Cycle 0 (Bit 30..31)
#define B_M1A_0_2 0x00000080000000 // Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 2, Cycle 0 (Bit 30..31)
#define B_M1A_0_3 0x000000C0000000 // Set_Other_Modes V: Blend Modeword, Multiply 1a Input Select 3, Cycle 0 (Bit 30..31)
// Set_Other_Modes HI Word
#define ATOMIC_PRIM 0x80000000000000 // Set_Other_Modes k: Force Primitive To Be Written To Frame Buffer Before Read Of Following Primitive

// Set_Tile: hi,lo ; Set The Tile
// Word: Set Tile Settings
// Set_Tile LO Word
#define SHIFT_S_0 0x0 // Set_Tile: Shift 0 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_1 0x1 // Set_Tile: Shift 1 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_2 0x2 // Set_Tile: Shift 2 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_3 0x3 // Set_Tile: Shift 3 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_4 0x4 // Set_Tile: Shift 4 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_5 0x5 // Set_Tile: Shift 5 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_6 0x6 // Set_Tile: Shift 6 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_7 0x7 // Set_Tile: Shift 7 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_8 0x8 // Set_Tile: Shift 8 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_9 0x9 // Set_Tile: Shift 9 Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_A 0xA // Set_Tile: Shift A Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_B 0xB // Set_Tile: Shift B Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_C 0xC // Set_Tile: Shift C Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_D 0xD // Set_Tile: Shift D Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_E 0xE // Set_Tile: Shift E Level Of Detail Shift For S Addresses (Bit 0..3)
#define SHIFT_S_F 0xF // Set_Tile: Shift F Level Of Detail Shift For S Addresses (Bit 0..3)
#define MASK_S_0 0x0 // Set_Tile: Mask 0 For Wrapping/Mirroring In S Direction, Zero = Clamp (Bit 14..17)
#define MASK_S_1 0x1 // Set_Tile: Mask 1 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_2 0x2 // Set_Tile: Mask 2 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_3 0x3 // Set_Tile: Mask 3 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_4 0x4 // Set_Tile: Mask 4 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_5 0x5 // Set_Tile: Mask 5 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_6 0x6 // Set_Tile: Mask 6 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_7 0x7 // Set_Tile: Mask 7 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_8 0x8 // Set_Tile: Mask 8 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_9 0x9 // Set_Tile: Mask 9 For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_A 0xA // Set_Tile: Mask A For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_B 0xB // Set_Tile: Mask B For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_C 0xC // Set_Tile: Mask C For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_D 0xD // Set_Tile: Mask D For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_E 0xE // Set_Tile: Mask E For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MASK_S_F 0xF // Set_Tile: Mask F For Wrapping/Mirroring In S Direction, Pass (Mask) LSBs Of S Address (Bit 4..7)
#define MIRROR_S 0x1 // Set_Tile: Mirror Enable For S Direction (Bit 8)
#define CLAMP_S 0x1  // Set_Tile:  Clamp Enable For S Direction (Bit 9)
#define SHIFT_T_0 0x0 // Set_Tile: Shift 0 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_1 0x1 // Set_Tile: Shift 1 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_2 0x2 // Set_Tile: Shift 2 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_3 0x3 // Set_Tile: Shift 3 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_4 0x4 // Set_Tile: Shift 4 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_5 0x5 // Set_Tile: Shift 5 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_6 0x6 // Set_Tile: Shift 6 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_7 0x7 // Set_Tile: Shift 7 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_8 0x8 // Set_Tile: Shift 8 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_9 0x9 // Set_Tile: Shift 9 Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_A 0xA // Set_Tile: Shift A Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_B 0xB // Set_Tile: Shift B Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_C 0xC // Set_Tile: Shift C Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_D 0xD // Set_Tile: Shift D Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_E 0xE // Set_Tile: Shift E Level Of Detail Shift For T Addresses (Bit 10..13)
#define SHIFT_T_F 0xF // Set_Tile: Shift F Level Of Detail Shift For T Addresses (Bit 10..13)
#define MASK_T_0 0x0 // Set_Tile: Mask 0 For Wrapping/Mirroring In T Direction, Zero = Clamp (Bit 14..17)
#define MASK_T_1 0x1 // Set_Tile: Mask 1 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_2 0x2 // Set_Tile: Mask 2 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_3 0x3 // Set_Tile: Mask 3 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_4 0x4 // Set_Tile: Mask 4 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_5 0x5 // Set_Tile: Mask 5 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_6 0x6 // Set_Tile: Mask 6 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_7 0x7 // Set_Tile: Mask 7 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_8 0x8 // Set_Tile: Mask 8 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_9 0x9 // Set_Tile: Mask 9 For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_A 0xA // Set_Tile: Mask A For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_B 0xB // Set_Tile: Mask B For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_C 0xC // Set_Tile: Mask C For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_D 0xD // Set_Tile: Mask D For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_E 0xE // Set_Tile: Mask E For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MASK_T_F 0xF // Set_Tile: Mask F For Wrapping/Mirroring In T Direction, Pass (Mask) LSBs Of T Address (Bit 14..17)
#define MIRROR_T 0x1 // Set_Tile: Mirror Enable For T Direction (Bit 18)
#define CLAMP_T 0x1  // Set_Tile:  Clamp Enable For T Direction (Bit 19)
#define PALETTE_0 0x0 // Set_Tile: Palette Number 0 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_1 0x1 // Set_Tile: Palette Number 1 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_2 0x2 // Set_Tile: Palette Number 2 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_3 0x3 // Set_Tile: Palette Number 3 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_4 0x4 // Set_Tile: Palette Number 4 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_5 0x5 // Set_Tile: Palette Number 5 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_6 0x6 // Set_Tile: Palette Number 6 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_7 0x7 // Set_Tile: Palette Number 7 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_8 0x8 // Set_Tile: Palette Number 8 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_9 0x9 // Set_Tile: Palette Number 9 For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_A 0xA // Set_Tile: Palette Number A For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_B 0xB // Set_Tile: Palette Number B For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_C 0xC // Set_Tile: Palette Number C For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_D 0xD // Set_Tile: Palette Number D For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_E 0xE // Set_Tile: Palette Number E For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
#define PALETTE_F 0xF // Set_Tile: Palette Number F For 4Bit Color Indexed Texels, This Number Is The MS 4Bits Of An 8Bit Index (Bit 20..23)
// Set_Tile/Set_Texture_Image/Set_Color_Image HI Word
#define SIZE_OF_PIXEL_4B 0x0  // Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 4B (Bit 51..52)
#define SIZE_OF_PIXEL_8B 0x1  // Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 8B (Bit 51..52)
#define SIZE_OF_PIXEL_16B 0x2 // Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 16B (Bit 51..52)
#define SIZE_OF_PIXEL_32B 0x3 // Set_Tile/Set_Texture_Image/Set_Color_Image: Size Of Pixel/Texel Color Element 32B (Bit 51..52)
#define IMAGE_DATA_FORMAT_RGBA 0x0       // Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format RGBA (Bit 53..55)
#define IMAGE_DATA_FORMAT_YUV 0x1        // Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format YUV (Bit 53..55)
#define IMAGE_DATA_FORMAT_COLOR_INDX 0x2 // Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format COLOR_INDX (Bit 53..55)
#define IMAGE_DATA_FORMAT_IA 0x3         // Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format IA (Bit 53..55)
#define IMAGE_DATA_FORMAT_I 0x4          // Set_Tile/Set_Texture_Image/Set_Color_Image: Image Data Format I (Bit 53..55)

/* C interface */
#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t rdp_cmd;

void run_dpc(const void *list, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif

#endif
