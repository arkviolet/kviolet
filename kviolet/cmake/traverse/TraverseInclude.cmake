#
# 包含多个头文件目录, TRAVERSE_INCLUDE_DIRECTORIES(name1 name2 ...)
#
MACRO(TRAVERSE_INCLUDE_DIRECTORIES)

	#
	# 检测参数个数
	#
	IF(${ARGC} LESS 1)

		MESSAGE(FATAL_ERROR "Has and is greater than one parameter")

	ENDIF()

	#
	# 遍历参数
	#
	FOREACH(param ${ARGN})

		#
		# 包含头文件目录
		#
		INCLUDE_DIRECTORIES(${param})

	ENDFOREACH()

ENDMACRO(TRAVERSE_INCLUDE_DIRECTORIES)


#
# 根据项目名包含多个头文件目录, TRAVERSE_INCLUDE_FOR_PROGRAM_NAME(name1 name2 ...)
#
MACRO(TRAVERSE_INCLUDE_FOR_PROGRAM_NAME)

	#
	# 检测参数个数
	#
	IF(${ARGC} LESS 1)

		MESSAGE(FATAL_ERROR "Has and is greater than one parameter")

	ENDIF()

	#
	# 遍历参数
	#
	FOREACH(param ${ARGN})

		#
		# 包含头文件目录
		#
		TARGET_INCLUDE_DIRECTORIES(${PROGRAM_NAME}	PUBLIC	${param})

	ENDFOREACH()

ENDMACRO(TRAVERSE_INCLUDE_FOR_PROGRAM_NAME)
