#
# 遍历递归指定目录安装头文件, TRAVERSE_INSTALL(source_dir, install_dir)
#
MACRO(TRAVERSE_INSTALL_INCLUDE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 2)

		MESSAGE(FATAL_ERROR "There is two and only two parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取头文件
	#
	FILE(GLOB INSTALL_FILES		"${ARGV0}/*.h"
								"${ARGV0}/*.hh"
								"${ARGV0}/*.hpp")

	#
	# 安装头文件到指定目录
	#
	INSTALL(PROGRAMS ${INSTALL_FILES} DESTINATION ${ARGV1})

ENDMACRO(TRAVERSE_INSTALL_INCLUDE)
