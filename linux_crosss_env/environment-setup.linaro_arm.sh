cat <<'EOF'
    ############################################################
    # 环境变量设置
    # CONFIGURE_FLAGS:--target=arm-linux-gnueabihf --host=arm-linux-gnueabihf --build=x86_64-pc-linux-gnu  
    # SDK_PATH: /opt/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabihf
    # BIN_PATH: /opt/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabihf/bin
    # ./configure $CONFIGURE_FLAGS --prefix=
    ############################################################
EOF

SDK_PATH=/opt/gcc-linaro-5.5.0-2017.10-x86_64_arm-linux-gnueabihf

export "AR=arm-linux-gnueabihf-ar"
export "AS=arm-linux-gnueabihf-as"
export "LD=arm-linux-gnueabihf-ld"
export "NM=arm-linux-gnueabihf-nm"
export "CC=arm-linux-gnueabihf-gcc"
#export "GCC=arm-linux-gnueabihf-gcc"
#export "CPP=arm-linux-gnueabihf-g++"
export "CXX=arm-linux-gnueabihf-g++"

export "FC=arm-linux-gnueabihf-gfortran"
export "F77=arm-linux-gnueabihf-gfortran"
export "RANLIB=arm-linux-gnueabihf-ranlib"
export "READELF=arm-linux-gnueabihf-readelf"
export "STRIP=arm-linux-gnueabihf-strip"
export "OBJCOPY=arm-linux-gnueabihf-objcopy"
export "OBJDUMP=arm-linux-gnueabihf-objdump"
export "DEFAULT_ASSEMBLER=arm-linux-gnueabihf-as"
export "DEFAULT_LINKER=arm-linux-gnueabihf-ld"

export "PKG_CONFIG=pkg-config"
export "STAGING_DIR=$SDK_PATH/sysroot"
export "INTLTOOL_PERL=/bin/perl"
export "ARCH=arm64"
export "CROSS_COMPILE=arm-linux-gnueabihf-"
export "PATH=$SDK_PATH/bin:$SDK_PATH/sbin:$PATH"
export "CONFIGURE_FLAGS=--target=arm-linux-gnueabihf --host=arm-linux-gnueabihf --build=x86_64-pc-linux-gnu  "
