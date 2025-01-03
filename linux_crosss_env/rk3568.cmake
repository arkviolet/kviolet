set(SDK_PATH /opt/sdk/rk3568/aarch64-linux-gcc-v12.3)
set(CMAKE_CURRENT_LIST_DIR ${SDK_PATH}/share/buildroot)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

if(NOT DEFINED CMAKE_SYSTEM_NAME)
  set(CMAKE_SYSTEM_NAME Buildroot)
endif()
if(NOT DEFINED CMAKE_SYSTEM_VERSION)
  set(CMAKE_SYSTEM_VERSION 1)
endif()
if(NOT DEFINED CMAKE_SYSTEM_PROCESSOR)
  set(CMAKE_SYSTEM_PROCESSOR aarch64)
endif()

if(NOT DEFINED CMAKE_C_FLAGS_DEBUG)
  set(CMAKE_C_FLAGS_DEBUG "" CACHE STRING "Debug CFLAGS")
endif()
if(NOT DEFINED CMAKE_C_FLAGS_RELEASE)
  set(CMAKE_C_FLAGS_RELEASE " -DNDEBUG" CACHE STRING "Release CFLAGS")
endif()

# Build type from the Buildroot configuration
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Buildroot build configuration")
endif()

if(NOT DEFINED CMAKE_C_FLAGS)
  set(CMAKE_C_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -g0 -D_FORTIFY_SOURCE=1" CACHE STRING "Buildroot CFLAGS")
endif()
if(NOT DEFINED CMAKE_EXE_LINKER_FLAGS)
  set(CMAKE_EXE_LINKER_FLAGS "" CACHE STRING "Buildroot LDFLAGS for executables")
endif()
if(NOT DEFINED CMAKE_SHARED_LINKER_FLAGS)
  set(CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "Buildroot LDFLAGS for shared libraries")
endif()
if(NOT DEFINED CMAKE_MODULE_LINKER_FLAGS)
  set(CMAKE_MODULE_LINKER_FLAGS "" CACHE STRING "Buildroot LDFLAGS for module libraries")
endif()

if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE 0)
endif()

if(NOT DEFINED CMAKE_PROGRAM_PATH)
  set(CMAKE_PROGRAM_PATH "${SDK_PATH}/bin")
endif()
if(NOT DEFINED CMAKE_SYSROOT)
  set(CMAKE_SYSROOT "${SDK_PATH}/aarch64-buildroot-linux-gnu/sysroot")
endif()
if(NOT DEFINED CMAKE_FIND_ROOT_PATH)
  set(CMAKE_FIND_ROOT_PATH "${SDK_PATH}/aarch64-buildroot-linux-gnu/sysroot")
endif()
if(NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_PROGRAM)
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
endif()
if(NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_PACKAGE)
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
endif()
if(NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_LIBRARY)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
endif()
if(NOT DEFINED CMAKE_FIND_ROOT_PATH_MODE_INCLUDE)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
endif()
set(ENV{PKG_CONFIG_SYSROOT_DIR} "${SDK_PATH}/aarch64-buildroot-linux-gnu/sysroot")

# This toolchain file can be used both inside and outside Buildroot.
if(NOT DEFINED CMAKE_C_COMPILER)
  set(CMAKE_C_COMPILER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-gcc")
endif()
if(1)
  if(NOT DEFINED CMAKE_CXX_FLAGS_DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "" CACHE STRING "Debug CXXFLAGS")
  endif()
  if(NOT DEFINED CMAKE_CXX_FLAGS_RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE " -DNDEBUG" CACHE STRING "Release CXXFLAGS")
  endif()
  if(NOT DEFINED CMAKE_CXX_FLAGS)
    set(CMAKE_CXX_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -g0 -D_FORTIFY_SOURCE=1" CACHE STRING "Buildroot CXXFLAGS")
  endif()
  if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-g++")
  endif()
endif()
if(0)
  if(NOT DEFINED CMAKE_Fortran_FLAGS_DEBUG)
    set(CMAKE_Fortran_FLAGS_DEBUG "" CACHE STRING "Debug Fortran FLAGS")
  endif()
  if(NOT DEFINED CMAKE_Fortran_FLAGS_RELEASE)
    set(CMAKE_Fortran_FLAGS_RELEASE " -DNDEBUG" CACHE STRING "Release Fortran FLAGS")
  endif()
  if(NOT DEFINED CMAKE_Fortran_FLAGS)
    set(CMAKE_Fortran_FLAGS "-Os -g0" CACHE STRING "Buildroot FCFLAGS")
  endif()
  if(NOT DEFINED CMAKE_Fortran_COMPILER)
    set(CMAKE_Fortran_COMPILER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-gfortran")
  endif()
endif()

# For Qt6
if(NOT DEFINED QT_HOST_PATH)
  set(QT_HOST_PATH "${SDK_PATH}")
endif()

if(NOT DEFINED QT_HOST_PATH_CMAKE_DIR)
  set(QT_HOST_PATH_CMAKE_DIR "${SDK_PATH}/lib/cmake")
endif()

set(CMAKE_AR "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-ar")
set(CMAKE_AS "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-as")
set(CMAKE_LINKER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-ld")
set(CMAKE_NM "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-nm")
set(CMAKE_RANLIB "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-ranlib")
set(CMAKE_READELF "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-readelf")
set(CMAKE_STRIP "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-strip")
set(CMAKE_OBJCOPY "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-objcopy")
set(CMAKE_OBJDUMP "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-objdump")
