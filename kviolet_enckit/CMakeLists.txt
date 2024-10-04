CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)

PROJECT(kviolet_enckit)

SET(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/../cmake/check
        ${CMAKE_SOURCE_DIR}/../cmake/traverse)

INCLUDE(TraverseSet)
INCLUDE(TraverseSource)
INCLUDE(TraverseLibrary)
INCLUDE(TraverseInstall)
INCLUDE(TraverseInclude)
INCLUDE(TraverseCMakeLists)
INCLUDE(TraverseSourceGroup)

INCLUDE(CheckSystem)
INCLUDE(CheckPlatform)
INCLUDE(CheckCompiler)
INCLUDE(CheckBuildType)
INCLUDE(CheckGlobalType)
INCLUDE(CheckInstallPrefix)

TRAVERSE_INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/project)

TRAVERSE_INCLUDE_DIRECTORIES(
        /usr/include
        /usr/local/include
        /home/$ENV{USER}/software/kviolet/include)

TRAVERSE_LIBRARY_DIRECTORIES(
        /usr/lib
        /usr/lib64
        /usr/local/lib
        /usr/local/lib64
        /home/$ENV{USER}/software/kviolet/lib
        /home/$ENV{USER}/software/kviolet/lib64)

TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()
