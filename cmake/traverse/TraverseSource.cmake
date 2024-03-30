#
# 遍历递归指定目录获取源文件, RECURSE_DIRECTORY_SOURCE_FILE(arg path)
#
MACRO(RECURSE_DIRECTORY_SOURCE_FILE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 2)

		MESSAGE(FATAL_ERROR "There is two and only two parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取源文件
	#
	FILE(GLOB_RECURSE ${ARGV0}	"${ARGV1}/*.c"
								"${ARGV1}/*.cc"
								"${ARGV1}/*.cpp"
								"${ARGV1}/*.h"
								"${ARGV1}/*.hh"
								"${ARGV1}/*.hpp")

ENDMACRO(RECURSE_DIRECTORY_SOURCE_FILE)


#
# 遍历递归当前目录获取源文件, RECURSE_CURRENT_DIRECTORY_SOURCE_FILE(arg)
#
MACRO(RECURSE_CURRENT_DIRECTORY_SOURCE_FILE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "There is one and only one parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取源文件
	#
	RECURSE_DIRECTORY_SOURCE_FILE(${ARGV0} ${CMAKE_CURRENT_LIST_DIR})

ENDMACRO(RECURSE_CURRENT_DIRECTORY_SOURCE_FILE)


####################################################################################################


#
# 遍历指定目录获取源文件, TRAVERSE_DIRECTORY_SOURCE_FILE(arg path)
#
MACRO(TRAVERSE_DIRECTORY_SOURCE_FILE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 2)

		MESSAGE(FATAL_ERROR "There is two and only two parameter")

	ENDIF()

	#
	# 遍历指定目录获取源文件
	#
	FILE(GLOB ${ARGV0}	"${ARGV1}/*.c"
						"${ARGV1}/*.cc"
						"${ARGV1}/*.cpp"
						"${ARGV1}/*.h"
						"${ARGV1}/*.hh"
						"${ARGV1}/*.hpp")

ENDMACRO(TRAVERSE_DIRECTORY_SOURCE_FILE)


#
# 遍历当前目录获取源文件, TRAVERSE_CURRENT_DIRECTORY_SOURCE_FILE(arg)
#
MACRO(TRAVERSE_CURRENT_DIRECTORY_SOURCE_FILE)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "There is one and only one parameter")

	ENDIF()

	#
	# 遍历指定目录获取源文件
	#
	TRAVERSE_DIRECTORY_SOURCE_FILE(${ARGV0} ${CMAKE_CURRENT_LIST_DIR})

ENDMACRO(TRAVERSE_CURRENT_DIRECTORY_SOURCE_FILE)