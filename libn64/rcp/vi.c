#include <rcp/vi.h>

#include <string.h>

#define VI_TV_MODE IO_32(0x80000000, 0x300)

static const vi_state_t ntsc_320 = {
    0x00003000, 0x00000000, 0x00000140, 0x00000200,
    0x00000000, 0x03e52239, 0x0000020d, 0x00000c15,
    0x0c150c15, 0x006c02ec, 0x002501ff, 0x000e0204,
    0x00000200, 0x00000400
};

static const vi_state_t pal_320 = {
    0x00003000, 0x00000000, 0x00000140, 0x00000200,
    0x00000000, 0x0404233a, 0x00000271, 0x00150c69,
    0x0c6f0c6e, 0x00800300, 0x005f0239, 0x0009026b,
    0x00000200, 0x00000400
};

static const vi_state_t mpal_320 = {
    0x00003000, 0x00000000, 0x00000140, 0x00000200,
    0x00000000, 0x04651e39, 0x0000020d, 0x00040c11,
    0x0c190c1a, 0x006c02ec, 0x002501ff, 0x000e0204,
    0x00000200, 0x00000400
};

static const vi_state_t ntsc_640 = {
    0x00003040, 0x00000000, 0x00000280, 0x00000200,
    0x00000000, 0x03e52239, 0x0000020c, 0x00000c15,
    0x0c150c15, 0x006c02ec, 0x002301fd, 0x000e0204,
    0x00000400, 0x02000800
};

static const vi_state_t pal_640 = {
    0x00003040, 0x00000000, 0x00000280, 0x00000200,
    0x00000000, 0x0404233a, 0x00000270, 0x00150c69,
    0x0c6f0c6e, 0x00800300, 0x005d0237, 0x0009026b,
    0x00000400, 0x02000800
};

static const vi_state_t mpal_640 = {
    0x00003040, 0x00000000, 0x00000280, 0x00000200,
    0x00000000, 0x04651e39, 0x0000020c, 0x00000c10,
    0x0c1c0c1c, 0x006c02ec, 0x002301fd, 0x000b0202,
    0x00000400, 0x02000800
};

static const vi_state_t ntsc_256 = {
    0x00003000, 0x00000000, 0x00000100, 0x00000200,
    0x00000000, 0x03e52239, 0x0000020d, 0x00000c15,
    0x0c150c15, 0x006c02ec, 0x002501ff, 0x000e0204,
    0x0000019A, 0x00000400
};

static const vi_state_t pal_256 = {
    0x00003000, 0x00000000, 0x00000100, 0x00000200,
    0x00000000, 0x0404233a, 0x00000271, 0x00150c69,
    0x0c6f0c6e, 0x00800300, 0x005f0239, 0x0009026b,
    0x0000019A, 0x00000400
};

static const vi_state_t mpal_256 = {
    0x00003000, 0x00000000, 0x00000100, 0x00000200,
    0x00000000, 0x04651e39, 0x0000020d, 0x00040c11,
    0x0c190c1a, 0x006c02ec, 0x002501ff, 0x000e0204,
    0x0000019A, 0x00000400
};

static const vi_state_t ntsc_512 = {
    0x00003040, 0x00000000, 0x00000200, 0x00000200,
    0x00000000, 0x03e52239, 0x0000020c, 0x00000c15,
    0x0c150c15, 0x006c02ec, 0x002301fd, 0x000e0204,
    0x00000334, 0x02000800
};

static const vi_state_t pal_512 = {
    0x00003040, 0x00000000, 0x00000200, 0x00000200,
    0x00000000, 0x0404233a, 0x00000270, 0x00150c69,
    0x0c6f0c6e, 0x00800300, 0x005d0237, 0x0009026b,
    0x00000334, 0x02000800
};

static const vi_state_t mpal_512 = {
    0x00003040, 0x00000000, 0x00000200, 0x00000200,
    0x00000000, 0x04651e39, 0x0000020c, 0x00000c10,
    0x0c1c0c1c, 0x006c02ec, 0x002301fd, 0x000b0202,
    0x00000334, 0x02000800
};

static const vi_state_t * const vi_modes[] = {
    &pal_320, &ntsc_320, &mpal_320, // VI_RES_320x240
    &pal_640, &ntsc_640, &mpal_640, // VI_RES_640x480
    &pal_256, &ntsc_256, &mpal_256, // VI_RES_256x240
    &pal_512, &ntsc_512, &mpal_512  // VI_RES_512x480
};

void vi_setup_res(vi_resolution_t res, vi_state_t *out) {
    uint32_t tv_mode = *VI_TV_MODE;
    switch (res)
    {
        case VI_RES_512x480:
            tv_mode += 3;
        case VI_RES_256x240:
            tv_mode += 3;
        case VI_RES_640x480:
            tv_mode += 3;
        case VI_RES_320x240:
        default:
            break;
    }
    memcpy(out, vi_modes[tv_mode], sizeof(vi_state_t));
}

void vi_wait_scanline (unsigned line) {
    while ( *VI_V_CURRENT_LINE != line);
}

