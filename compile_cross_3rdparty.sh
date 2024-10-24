#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

GIT_PATCHE_DIR=$sourcePath/patches

# 编译安装路径
INSTALL_PREFIX_LINUX=/home/${USER}/software/kviolet_3rdparty
INSTALL_PREFIX_CROSS_LINUX=/home/${USER}/software/kviolet_cross_3rdparty

# 3rd 编译目录
PACKAGE_COMPILE_DIR=~/workspace/package/cross_3rdparty

mkdir -vp $PACKAGE_COMPILE_DIR

# grpc
cd $PACKAGE_COMPILE_DIR

git clone --recurse-submodules -b v1.50.1 --depth 1 --shallow-submodules https://github.com/grpc/grpc

cd $PACKAGE_COMPILE_DIR/grpc && mkdir build && cd build

cmake .. -DgRPC_INSTALL=ON \
         -DgRPC_BUILD_TESTS=OFF \
         -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX_LINUX/grpc

make -j8 && make install

cd $PACKAGE_COMPILE_DIR/grpc && mkdir build_rk3568 && cd build_rk3568

cmake .. -DgRPC_INSTALL=ON \
		 -DgRPC_BUILD_TESTS=OFF  \
		 -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX_CROSS_LINUX/grpc/rk3568 \
		 -DCMAKE_TOOLCHAIN_FILE=/opt/workspace/Rockchip/rk3568/aarch64-linux-gcc-v12.3/share/buildroot/toolchainfile.cmake \
		 -D_gRPC_CPP_PLUGIN=$INSTALL_PREFIX_LINUX/grpc/bin/grpc_cpp_plugin \
		 -D_gRPC_PROTOBUF_PROTOC_EXECUTABLE=$INSTALL_PREFIX_LINUX/grpc/bin/protoc

make -j8 && make install

cd $PACKAGE_COMPILE_DIR/grpc && mkdir build_h3_r258 && cd build_h3_r258

cmake .. -DgRPC_INSTALL=ON \
		 -DgRPC_BUILD_TESTS=OFF \
		 -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX_CROSS_LINUX/grpc/h3_r258 \
		 -DCMAKE_TOOLCHAIN_FILE=$sourcePath/cmakemoudes/h3_r258.cmake \
		 -D_gRPC_CPP_PLUGIN=$INSTALL_PREFIX_LINUX/grpc/bin/grpc_cpp_plugin \
		 -D_gRPC_PROTOBUF_PROTOC_EXECUTABLE=$INSTALL_PREFIX_LINUX/grpc/bin/protoc

cd $PACKAGE_COMPILE_DIR/grpc && git apply -p1 --ignore-space-change --whitespace=nowarn $GIT_PATCHE_DIR/grpc_h3_r258.patch

cd $PACKAGE_COMPILE_DIR/grpc/cd build_h3_r258

make -j8 && make install

# gdb
# Rockchip rk3568
source /opt/workspace/Rockchip/rk3568/aarch64-linux-gcc-v12.3/environment-setup
export "CONFIGURE_FLAGS=--target=aarch64-buildroot-linux-gnu --host=aarch64-buildroot-linux-gnu --build=x86_64-pc-linux-gnu"

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/gmp/gmp-6.1.2.tar.xz

tar -xvf gmp-6.1.2.tar.xz && cd gmp-6.1.2

./configure	$CONFIGURE_FLAGS \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--exec-prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--sysconfdir=/home/${USER}/software/kviolet_cross_3rdparty/gun/etc \
			--localstatedir=/home/${USER}/software/kviolet_cross_3rdparty/gun/var

make -j8 && make install

rm /home/${USER}/software/kviolet_cross_3rdparty/gun/lib/libgmp.la

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/mpfr/mpfr-4.0.1.tar.gz

tar -xvf mpfr-4.0.1.tar.gz && cd mpfr-4.0.1/

./configure $CONFIGURE_FLAGS \
			--enable-thread-safe \
			--enable-warnings \
			--with-gmp=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--exec-prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--sysconfdir=/home/${USER}/software/kviolet_cross_3rdparty/gun/etc \
			--localstatedir=/home/${USER}/software/kviolet_cross_3rdparty/gun/var

make -j8 && make install

