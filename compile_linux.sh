#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

# 编译安装路径
TOOLKIT_INSTALL_PREFIX_LINUX=/home/${USER}/software/kviolet

cd $sourcePath/kviolet

rm -rf build && mkdir build && cd build && cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_LINUX}

make -j8 && make install
