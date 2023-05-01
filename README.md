The kviolet C++ Project
====================================================
## 
## 主要借鉴hm大佬c++ tinyToolkit
## 


##
## 开发机器：x86 Ubuntu 20.4/22.4
## 开发板: Ubuntu 20.4,Android,rk3308
##

## 1. 环境

* Ubuntu    -   20.4
* Rk3308    -   arm64
* Android   -   arm64

## 2. 下载

### 2.1 安装依赖：

安装依赖：

```bash
#
# 安装编译环境,依赖库,调试工具
#

$ sudo ./install_env_ubuntu.sh 

```

### 2.2 下载

```bash

$ cd ~ && mkdir workspace && cd ~/workspace/
$ 
$ https://github.com/arkviolet/kviolet.git

```

## 3. 编译

```bash

$./compile_linux.sh
$
$./compile_android.sh
$
$./compile_rk3308.sh

```

####
```text
├── compile_android.sh              #android 编译脚本
├── compile_linux.sh                #linux 编译脚本
├── compile_rk3308.sh               #rk3308 编译脚本
├── install_env_centos.sh           
├── install_env_ubuntu.sh           #开发机环境
├── kslam                           #视觉slam框架
├── vslam                           #激光slam框架
├── softwore                        #测试代码
├── kviolet                         #c++ sdk
├── README.md               

```