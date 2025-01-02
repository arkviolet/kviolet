#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

##########################################################################
PLATFORM_TYPE=x86_64

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/software/toolkit/$PLATFORM_TYPE

cd $sourcePath/toolkit/kviolet

rm -rf build_$PLATFORM_TYPE && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX

make -j && make install

cd $sourcePath/toolkit/kviolet_enckit

rm -rf build && mkdir build && cd build && cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX \
  -DPLATFORM_TYPE=$PLATFORM_TYPE


#########################################################################
PLATFORM_TYPE=linaro_arm

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/software/toolkit/$PLATFORM_TYPE

cd $sourcePath/toolkit/kviolet

rm -rf build_$PLATFORM_TYPE && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX \
  -DCMAKE_TOOLCHAIN_FILE=$sourcePath/linux_crosss_env/linaro_arm.cmake

make -j && make install

######################################################################################

# rk3568
PLATFORM_TYPE=rk3568

TOOLKIT_INSTALL_PREFIX_LINUX=$sourcePath/software/toolkit/$PLATFORM_TYPE

cd $sourcePath/toolkit/kviolet

rm -rf build_$PLATFORM_TYPE && mkdir build_$PLATFORM_TYPE && cd build_$PLATFORM_TYPE

cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=$TOOLKIT_INSTALL_PREFIX_LINUX \
  -DCMAKE_TOOLCHAIN_FILE=$sourcePath/linux_crosss_env/rk3568.cmake

make -j && make install
