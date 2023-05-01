# Install script for directory: /home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so"
         RPATH "/usr/local/lib:/usr/local/lib64")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib64/libkvioletd.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib64" TYPE SHARED_LIBRARY FILES "/home/kviolet/workspace/tinytoolkit/kviolet/cmake-build-debug/lib/libkvioletd.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so"
         OLD_RPATH ":::::::::::::::::::::::::::::::"
         NEW_RPATH "/usr/local/lib:/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib64/libkvioletd.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib64/libkvioletd.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib64" TYPE STATIC_LIBRARY FILES "/home/kviolet/workspace/tinytoolkit/kviolet/cmake-build-debug/lib/libkvioletd.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/kviolet/actor/active.h;/usr/local/include/kviolet/actor/actor.h;/usr/local/include/kviolet/actor/actorface.h;/usr/local/include/kviolet/actor/event.h;/usr/local/include/kviolet/actor/lockqueue.h;/usr/local/include/kviolet/actor/node.h;/usr/local/include/kviolet/actor/statemachine.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/kviolet/actor" TYPE PROGRAM FILES
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/active.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/actor.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/actorface.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/event.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/lockqueue.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/node.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/actor/statemachine.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/kviolet/common/common.h;/usr/local/include/kviolet/common/define.h;/usr/local/include/kviolet/common/definecpp.h;/usr/local/include/kviolet/common/include.h;/usr/local/include/kviolet/common/procotol.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/kviolet/common" TYPE PROGRAM FILES
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/common/common.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/common/define.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/common/definecpp.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/common/include.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/common/procotol.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/kviolet/efficient/annularcache.h;/usr/local/include/kviolet/efficient/efficient.h;/usr/local/include/kviolet/efficient/instwlinklist.h;/usr/local/include/kviolet/efficient/twlinklist.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/kviolet/efficient" TYPE PROGRAM FILES
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/efficient/annularcache.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/efficient/efficient.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/efficient/instwlinklist.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/efficient/twlinklist.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/kviolet/utilities/filesystem.h;/usr/local/include/kviolet/utilities/math.h;/usr/local/include/kviolet/utilities/net.h;/usr/local/include/kviolet/utilities/string.h;/usr/local/include/kviolet/utilities/time.h;/usr/local/include/kviolet/utilities/utilities.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/kviolet/utilities" TYPE PROGRAM FILES
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/utilities/filesystem.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/utilities/math.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/utilities/net.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/utilities/string.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/utilities/time.h"
    "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/utilities/utilities.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/kviolet/kviolet.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/kviolet" TYPE PROGRAM FILES "/home/kviolet/workspace/tinytoolkit/kviolet/project/kviolet/kviolet.h")
endif()

