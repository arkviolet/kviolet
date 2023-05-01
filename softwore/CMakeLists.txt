#
# cmake支持的最低版本
#
CMAKE_MINIMUM_REQUIRED(VERSION 3.8 FATAL_ERROR)


#
# 项目名
#
PROJECT(softwre VERSION 0.0.1)


#
# cmake模块
#
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/check
        ${CMAKE_SOURCE_DIR}/cmake/traverse)


#
# 添加cmake模块
#
INCLUDE(TraverseSet)
INCLUDE(TraverseSource)
INCLUDE(TraverseLibrary)
INCLUDE(TraverseInstall)
INCLUDE(TraverseInclude)
INCLUDE(TraverseCMakeLists)
INCLUDE(TraverseSourceGroup)


#
# 添加cmake模块
#
INCLUDE(CheckSystem)
INCLUDE(CheckPlatform)
INCLUDE(CheckCompiler)
INCLUDE(CheckBuildType)
INCLUDE(CheckGlobalType)
INCLUDE(CheckInstallPrefix)


#
# 包含多个头文件目录
#
TRAVERSE_INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/project)


#
# 添加目录
#
IF (WIN32)

    #
    # 包含多个头文件目录
    #
    TRAVERSE_INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/3rd/fmt/include)

ELSE ()

    #
    # 包含多个头文件目录
    #
    TRAVERSE_INCLUDE_DIRECTORIES(
            /usr/inlcude
            /usr/local/include)

    #
    # 包含多个连接库目录
    #
    TRAVERSE_LIBRARY_DIRECTORIES(
            /usr/lib
            /usr/lib64
            /usr/local/lib
            /usr/local/lib64)

ENDIF ()


#TRAVERSE_INCLUDE_DIRECTORIES()

#
# 遍历当前目录添加项目
#
TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()
