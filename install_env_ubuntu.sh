#!/bin/bash

#
#   适用环境  ubuntu20.4 / 22.4
#
source /etc/profile

mkdir  -p ~/package/
mkdir  -p ~/software/

SOFTWARE_PATH=~/software

# Android NDK
export ANDROID_NDK=/home/${USER}/software/android-ndk-r21e
export NDK_HOME_DIR=/home/${USER}/software/android-ndk-r21e
export ANDROID_NDK_ROOT=/home/${USER}/software/android-ndk-r21e
export ANDROID_NDK_PATH=/home/${USER}/software/android-ndk-r21e
export ANDROID_NDK_HOME=/home/${USER}/software/android-ndk-r21e


sudo sh -c 'echo "
deb http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse" >>/etc/apt/sources.list'

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install adb -y

sudo apt-get install rar -y

sudo apt-get install vim -y

sudo apt-get install tree -y

sudo apt-get install xvfb -y

sudo apt-get install wget -y

sudo apt-get install nginx -y

sudo apt-get install apt-file -y

sudo apt-get install terminator -y

sudo apt-get install imagemagick -y

sudo apt-get install libopencv-dev -y

sudo apt-get install git gitk gitg -y

sudo apt-get install openssh-server -y

sudo apt-get install libyaml-cpp-dev -y

sudo apt-get install libusb-1.0-0-dev -y

sudo apt-get install libmemcached-dev -y

sudo apt-get install libtokyocabinet-dev -y

sudo apt-get install gcc g++ gcc-10 g++-10 -y

sudo apt-get install redis-tools redis-server -y

sudo apt-get install cmake make automake autoconf -y

sudo apt-get install libgflags-dev libgoogle-glog-dev -y

sudo apt-get install libatlas-base-dev libsuitesparse-dev -y

sudo apt-get install gfortran libgtk-3-dev libavresample-dev -y

sudo apt-get install mysql-server mysql-client libmysqlcppconn-dev -y

sudo apt-get install libbz2-dev libegl1-mesa-dev libwayland-dev libxkbcommon-dev wayland-protocols -y

sudo apt-get install yasm libvpx-dev libopus-dev libfdk-aac-dev libmp3lame-dev libx265-dev libnuma-dev -y

sudo apt-get install ffmpeg libglew-dev intel-mkl-full libsuitesparse-dev libpcl-dev -y

sudo apt-get install curl -y

sudo apt-get libsqlite3-dev -y

sudo apt-get install libssl-dev -y

sudo apt-get install libglew-dev -y

sudo apt-get install python3-pip -y

sudo apt-get install libudev-dev -y

sudo apt-get install libevdev-dev -y

sudo apt-get install libcurl4-gnutls-dev  -y

sudo apt-get install docker.io docker-compose -y

sudo apt-get install libgoogle-glog-dev libgoogle-flags-dev -y

sudo apt-get install minicom -y

sudo apt-get install yakuake guake -y

sudo apt-get install jtop htop atop iotop -y

sudo apt-get install lsof pidstat mstat dstat mpstat iostat sysstat -y

sudo apt-get install linux-tools-common linux-tools-generic linux-tools-$(uname -r)

sudo apt-get install libdwarf-dev -y

sudo apt-get install libperl libperl-dev -y

sudo apt-get install libdwarf-freebsd-dev -y

sudo apt-get install systemtap-sdt-dev -y

sudo apt-get install audit-libs-dev -y

sudo apt-get install libaudit-dev -y

sudo apt-get install libdw-dev -y

sudo apt-get install libslang2-dev -y

sudo apt-get install libgtk2.0-dev -y

sudo apt-get install libiberty-dev -y

sudo apt-get install libunwind-dev -y

sudo apt-get install binutils-dev -y

sudo apt-get install libiberty-dev -y


#
# linux perf
#
sudo apt-get install libdw-dev -y
sudo apt-get install libelf-dev -y
sudo apt-get install python-dev -y
sudo apt-get install libperl-dev -y
sudo apt-get install libnuma-dev -y
sudo apt-get install binutils-dev -y
sudo apt-get install libaudit-dev -y
sudo apt-get install libgtk2.0-dev -y
sudo apt-get install libunwind-dev -y
sudo apt-get install libslang2-dev -y
sudo apt-get install libiberty-dev -y
sudo apt-get install systemtap-sdt-dev  -y

sudo apt-get install fuse libfuse-dev -y

sudo apt-get install ffmpeg -y
sudo apt-get install pulseaudio  libpulse-dev -y
sudo apt-get install pulseaudio:arm64  libpulse-dev:arm64 -y

mkdir -p  ~/workspace
cd ~/workspace
wget http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/v4.x/linux-4.9.xxx.tar.gz  #需要与当前内核版本相对对应
tar -zxvf linux-4.9.xxx.tar.gz
cd linux-4.9.xxx/tools/perf/
make -j4

#
# VPN
#
wget https://github.com/Fndroid/clash_for_windows_pkg/releases/download/0.20.22/Clash.for.Windows-0.20.22-x64-linux.tar.gz


#
# python3 pip3
#
  if [ ! -d ~/.pip/ ]; then
    mkdir -p ~/.pip/
    chmod 755 -R ~/.pip/
  fi

  echo "[global]
	index-url = https://pypi.tuna.tsinghua.edu.cn/simple" >~/.pip/pip.conf

        pip3 install --upgrade pip
        pip3 install bs4
        pip3 install ssh
        pip3 install lulu
        pip3 install xlrd
        pip3 install lxml
        pip3 install pyqt5
        pip3 install psutil
        pip3 install pandas
        pip3 install pillow
        pip3 install you-get
        pip3 install pyquery
        pip3 install pymysql
        pip3 install openpyxl
        pip3 install html5lib
        pip3 install paramiko
        pip3 install pycrypto
        pip3 install selenium
        pip3 install requests
        pip3 install FlashText
        pip3 install matplotlib
        pip3 install simplejson
        pip3 install xlsxwriter
        pip3 install sqlalchemy
        pip3 install goto-statement
        pip3 install mysql-connector
        pip3 install pyvirtualdisplay

        sudo -H pip3 install -U jetson-stats -i https://pypi.tuna.tsinghua.edu.cn/simple

#
# download android NDK21
#
    cd ~/package/ && wget https://dl.google.com/android/repository/android-ndk-r21e-linux-x86_64.zip

    unzip android-ndk-r21e-linux-x86_64.zip

    rm android-ndk-r21e-linux-x86_64.zip

    mv android-ndk-r21e ~/software/


#
# download rk3308 gcc
#
    cd ~/package/ && wget rk3308.zip

    unzip rk3308.zip

    rm rk3308.zip

    mv rk3308 ~/software/


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


#
# linux,jetbrains-toolbox
#
  cd ~/package/  && wget https://download.jetbrains.com/toolbox/jetbrains-toolbox-1.8.3678.tar.gz

  tar -xvf jetbrains-toolbox-1.8.3678.tar.gz

  rm -rf jetbrains-toolbox-1.8.3678.tar.gz

  mv jetbrains-toolbox-1.8.3678 ${SOFTWARE_PATH}/jetbrains-toolbox


#
# linux,zlog
#
  cd ~/package/ && git clone https://github.com/HardySimpson/zlog.git

  cd zlog

  make PREFIX=./zlog

  make PREFIX=${SOFTWARE_PATH}/zlog install

