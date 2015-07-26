#!/bin/bash
set -e

#
# tools/build-linux-toolchain.sh: Linux toolchain build script.
#
# n64chain: A (free) open-source N64 development toolchain.
# Copyright 2014-15 Tyler J. Stachecki <tstache1@binghamton.edu>
#
# This file is subject to the terms and conditions defined in
# 'LICENSE', which is part of this source code package.
#

BINUTILS="ftp://ftp.gnu.org/gnu/binutils/binutils-2.25.tar.bz2"
GCC="ftp://ftp.gnu.org/gnu/gcc/gcc-5.2.0/gcc-5.2.0.tar.bz2"

export PATH="${PATH}:${SCRIPT_DIR}/bin"

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${SCRIPT_DIR} && mkdir -p {stamps,tarballs}

if [ ! -f stamps/binutils-download ]; then
  wget "${BINUTILS}" -O "tarballs/$(basename ${BINUTILS})"
  touch stamps/binutils-download
fi

if [ ! -f stamps/binutils-extract ]; then
  mkdir -p binutils-{build,source}
  tar -xf tarballs/$(basename ${BINUTILS}) -C binutils-source --strip 1
  touch stamps/binutils-extract
fi

if [ ! -f stamps/binutils-configure ]; then
  pushd binutils-build
  ../binutils-source/configure \
    --prefix="${SCRIPT_DIR}" \
    --with-lib-path="${SCRIPT_DIR}/lib" \
    --target=mips64-elf --with-arch=vr4300 \
    --enable-64-bit-bfd \
    --enable-gold \
    --enable-plugins \
    --enable-static \
    --disable-multilib \
    --disable-nls \
    --disable-shared \
    --disable-werror
  popd

  touch stamps/binutils-configure
fi

if [ ! -f stamps/binutils-build ]; then
  pushd binutils-build
  make
  popd

  touch stamps/binutils-build
fi

if [ ! -f stamps/binutils-install ]; then
  pushd binutils-build
  make install
  popd

  touch stamps/binutils-install
fi

if [ ! -f stamps/gcc-download ]; then
  wget "${GCC}" -O "tarballs/$(basename ${GCC})"
  touch stamps/gcc-download
fi

if [ ! -f stamps/gcc-extract ]; then
  mkdir -p gcc-{build,source}
  tar -xf tarballs/$(basename ${GCC}) -C gcc-source --strip 1
  touch stamps/gcc-extract
fi

if [ ! -f stamps/gcc-configure ]; then
  pushd gcc-build
  ../gcc-source/configure \
    --prefix="${SCRIPT_DIR}" \
    --target=mips64-elf --with-arch=vr4300 \
    --enable-languages=c --without-headers --with-newlib \
    --with-gnu-as=${SCRIPT_DIR}/bin/mips64-elf-as \
    --with-gnu-ld=${SCRIPT_DIR}/bin/mips64-elf-ld \
    --enable-checking=release \
    --disable-decimal-float \
    --disable-libatomic \
    --disable-libgomp \
    --disable-libitm \
    --disable-libquadmath \
    --disable-libquadmath-support \
    --disable-libsanitizer \
    --disable-libssp \
    --disable-multilib \
    --disable-nls \
    --disable-shared \
    --disable-threads \
    --disable-win32-registry \
    --enable-gold \
    --enable-lto \
    --enable-plugin \
    --enable-static \
    --without-included-gettext
  popd

  touch stamps/gcc-configure
fi

if [ ! -f stamps/gcc-build ]; then
  pushd gcc-build
  make
  popd

  touch stamps/gcc-build
fi

if [ ! -f stamps/gcc-install ]; then
  pushd gcc-build
  make install
  popd

  # build-win32-toolchain.sh needs this; the cross-compiler build
  # will look for mips64-elf-cc and we only have mips64-elf-gcc.
  pushd "${SCRIPT_DIR}/bin"
  ln -sfv mips64-elf-{gcc,cc}
  popd

  touch stamps/gcc-install
fi

if [ ! -f stamps/checksum-build ]; then
  cc -Wall -Wextra -pedantic -std=c99 -static checksum.c -o bin/checksum

  touch stamps/checksum-build
fi

rm -rf "${SCRIPT_DIR}"/../tools/tarballs
rm -rf "${SCRIPT_DIR}"/../tools/*-source
rm -rf "${SCRIPT_DIR}"/../tools/*-build
rm -rf "${SCRIPT_DIR}"/../tools/stamps
exit 0

