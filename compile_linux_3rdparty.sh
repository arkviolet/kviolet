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

make -j4 && make install

# dbus-cpp
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/lib-cpp/dbus-cpp.git

cd dbus-cpp && git checkout a0fc0e0 && git apply -p1 --ignore-space-change --whitespace=nowarn $GIT_PATCHE_DIR/dbus-cpp.patch

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/dbus-cpp

make -j && make install

# dfu-util
cd $PACKAGE_COMPILE_DIR

git clone git://git.code.sf.net/p/dfu-util/dfu-util

cd dfu-util && git checkout v0.9
 
autoreconf -v -i &&  ./configure --prefix=${INSTALL_PREFIX_LINUX}/dfu-util # arm:--build=x86_64-linux-gnu --host=aarch64-linux-gnu

make -j && make install

# json
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/open-source-parsers/jsoncpp

cd jsoncpp && git checkout 1.8.4

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/jsoncpp \
  -DJSONCPP_WITH_TESTS=OFF

make -j && make install

# fmt
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/fmtlib/fmt.git

cd fmt && git checkout 8.0.1

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/fmt \
  -DBUILD_SHARED_LIBS=ON \
  -DFMT_TEST=OFF

make -j && make install

# yaml-cpp
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/SiriusVoyager/yaml-cpp.git

cd yaml-cpp && git checkout yaml-cpp-0.6.2

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/yaml-cpp \
  -DYAML_CPP_BUILD_TESTS=OFF \
  -DCMAKE_CXX_FLAGS=-fPIC

make -j && make install

# gflag
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/gflags/gflags.git

cd gflags && git checkout v2.2.2

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/gflags \
  -DCMAKE_CXX_FLAGS=-fPIC

make -j && make install

# glog
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/google/glog.git

cd glog && git checkout v0.5.0

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/glog

make -j && make install

# libcanard
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/UAVCAN/libcanard

cd libcanard && git checkout 54a004bd && git apply -p1 --ignore-space-change --whitespace=nowarn $GIT_PATCHE_DIR/libcanard.patch

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/libcanard \
  -DCMAKE_CXX_FLAGS=-fPIC

make -j && make install

# libusb
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/libusb/libusb.git

cd libusb && git checkout v1.0.26

autoreconf -v -i &&  ./configure --enable-udev=no --with-pic --prefix=${INSTALL_PREFIX_LINUX}/libusb 

make -j && make install
