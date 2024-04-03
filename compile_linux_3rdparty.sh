#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

# 编译安装路径
INSTALL_PREFIX_LINUX=/home/${USER}/software/3rdparty

# grpc
cd ~/workspace/

git clone --recurse-submodules -b v1.56.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc

cd grpc && mkdir build && cd build && cmake .. \
  -DgRPC_INSTALL=ON \
  -DgRPC_BUILD_TESTS=OFF \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/grpc

make -j && make install
