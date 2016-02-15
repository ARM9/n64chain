#
# Makefile for n64chain ROMs.
#
# n64chain: A (free) open-source N64 development toolchain.
# Copyright 2014 Tyler J. Stachecki <tstache1@binghamton.edu>
#
# This file is subject to the terms and conditions defined in
# 'LICENSE', which is part of this source code package.
#

ifdef SystemRoot
FIXPATH = $(subst /,\,$1)
RM = del /Q
else
FIXPATH = $1
RM = rm -f
endif

ROM_NAME := $(notdir $(CURDIR))

LIBN64DIR := $(call FIXPATH,../libn64)
LIBN64 := $(call FIXPATH,$(LIBN64DIR)/libn64.a)
LDSCRIPT := $(call FIXPATH,$(LIBN64DIR)/rom.ld)
ROM_HEADER := $(call FIXPATH,$(LIBN64DIR)/header.bin)

TOOLSDIR := $(call FIXPATH,$(CURDIR)/../tools)
N64_GCC_PREFIX := $(call FIXPATH,$(TOOLSDIR)/bin/mips64-elf-)

AS := $(N64_GCC_PREFIX)as
AR := $(N64_GCC_PREFIX)ar
CC := $(N64_GCC_PREFIX)gcc
OBJCOPY := $(N64_GCC_PREFIX)objcopy

MAKE := $(call FIXPATH,$(TOOLSDIR)/bin/make)
RSPASM := $(call FIXPATH,$(TOOLSDIR)/bin/rspasm)
CHECKSUM := $(call FIXPATH,$(TOOLSDIR)/bin/checksum)

CFLAGS := -Wall -Wextra -pedantic -std=c99 \
	-I$(LIBN64DIR)/include -I$(LIBN64DIR) -I.
OPTFLAGS := -Os -march=vr4300 -flto -ffat-lto-objects \
	-mgpopt -G8 -mno-extern-sdata

ASMFILES := $(call FIXPATH,\
	src/graphics.S \
)

CFILES := $(call FIXPATH,\
	src/main.c \
)

UCODES := $(call FIXPATH,\
	src/graphics.rsp \
)

OBJFILES := \
	$(ASMFILES:.S=.o) \
	$(CFILES:.c=.o)

UCODEBINS := $(UCODES:.rsp=.bin)
DEPFILES := $(OBJFILES:.o=.d)

#
# Primary targets.
#
all: $(ROM_NAME).z64

$(ROM_NAME).z64: $(ROM_NAME).elf
	@echo $(call FIXPATH,"Building: $(ROM_NAME)/$@")
	@$(OBJCOPY) -O binary $< $@
	@$(CHECKSUM) $(ROM_HEADER) $@

#
# Link compiled targets
#
$(ROM_NAME).elf: $(LIBN64) $(OBJFILES)
	@echo $(call FIXPATH,"Building: $(ROM_NAME)/$@")
	@$(CC) $(CFLAGS) $(OPTFLAGS) -nostdlib \
		-Wl,-Map=$(ROM_NAME).map \
		-T$(LDSCRIPT) \
		-L$(LIBN64DIR) \
		-o $@ $(OBJFILES) \
		-ln64

$(LIBN64):
	@$(MAKE) -sC $(LIBN64DIR)

#
# Generic compilation/assembly targets.
#
$(call FIXPATH,src/graphics.o): $(call FIXPATH,src/graphics.S) $(call FIXPATH,src/graphics.bin)
%.o: %.S
	@echo $(call FIXPATH,"Assembling: $(ROM_NAME)/$<")
	@$(CC) $(CFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

%.o: %.c
	@echo $(call FIXPATH,"Compiling: $(ROM_NAME)/$<")
	@$(CC) $(CFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

%.bin: %.rsp
	@echo $(call FIXPATH,"Assembling: $(ROM_NAME)/$<")
	@$(RSPASM) -o $@ $<

#
# Clean project target.
#
.PHONY: clean
clean:
	@echo "Cleaning $(ROM_NAME)..."
	@$(RM) $(ROM_NAME).map $(ROM_NAME).elf $(ROM_NAME).z64 \
		$(DEPFILES) $(OBJFILES) $(UCODEBINS)

#
# Use computed dependencies.
#
-include $(DEPFILES)

