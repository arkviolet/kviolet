#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

# 设置平台
PLATFORM_TYPE=x86_64

# 编译安装路径
TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/toolkit/$PLATFORM_TYPE

cd $sourcePath/kviolet

rm -rf build_$PLATFORM_TYPE && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX

make -j && make install

cd $sourcePath/kviolet_enckit

rm -rf build && mkdir build && cd build && cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX \
  -DPLATFORM_TYPE=$PLATFORM_TYPE


#########################################################################

# Allwinner h3 r258
# https://releases.linaro.org/components/toolchain/binaries/5.5-2017.10/arm-linux-gnueabihf/
# https://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabihf/

PLATFORM_TYPE=linaro_arm

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/toolkit/$PLATFORM_TYPE

cd $sourcePath/kviolet

rm -rf build_$PLATFORM_TYPE && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX \
  -DCMAKE_TOOLCHAIN_FILE=$sourcePath/cmakemoudes/linaro_arm.cmake

make -j && make install

######################################################################################

#
# Rockchip
# rk3568
PLATFORM_TYPE=rk3568

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/toolkit/$PLATFORM_TYPE

cd $sourcePath/kviolet

rm -rf build_$PLATFORM_TYPE && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX \
  -DCMAKE_TOOLCHAIN_FILE=$sourcePath/cmakemoudes/rk3568.cmake
  #-DCMAKE_TOOLCHAIN_FILE=/opt/rk3568-toolchain/share/buildroot/toolchainfile.cmake

make -j && make install
