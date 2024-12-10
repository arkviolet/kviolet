#!/usr/bin/env bash

set -ex

sourcePath=$(cd $(dirname $0) && pwd)

BINUTILS_VERSION=2.40

PACKAGE_COMPILE_DIR=$sourcePath/linux_packages
INSTALL_PREFIX_CROSS_LINUX=$sourcePath/linux_packages/install

mkdir -vp linux_packages

cd $sourcePath/linux_packages

##########################################################################################
#ncurses
# Allwinner h3_r258
export PATH=$PATH:/opt/sdk/h3/toolchains/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabihf/bin/
export "CONFIGURE_FLAGS=--host=arm-linux-gnueabihf --build=x86_64-pc-linux-gnu"
export CC="arm-linux-gnueabihf-gcc"

cd $PACKAGE_COMPILE_DIR

wget  https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.2.tar.gz

tar xvf ncurses-6.2.tar.gz && cd ncurses-6.2/

./configure $CONFIGURE_FLAGS \
    --with-shared=no \
    --prefix=$INSTALL_PREFIX_CROSS_LINUX/h3_r258/ncurses

make -j8 && make install

# procps
cd $PACKAGE_COMPILE_DIR
export NCURSES_LIBS="-L$INSTALL_PREFIX_CROSS_LINUX/h3_r258/ncurses/lib -lncurses"

git clone https://gitlab.com/procps-ng/procps.git

cd procps && ./autogen.sh 

./configure $CONFIGURE_FLAGS \
    --prefix=$INSTALL_PREFIX_CROSS_LINUX/h3_r258/procps

make -j8 && make install


##########################################################################################
# rk3568

cd $PACKAGE_COMPILE_DIR

source /opt/rk3568/aarch64-linux-gcc-v12.3/environment-setup
export "CONFIGURE_FLAGS=--target=aarch64-buildroot-linux-gnu --host=aarch64-buildroot-linux-gnu --build=x86_64-pc-linux-gnu"

cd $PACKAGE_COMPILE_DIR

git clone https://gitlab.com/procps-ng/procps.git

cd procps

./configure $CONFIGURE_FLAGS \
            --prefix=$INSTALL_PREFIX_CROSS_LINUX/rk3568/procps \
            --enable-shared=no

make -j8 && make install

cd $PACKAGE_COMPILE_DIR

wget https://fossies.org/linux/misc/minicom-2.9.tar.bz2

tar -xjvf  minicom-2.9.tar.bz2 && cd minicom-2.9/

./configure $CONFIGURE_FLAGS --prefix=$INSTALL_PREFIX_CROSS_LINUX/rk3568/minicom

make -j8 && make install
