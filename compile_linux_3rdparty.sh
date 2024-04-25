#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

# patche目录
GIT_PATCHE_DIR=$sourcePath/patches

# 编译安装路径
INSTALL_PREFIX_LINUX=/home/${USER}/software/3rdparty

# 3rd 编译目录
PACKAGE_COMPILE_DIR=~/workspace/package

# grpc
cd $PACKAGE_COMPILE_DIR

git clone --recurse-submodules -b v1.56.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

cd grpc && mkdir build && cd build && cmake .. \
  -DgRPC_INSTALL=ON \
  -DgRPC_BUILD_TESTS=OFF \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/grpc

make -j && make install

# dbus-cpp
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/lib-cpp/dbus-cpp.git

cd dbus-cpp && git checkout a0fc0e0 && git apply -p1 --ignore-space-change --whitespace=nowarn $GIT_PATCHE_DIR/dbus-cpp.patche

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/dbus-cpp

make -j && make install

# dfu-util
cd $PACKAGE_COMPILE_DIR

git clone git://git.code.sf.net/p/dfu-util/dfu-util

cd dfu-util && git checkout v0.9 && autoreconf -v -i && ./configure --prefix=${INSTALL_PREFIX_LINUX}/dfu-util # arm:--build=x86_64-linux-gnu --host=aarch64-linux-gnu

make -j && make install
