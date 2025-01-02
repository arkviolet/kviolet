#!/bin/bash

set -ex

mkdir -vp ~/package/
mkdir -vp ~/software/

sudo apt-get update

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

sudo apt-get install gcc g++ -y

sudo apt-get install redis-tools redis-server -y

sudo apt-get install cmake make automake autoconf -y

sudo apt-get install libgflags-dev libgoogle-glog-dev -y

sudo apt-get install libatlas-base-dev libsuitesparse-dev -y

sudo apt-get install gfortran libgtk-3-dev -y

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

sudo apt-get install libgoogle-glog-dev libgflags-dev -y

sudo apt-get install minicom -y

sudo apt-get install yakuake guake -y

sudo apt-get install htop atop iotop -y

sudo apt-get install lsof dstat sysstat -y

sudo apt-get install linux-tools-common linux-tools-generic linux-tools-$(uname -r)

sudo apt-get install libdwarf-dev -y

sudo apt-get install libperl libperl-dev -y

sudo apt-get install libdwarf-freebsd-dev -y

sudo apt-get install systemtap-sdt-dev -y

sudo apt-get install libaudit-dev -y

sudo apt-get install libdw-dev -y

sudo apt-get install libslang2-dev -y

sudo apt-get install libgtk2.0-dev -y

sudo apt-get install libunwind-dev -y

sudo apt-get install binutils-dev -y

sudo apt-get install libiberty-dev -y

sudo apt-get install libelf-dev -y

sudo apt-get install fuse libfuse-dev -y

sudo apt-get install python2-dev python3-dev -y

sudo apt-get install ffmpeg -y

sudo apt-get install pulseaudio libpulse-dev -y

sudo apt-get install pulseaudio:arm64 libpulse-dev:arm64 -y

sudo apt-get install libsndfile-dev libsndfile1 -y

sudo apt-get install protobuf-compiler-grpc libgrpc++-dev -y

sudo apt-get install libsystemd-dev -y

sudo apt-get install libboost-all-dev libprocess-cpp-dev -y

sudo apt-get install libsdbus-c++ libsdbus-c++-dev libdbus-1-dev -y

sudo apt-get install libgstreamer1.0-dev gstreamer1.0-rtsp -y

sudo apt-get install cutecom -y

# mqtt                  https://github.com/emqx/MQTTX/releases/tag/v1.10.0
# BloomRPC              https://github.com/bloomrpc/bloomrpc/releases
# grpcurl               https://github.com/fullstorydev/grpcurl/releases
# mqtt ca_certificates  https://github.com/owntracks/tools/blob/master/TLS/generate-CA.sh
# vpn software          https://github.com/2dust/v2rayN/releases/download/6.21/v2rayN-With-Core.zip

# perf
mkdir -vp ~/workspace && cd ~/workspace
wget http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/v4.x/linux-4.9.xxx.tar.gz  #需要与当前内核版本相对对应
tar -zxvf linux-4.9.xxx.tar.gz
cd linux-4.9.xxx/tools/perf/
make -j4

#
# python3 pip3
#
  if [ ! -d ~/.pip/ ]; then
    mkdir -p ~/.pip/
    chmod 755 -R ~/.pip/
  fi

  sh -c 'echo "[global]\nindex-url = https://pypi.tuna.tsinghua.edu.cn/simple" >~/.pip/pip.conf'
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
