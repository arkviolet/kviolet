SET(SDK_PATH "/opt/rk3568/aarch64-linux-gcc-v12.3/")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})






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


set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_SYSTEM_NAME linux)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_C_COMPILER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-gcc")
set(CMAKE_CXX_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -g0 -D_FORTIFY_SOURCE=1" CACHE STRING "Buildroot CXXFLAGS")
set(CMAKE_CXX_COMPILER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-g++")

set(CMAKE_AR "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-ar")
set(CMAKE_AS "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-as")
set(CMAKE_LINKER "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-ld")
set(CMAKE_NM "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-nm")
set(CMAKE_RANLIB "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-ranlib")
set(CMAKE_READELF "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-readelf")
set(CMAKE_STRIP "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-strip")
set(CMAKE_OBJCOPY "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-objcopy")
set(CMAKE_OBJDUMP "${SDK_PATH}/bin/aarch64-buildroot-linux-gnu-objdump")
