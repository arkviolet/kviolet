#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

##############################################################################

# 设置平台
PLATFORM_TYPE=x86_64

# 编译安装路径
TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/toolkit/$PLATFORM_TYPE

# 第三方软件路径
PACKAGE=$sourcePath/package

mkdir -vp $PACKAGE

# fmt
cd $PACKAGE && git clone https://github.com/fmtlib/fmt

cd $PACKAGE/fmt && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}/

make -j4 && make install

##############################################################################

# Allwinner h3 r258
PLATFORM_TYPE=linaro_arm

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/toolkit/$PLATFORM_TYPE

cd $PACKAGE/fmt && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DFMT_TEST=OFF \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX} \
  -DCMAKE_TOOLCHAIN_FILE=$sourcePath/cmakemoudes/linaro_arm.cmake

make -j4 && make install

##############################################################################

# rk3568
PLATFORM_TYPE=rk3568

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/toolkit/$PLATFORM_TYPE

cd $PACKAGE/fmt && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DFMT_TEST=OFF \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX} \
  -DCMAKE_TOOLCHAIN_FILE=$sourcePath/cmakemoudes/rk3568.cmake

make -j4 && make install
