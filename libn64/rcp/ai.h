#ifndef LIBN64_RCP_AI_H
#define LIBN64_RCP_AI_H

#include <mmio.h>

#define AI_BASE 0xA4500000 // $04500000..$04500017 Audio Interface (AI) Base Register
#define AI_DRAM_ADDR    IO_32(AI_BASE,0x00) // $04500000..$04500003 AI: DRAM Address Register
#define AI_LEN          IO_32(AI_BASE,0x04) // $04500004..$04500007 AI: Length Register
#define AI_CONTROL      IO_32(AI_BASE,0x08) // $04500008..$0450000B AI: Control Register
#define AI_STATUS       IO_32(AI_BASE,0x0C) // $0450000C..$0450000F AI: Status Register
#define AI_DACRATE      IO_32(AI_BASE,0x10) // $04500010..$04500013 AI: DAC Sample Period Register
#define AI_BITRATE      IO_32(AI_BASE,0x14) // $04500014..$04500017 AI: Bit Rate Register

#endif
