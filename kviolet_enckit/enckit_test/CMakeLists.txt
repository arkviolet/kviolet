SET(PROGRAM_NAME enckit_test)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

RECURSE_CURRENT_DIRECTORY_SOURCE_FILE(SOURCE_FILES)

ADD_EXECUTABLE(${PROGRAM_NAME} ${SOURCE_FILES})

TRAVERSE_LIBRARY_FOR_PROGRAM_NAME(kviolet kviolet_enckit)

REDEFINE_FILE_MACRO(${PROGRAM_NAME})                                                    #添加启动项目

ADD_DEFINITIONS(-Wno-builtin-macro-redefined)                                           #修改预设宏 消除警告
