#!/usr/bin/env bash

####################################################################################################

#
# 脚本路径
#
sourcePath=$(cd $(dirname $0) && pwd)

#
# Android NDK 路径
#
ANDROID_NDK=/home/${USER}/software/android-ndk-r21e

#
# 编译安装路径
#
TOOLKIT_INSTALL_PREFIX_ANDROID=/home/${USER}/software/android/kviolet

#
# Android 创建并进入目录
#
cd ${sourcePath}/tinyToolkit/3rd/fmt

mkdir build_android && cd build_android

#
# 生成make
#
cmake .. \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_C_FLAGS=-fPIC \
  -DCMAKE_CXX_FLAGS=-fPIC \
  -DCMAKE_SYSTEM_NAME=Android \
  -DCMAKE_SYSTEM_VERSION=26 \
  -DCMAKE_ANDROID_ARCH_ABI=arm64-v8a \
  -DCMAKE_ANDROID_NDK=${ANDROID_NDK} \
  -DCMAKE_INSTALL_PREFIX=${TOOLKIT_INSTALL_PREFIX_ANDROID}

#
# 编译安装
#
make -j8 && make install