rm /home/${USER}/software/kviolet_cross_3rdparty/gun/lib/libmpfr.la

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/mpc/mpc-1.1.0.tar.gz

tar -xvf mpc-1.1.0.tar.gz && cd mpc-1.1.0/

./configure $CONFIGURE_FLAGS \
			--with-gmp=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-mpfr=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--exec-prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--sysconfdir=/home/${USER}/software/kviolet_cross_3rdparty/gun/etc \
			--localstatedir=/home/${USER}/software/kviolet_cross_3rdparty/gun/var

make -j8 && make install

rm /home/${USER}/software/kviolet_cross_3rdparty/gun/lib/libmpc.la

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/gdb/gdb-8.1.tar.gz

tar -xvf gdb-8.1.tar.gz && cd gdb-8.1/

./configure $CONFIGURE_FLAGS \
			--with-gmp=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-mpfr=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-mpc=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--enable-host-shared \
			--enable-vtable-verify \
			--enable-lto \
			--enable-libssp \
			--enable-libada \
			--program-suffix=8.1 \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--exec-prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--sysconfdir=/home/${USER}/software/kviolet_cross_3rdparty/gun/etc \
			--localstatedir=/home/${USER}/software/kviolet_cross_3rdparty/gun/var

sed -i '179,181d' gdb/nat/linux-ptrace.h

make -j8 && make install

# gdb
# Allwinner h3_r258
export PATH=$PATH:/opt/workspace/Allwinner/h3_r258/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabihf/bin/
export "CONFIGURE_FLAGS=--host=arm-linux-gnueabihf --build=x86_64-pc-linux-gnu"
export CC="arm-linux-gnueabihf-gcc"

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/gmp/gmp-6.0.0a.tar.xz

tar -xvf gmp-6.0.0a.tar.xz && cd gmp-6.0.0

./configure	$CONFIGURE_FLAGS \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--enable-cxx \
			--enable-fft

make -j8 && make install

rm /home/${USER}/software/kviolet_cross_3rdparty/gun/lib/lib*.la

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/mpfr/mpfr-3.1.3.tar.xz

tar -xvf mpfr-3.1.3.tar.xz && cd mpfr-3.1.3/

./configure	$CONFIGURE_FLAGS \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-gmp=/home/${USER}/software/kviolet_cross_3rdparty/gun

make -j8 && make install

rm /home/${USER}/software/kviolet_cross_3rdparty/gun/lib/lib*.la

cd $PACKAGE_COMPILE_DIR

wget http://mirrors.ustc.edu.cn/gnu/mpc/mpc-1.0.3.tar.gz

tar -xvf mpc-1.0.3.tar.gz && cd mpc-1.0.3/

./configure	$CONFIGURE_FLAGS \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-gmp=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-mpfr=/home/${USER}/software/kviolet_cross_3rdparty/gun

make -j8 && make install

cd $PACKAGE_COMPILE_DIR

rm /home/${USER}/software/kviolet_cross_3rdparty/gun/lib/lib*.la

wget http://mirrors.ustc.edu.cn/gnu/gdb/gdb-8.0.tar.gz

tar -xvf gdb-8.0.tar.gz && cd gdb-8.0/

./configure $CONFIGURE_FLAGS \
			--prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-gmp=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-mpfr=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--with-mpc=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--program-suffix=8.0 \
			--with-gnu-ld \
			--enable-plugins \
			--enable-tui \
			--with-pkgversion=Linaro_GDB-2017.10 \
			--disable-gas \
			--disable-binutils \
			--disable-ld \
			--disable-gold \
			--disable-gprof \
			--without-curses \
			--enable-tui=no	\
			--exec-prefix=/home/${USER}/software/kviolet_cross_3rdparty/gun \
			--sysconfdir=/home/${USER}/software/kviolet_cross_3rdparty/gun/etc \
			--localstatedir=/home/${USER}/software/kviolet_cross_3rdparty/gun/var

make -j8 && make install

#ncurses
cd $PACKAGE_COMPILE_DIR

wget  https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.2.tar.gz

tar xvf ncurses-6.2.tar.gz && cd ncurses-6.2/

./configure $CONFIGURE_FLAGS \
            --with-shared \
		        --prefix=/home/${USER}/software/kviolet_cross_3rdparty/ncurses

make -j8 && make install
