SET(PROGRAM_NAME tool_test)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(tool_test main.cpp)

target_link_libraries(tool_test kviolet)

add_library(test_generic_plug SHARED generic_plug/plug_instance.cpp)

target_link_libraries(test_generic_plug kviolet)

REDEFINE_FILE_MACRO(${PROGRAM_NAME})                                                    #添加启动项目

ADD_DEFINITIONS(-Wno-builtin-macro-redefined)                                           #修改预设宏 消除警告

ADD_EXECUTABLE(can_tool_send can_tool_send.cpp)