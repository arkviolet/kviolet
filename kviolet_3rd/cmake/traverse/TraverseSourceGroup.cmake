#
# 遍历递归指定目录定义源文件分组, RECURSE_DIRECTORY_SOURCE_FILE_GROUP(path)
#
MACRO(RECURSE_DIRECTORY_SOURCE_FILE_GROUP)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "There is one and only one parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取源文件
	#
	RECURSE_DIRECTORY_SOURCE_FILE(GROUP_FILES ${ARGV0})

	#
	# 遍历源文件
	#
	FOREACH(source ${GROUP_FILES})

		#
		# 获取相对路径
		#
		FILE(RELATIVE_PATH relative ${ARGV0} ${source})

		#
		# 获取组名
		#
		STRING(REGEX REPLACE "\(.*\)/.*" \\1 group ${relative})

		#
		# 判断是否为根组名
		#
		STRING(COMPARE EQUAL ${relative} ${group} rootGroup)

		#
		# 设置组名
		#
		IF (rootGroup)

			#
			# 设置根组名
			#
			SET(group "\\")

		ELSE()

			#
			# 设置子组名
			#
			STRING(REPLACE "/" "\\" group ${group})

		ENDIF()

		#
		# 把代码添加到对应的组
		#
		SOURCE_GROUP(${group} FILES ${source})

	ENDFOREACH()

ENDMACRO(RECURSE_DIRECTORY_SOURCE_FILE_GROUP)


#
# 遍历递归当前目录定义源文件分组, RECURSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP()
#
MACRO(RECURSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 0)

		MESSAGE(FATAL_ERROR "There is not need parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取源文件定义分组
	#
	RECURSE_DIRECTORY_SOURCE_FILE_GROUP(${CMAKE_CURRENT_LIST_DIR})

ENDMACRO(RECURSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP)


####################################################################################################


#
# 遍历指定目录定义源文件分组, TRAVERSE_DIRECTORY_SOURCE_FILE_GROUP(path)
#
MACRO(TRAVERSE_DIRECTORY_SOURCE_FILE_GROUP)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "There is one and only one parameter")

	ENDIF()

	#
	# 遍历指定目录获取源文件
	#
	TRAVERSE_DIRECTORY_SOURCE_FILE(GROUP_FILES ${ARGV0})

	#
	# 遍历源文件
	#
	FOREACH(source ${GROUP_FILES})

		#
		# 获取相对路径
		#
		FILE(RELATIVE_PATH relative ${ARGV0} ${source})

		#
		# 获取组名
		#
		STRING(REGEX REPLACE "\(.*\)/.*" \\1 group ${relative})

		#
		# 判断是否为根组名
		#
		STRING(COMPARE EQUAL ${relative} ${group} rootGroup)

		#
		# 设置组名
		#
		IF (rootGroup)

			#
			# 设置根组名
			#
			SET(group "\\")

		ELSE()

			#
			# 设置子组名
			#
			STRING(REPLACE "/" "\\" group ${group})

		ENDIF()

		#
		# 把代码添加到对应的组
		#
		SOURCE_GROUP(${group} FILES ${source})

	ENDFOREACH()

ENDMACRO(TRAVERSE_DIRECTORY_SOURCE_FILE_GROUP)


#
# 遍历当前目录定义源文件分组, TRAVERSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP()
#
MACRO(TRAVERSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 0)

		MESSAGE(FATAL_ERROR "There is not need parameter")

	ENDIF()

	#
	# 遍历当前目录获取源文件定义分组
	#
	TRAVERSE_DIRECTORY_SOURCE_FILE_GROUP(${CMAKE_CURRENT_LIST_DIR})

ENDMACRO(TRAVERSE_CURRENT_DIRECTORY_SOURCE_FILE_GROUP)
