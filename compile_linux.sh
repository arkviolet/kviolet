#!/usr/bin/env bash


#
# 脚本路径
#
sourcePath=$(cd $(dirname $0) && pwd)


#
# 编译安装路径
#
TOOLKIT_INSTALL_PREFIX_LINUX=/home/${USER}/software/kviolet

#
# Linux 创建并进入目录
#
cd ${sourcePath}/tinyToolkit/3rd/fmt

mkdir build_linux && cd build_linux

#
# 生成make
#
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

#
# 编译安装
#

make -j8 && make install

#
# Linux 创建并进入目录
#

cd ${sourcePath}/tinyToolkit

mkdir build_linux && cd build_linux

#
# 生成make
#
cmake ../ \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

#
# 编译安装
#
make -j8 && make install

#
# Linux 创建并进入目录
#
cd ${sourcePath}/tinyToolkit-extra

mkdir build_linux && cd build_linux

#
# 生成make
#
cmake ../ \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

#
# 编译安装
#
make -j8 && make install
