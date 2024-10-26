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

#
#   __FILE__ 只显示文件名
#
FUNCTION(REDEFINE_FILE_MACRO targetname)

	GET_TARGET_PROPERTY(source_files "${targetname}" SOURCES)                           #获取当前目标的所有源文件

	FOREACH (sourcefile ${source_files})                                                #遍历源文件

		GET_PROPERTY(defs SOURCE "${sourcefile}" PROPERTY COMPILE_DEFINITIONS)          #获取当前源文件的编译参数

		GET_FILENAME_COMPONENT(filepath "${sourcefile}" ABSOLUTE)                       #获取当前文件的绝对路径

		STRING(REGEX REPLACE ".*/" "" relpath ${filepath})                              #替换绝对路径中前缀

		LIST(APPEND defs "__FILE__=\"${relpath}\"")                                     #将我们要加的编译参数(__FILE__定义)添加到原来的编译参数里面

		SET_PROPERTY(SOURCE "${sourcefile}" PROPERTY COMPILE_DEFINITIONS ${defs} )       #重新设置源文件的编译参数

	ENDFOREACH ()

ENDFUNCTION()