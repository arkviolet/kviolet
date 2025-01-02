CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)

PROJECT(kviolet)

SET(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/cmake/check
        ${CMAKE_SOURCE_DIR}/cmake/traverse)

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

TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()
