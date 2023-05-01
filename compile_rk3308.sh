#!/usr/bin/env bash

#
# 脚本路径
#
sourcePath=$(cd $(dirname $0) && pwd)

#
# 编译安装路径
#
TOOLKIT_INSTALL_PREFIX_RK3308=/home/${USER}/software/rk3308/kviolet/

#
# RK3308 创建并进入目录
#
cd ${sourcePath}/tinyToolkit/3rd/fmt

mkdir build_rk3308 && cd build_rk3308

#
# 生成make
#
#  rk3308.cmake
#  CMAKE_SYSTEM_PROCESSOR arm
#  CMAKE_C_COMPILER       rk3308/bin/aarch64-rockchip-linux-gnu-gcc
#  CMAKE_CXX_COMPILER     rk3308/bin/aarch64-rockchip-linux-gnu-g++
#  CMAKE_SYSROOT          rk3308/aarch64-rockchip-linux-gnu/sysroot

cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=rk3308.cmake \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_RK3308}

#

#
# 编译安装
#
make -j8 && make install
