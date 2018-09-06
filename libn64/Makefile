#
# libn64/Makefile: Makefile for libn64.
#
# n64chain: A (free) open-source N64 development toolchain.
# Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
#
# This file is subject to the terms and conditions defined in
# 'LICENSE', which is part of this source code package.
#

ifdef SystemRoot
FIXPATH := $(subst /,\,$1)
RM := del /Q
else
FIXPATH = $1
RM := rm -f
endif

SDK_DIR := $(call FIXPATH,$(CURDIR)/../tools)
N64_GCC_PREFIX := $(call FIXPATH,$(SDK_DIR)/bin/mips64-elf-)

AS  := $(N64_GCC_PREFIX)as
AR  := $(N64_GCC_PREFIX)ar
CC  := $(N64_GCC_PREFIX)gcc
CXX := $(N64_GCC_PREFIX)g++

CFLAGS   := -Wall -Wextra -pedantic -fno-builtin -nostdinc -I. -Iinclude
CXXFLAGS := $(CFLAGS) -std=c++14 -fno-rtti -fno-exceptions
CFLAGS   += -std=c99
OPTFLAGS := -O2 -march=vr4300 -mabi=o64 -mlong32 -flto -ffat-lto-objects \
	-mgpopt -G8 -mno-extern-sdata

ASMFILES := $(call FIXPATH,\
	libc/crt0.S \
)

CFILES := $(call FIXPATH,\
	libc/math.c \
	libc/time.c \
	libc/stdlib.c \
	libc/string.c \
	rcp/pi.c \
	rcp/rdp.c \
	rcp/vi.c \
	vr4300/cache.c \
)

#CXXFILES := $(call FIXPATH,\
	#cxx/cxxabi.cpp \
	#cxx/alloc.cpp \
#)

OBJFILES := \
	$(ASMFILES:.S=.o) \
	$(CFILES:.c=.o) \
	$(CXXFILES:.cpp=.o)

DEPFILES := $(OBJFILES:.o=.d)

#
# Primary targets.
#
libn64.a: $(OBJFILES)
	@echo $(call FIXPATH,"Building: libn64/$@")
	@$(AR) rcs $@ $^

#
# Generic compilation/assembly targets.
#
%.o: %.S
	@echo $(call FIXPATH,"Assembling: libn64/$<")
	@$(CC) $(CFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

%.o: %.c
	@echo $(call FIXPATH,"Compiling: libn64/$<")
	@$(CC) $(CFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

%.o: %.cpp
	@echo $(call FIXPATH,"Compiling: libn64/$<")
	@$(CXX) $(CXXFLAGS) $(OPTFLAGS) -MMD -c $< -o $@
#
# Clean project target.
#
.PHONY: clean
clean:
	@echo "Cleaning libn64..."
	@$(RM) libn64.a $(DEPFILES) $(OBJFILES)

