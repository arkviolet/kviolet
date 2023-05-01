#!/bin/bash

#
#   适用环境  centos6 centos7
#

source /etc/profile

CPU=-j4

LONGBIT_VERSION=$(getconf LONG_BIT)

#yum
if [ ${LONGBIT_VERSION} == "32" ]; then

  rpm -Uvh http://mirrors.ustc.edu.cn/epel/6/i386/Packages/e/epel-release-6-8.noarch.rpm

  rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-6

  sed -i 'N;8a\priority=11' /etc/yum.repos.d/epel.repo

  yum makecache

elif [ ${LONGBIT_VERSION} == "64" ]; then

  rpm -Uvh http://mirrors.ustc.edu.cn/epel/6/x86_64/Packages/e/epel-release-6-8.noarch.rpm

  rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-6

  sed -i 'N;8a\priority=11' /etc/yum.repos.d/epel.repo

  yum makecache

fi

yum upgrade -y

yum install ibus* -y

yum install squid -y

yum install pam-devel openldap-devel cyrus-sasl-devel openssl-devel -y

yum install gcc gcc-c++ glibc-static glibc-devel gflags gflags-devel zlib-devel unzip -y

yum install python python-devel python-pip python34 python34-devel python34-pip libtool -y

yum install curl libcurl libcurl-devel boost boost-devel boost-doc openssl-devel libgcrypt-devel -y

yum install qtwebkit qt-devel qtwebkit-devel qt5-qtwebkit qt5-qtwebkit-devel qt5-qttools qt5-qttools-devel -y

rpm -ivh http://repo.mysql.com/mysql-community-release-el6-5.noarch.rpm && yum install mysql-community-server mysql-community-devel -y




yum install git gitk gitg -y

yum install curl wget net-tools -y

yum install -y http://mirror.centos.org/centos/7/extras/x86_64/Packages/centos-release-scl-rh-2-3.el7.centos.noarch.rpm -y

yum install -y http://mirror.centos.org/centos/7/extras/x86_64/Packages/centos-release-scl-2-3.el7.centos.noarch.rpm -y

yum install devtoolset-9-gcc-c++ -y

source /opt/rh/devtoolset-9/ #刷新cc版本

