#
# 包含多个连接库目录, TRAVERSE_LIBRARY_DIRECTORIES(name1 name2 ...)
#
MACRO(TRAVERSE_LIBRARY_DIRECTORIES)

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
		# 包含连接库目录
		#
		LINK_DIRECTORIES(${param})

	ENDFOREACH()

ENDMACRO(TRAVERSE_LIBRARY_DIRECTORIES)


#
# 根据项目名链接多个动态库, TRAVERSE_LIBRARY_FOR_PROGRAM_NAME(library1 library2 ...)
#
MACRO(TRAVERSE_LIBRARY_FOR_PROGRAM_NAME)

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
		# 链接动态库
		#
		TARGET_LINK_LIBRARIES(${PROGRAM_NAME} PUBLIC ${param})

	ENDFOREACH()

ENDMACRO(TRAVERSE_LIBRARY_FOR_PROGRAM_NAME)
