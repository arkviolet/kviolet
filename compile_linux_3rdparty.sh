#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

# patche目录
GIT_PATCHE_DIR=$sourcePath/patches

# 编译安装路径
INSTALL_PREFIX_LINUX=/home/${USER}/software/3rdparty

# 3rd 编译目录
PACKAGE_COMPILE_DIR=~/workspace/package

mkdir -vp $PACKAGE_COMPILE_DIR

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

# srs
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/ossrs/srs

cd srs && git checkout fa8096ad0117a085515729e12a3758ca26036552

cd trunk && ./configure --prefix=${INSTALL_PREFIX_LINUX}/srs # arm:--cross-build --cc=aarch64-linux-gnu-gcc --cxx=aarch64-linux-gnu-g++ --ar=aarch64-linux-gnu-ar --ld=aarch64-linux-gnu-ld --randlib=aarch64-linux-gnu-randlib

make -j && make install

# json
cd $PACKAGE_COMPILE_DIR

git clone https://github.com/open-source-parsers/jsoncpp

cd jsoncpp && git checkout 1.8.4

mkdir build && cd build && cmake .. \
  -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX_LINUX}/jsoncpp \
  -DJSONCPP_WITH_TESTS=OFF

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

#
# compile linux/android opencv4,opencv,opencv_contrib
#
  cd ~/package/

  git clone https://github.com/opencv/opencv.git
  git clone https://github.com/opencv/opencv_contrib.git

  cd opencv && git checkout 4.3.0
  cd ~/package/opencv_contrib && git checkout 4.3.0

  #Linux
  cd ~/package/opencv && mkdir build_linux && cd build_linux

  cmake ..   -DCMAKE_BUILD_TYPE="Release" \
            -DOPENCV_EXTRA_MODULES_PATH=~/package/opencv_contrib/modules/ \
            -DCMAKE_INSTALL_PREFIX=${SOFTWARE_PATH}/opencv \
            -DWITH_XINE=ON \
            -DWITH_FFMPEG=ON \
            -DWITH_OPENGL=ON \
            -DWITH_GTK_2_X=ON \
            -DBUILD_TESTS=OFF

  make -j16 && make install

  #Andorid
  cd ~/package/opencv && mkdir build_andorid && cd build_andorid

  cmake .. -DOPENCV_EXTRA_MODULES_PATH=~/package/opencv_contrib/modules/ \
            -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
            -DCMAKE_ANDROID_NDK=$ANDROID_NDK \
            -DANDROID_NATIVE_API_LEVEL=$ANDROID_NATIVE_API \
            -DANDROID_ABI=arm64-v8a \
            -DCMAKE_BUILD_TYPE=Release  \
            -DBUILD_ANDROID_PROJECTS=OFF \
            -DBUILD_ANDROID_EXAMPLES=OFF \
            -DBUILD_DOCS=OFF \
            -DBUILD_PERF_TESTS=OFF \
            -DBUILD_TESTS=OFF \
            -DCMAKE_INSTALL_PREFIX=${SOFTWARE_PATH}/android/opencv

  make -j16 && make install

#
# compile linux/android ceres2.0
#
  cd ~/package/

  wget http://ceres-solver.org/ceres-solver-2.0.0.tar.gz

  tar -xzvf ceres-solver-2.0.0.tar.gz

  mv ceres-solver-2.0.0 ceres

  rm ceres-solver-2.0.0.tar.gz

  #
  # linux android
  #
  cd  ceres && mkdir build_linux && mkdir build_andorid

  cd build_linux

  cmake ..  \
        -DCMAKE_INSTALL_PREFIX=~/software/ceres_2 \
        -DANDROID_STL=c++_shared \
        -DCMAKE_BUILD_TYPE=Release  \
        -Wno-dev \
        -DCMAKE_C_FLAGS="-O3 -s" \
        -DCMAKE_CXX_FLAGS="-O3 -std=c++11 -s" \
        -DANDROID_STRIP_DEBUG_SYMBOLS=1 \
        -DEIGENSPARSE=ON \
        -DSCHUR_SPECIALIZATIONS=ON \
        -DCXSPARSE=OFF \
        -DSUITESPARSE=ON \
        -DMINIGLOG=OFF \
        -DGFLAGS=OFF

  make -j16 && make install

  cd build_andorid

  cmake .. \
        -DCMAKE_INSTALL_PREFIX=~/software/android/ceres_2 \
        -DANDROID_STL=c++_shared \
        -DCMAKE_BUILD_TYPE=Release  \
        -Wno-dev \
        -DCMAKE_C_FLAGS="-O3 -s" \
        -DCMAKE_CXX_FLAGS="-O3 -std=c++11 -s" \
        -DANDROID_STRIP_DEBUG_SYMBOLS=1 \
        -DEIGENSPARSE=ON \
        -DSCHUR_SPECIALIZATIONS=ON \
        -DCXSPARSE=OFF \
        -DSUITESPARSE=ON \
        -DMINIGLOG=OFF \
        -DGFLAGS=OFF \
        -DCMAKE_SYSTEM_NAME=Android \
        -DANDROID_NDK=$ANDROID_NDK \
        -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK/build/cmake/android.toolchain.cmake \
        -DANDROID_ABI=arm64-v8a \
        -DANDROID_NATIVE_API_LEVEL=$ANDROID_NATIVE_API \
        -DBUILD_SHARED_LIBS=$BUILD_SHARED_LIBS_EN \
        -DCMAKE_Fortran_COMPILER=aarch64-linux-android-gfortran \
        -DBUILD_EXAMPLES=OFF \
        -DBUILD_TESTING=OFF \
        -DBUILD_BENCHMARKS=OFF \
        -DCERES_THREADING_MODEL=CXX_THREADS

  make -j16 && make install

#
# linux key-value dataset
#
  cd ~/package/ && wget http://fallabs.com/tokyocabinet/tokyocabinet-1.4.47.tar.gz

  tar -xvf tokyocabinet-1.4.47.tar.gz

  rm -rf tokyocabinet-1.4.47.tar.gz

  mv tokyocabinet-1.4.47 tokyocabinet && cd tokyocabinet

  ./configure \
            --prefix=${SOFTWARE_PATH}/tokyocabinet

  make -j16 && make install

#
# linux,gperftools,c++14，
#
  cd ~/package/  && wget https://github.com/gperftools/gperftools/releases/download/gperftools-2.7/gperftools-2.7.tar.gz

  tar -xvf gperftools-2.7.tar.gz

  rm -rf gperftools-2.7.tar.gz

  mv gperftools-2.7 gperftools && cd gperftools

  ./configure \
        --prefix=${SOFTWARE_PATH}/gperftools \
        --enable-silent-rules \
        --enable-maintainer-mode \
        --enable-dependency-tracking \
        --enable-stacktrace-via-backtrace \
        --enable-libunwind \
        --enable-frame-pointers \
        --enable-dynamic-sized-delete-support \
        --enable-sized-delete \
        --enable-emergency-malloc

  make -j16 && make install