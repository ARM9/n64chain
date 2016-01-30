#ifndef LIBN64_RDP_H
#define LIBN64_RDP_H

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
#define CYCLE_TYPE_FILL 0x0030000000000000

#define load_block(sl,tl,tile,sh,dxt) 0x3300000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(dxt,11,0)

#define load_tile(sl,tl,tile,sh,th) 0x3400000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(th,11,0)

#define load_tlut(sl,tl,tile,sh,th) 0x3000000000000000 \
    | SetField(sl,55,44)|SetField(tl,43,32)|SetField(tile,26,24) \
    | SetField(sh,23,12)|SetField(th,11,0)

#define sync_pipe   0x2700000000000000
#define sync_tile   0x2800000000000000
#define sync_full   0x2900000000000000
#define sync_load   0x3100000000000000
#define no_op       0x0000000000000000

/* Triangle coefficient commands */
#define edge_coefficients(xl,xlf,dxldy,dxldyf,xh,xhf,dxhdy,dxhdyf,xm,xmf,dxmdy,dxmdyf) \
    SetField(xl,63,48)|SetField(xlf,47,32)|SetField(dxldy,31,16) \
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
#define fill_triangle(mf,miplvl,tile,yl,ym,yh, xl,xlf,dxldy,dxldyf,xh,xhf,dxhdy,dxhdyf,xm,xmf,dxmdy,dxmdyf) 0x0800000000000000 \
    | SetField(mf,55,55)|SetField(miplvl,53,51)|SetField(tile,50,48) \
    | SetField(yl,45,32)|SetField(ym,29,16)|SetField(yh,13,0) \
    , edge_coefficients(xl,xlf,dxldy,dxldyf,xh,xhf,dxhdy,dxhdyf,xm,xmf,dxmdy,dxmdyf)

#define fill_rectangle(x0, y0, x1, y1) 0x3600000000000000 \
    | SetField(x1,55,44)|SetField(y1,43,32) \
    | SetField(x0,23,12)|SetField(y0,11,0)

// TODO WARNING mixed info on this
#define texture_rectangle(x0) 0x2400000000000000 \
    | SetField(x0,55,44) \
    , ()

#define texture_rectangle_flip()

/* C interface */
#ifndef __LANGUAGE_ASSEMBLY
#include <stdint.h>

typedef uint64_t rdp_cmd;

void runDPC(const void *list, uint32_t len);

#endif

#endif
