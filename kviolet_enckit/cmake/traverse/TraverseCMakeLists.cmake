#
# 遍历指定目录添加项目, TRAVERSE_DIRECTORY_ADD_PROJECT(path)
#
MACRO(TRAVERSE_DIRECTORY_ADD_PROJECT)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "There is one and only one parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取cmake文件
	#
	FILE(GLOB_RECURSE CMAKE_FILES "${ARGV0}/CMakeLists.txt")

	#
	# 遍历cmake文件
	#
	FOREACH(source ${CMAKE_FILES})

		#
		# 获取相对路径
		#
		FILE(RELATIVE_PATH relative ${ARGV0} ${source})

		#
		# 查找子目录位置
		#
		STRING(FIND ${relative} "/" subPos)

		#
		# 判断是否为根目录
		#
		IF(NOT ${subPos} EQUAL -1)

			#
			# 查找cmake文件所在位置
			#
			STRING(FIND ${relative} "/CMakeLists.txt" cmakePos)

			#
			# 判断是否为子目录的cmake文件
			#
			IF(${subPos} EQUAL ${cmakePos})

				#
				# 获取子目录名称
				#
				STRING(SUBSTRING ${relative} 0 ${subPos} folder)

				#
				# 添加下级目录
				#
				ADD_SUBDIRECTORY(${folder})

			ENDIF()

		ENDIF()

	ENDFOREACH()

ENDMACRO(TRAVERSE_DIRECTORY_ADD_PROJECT)


#
# 遍历当前目录添加项目, TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()
#
MACRO(TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 0)

		MESSAGE(FATAL_ERROR "There is not need parameter")

	ENDIF()

	#
	# 遍历指定目录添加项目
	#
	TRAVERSE_DIRECTORY_ADD_PROJECT(${CMAKE_CURRENT_LIST_DIR})

ENDMACRO(TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT)


####################################################################################################


#
# 遍历递归指定目录添加项目, RECURSE_DIRECTORY_ADD_PROJECT(path)
#
MACRO(RECURSE_DIRECTORY_ADD_PROJECT)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 1)

		MESSAGE(FATAL_ERROR "There is one and only one parameter")

	ENDIF()

	#
	# 遍历递归指定目录获取cmake文件
	#
	FILE(GLOB_RECURSE CMAKE_FILES "${ARGV0}/CMakeLists.txt")

	#
	# 遍历cmake文件
	#
	FOREACH(source ${CMAKE_FILES})

		#
		# 获取相对路径
		#
		FILE(RELATIVE_PATH relative ${ARGV0} ${source})

		#
		# 查找cmake文件所在位置
		#
		STRING(FIND ${relative} "/CMakeLists.txt" cmakePos)

		#
		# 判断是否为根目录
		#
		IF(NOT ${cmakePos} EQUAL -1)

			#
			# 获取子目录名称
			#
			STRING(SUBSTRING ${relative} 0 ${cmakePos} folder)

			#
			# 添加下级目录
			#
			ADD_SUBDIRECTORY(${folder})

		ENDIF()

	ENDFOREACH()

ENDMACRO(RECURSE_DIRECTORY_ADD_PROJECT)


#
# 遍历递归当前目录添加项目, RECURSE_CURRENT_DIRECTORY_ADD_PROJECT()
#
MACRO(RECURSE_CURRENT_DIRECTORY_ADD_PROJECT)

	#
	# 检测参数个数
	#
	IF(NOT ${ARGC} EQUAL 0)

		MESSAGE(FATAL_ERROR "There is not need parameter")

	ENDIF()

	#
	# 遍历递归指定目录添加项目
	#
	RECURSE_DIRECTORY_ADD_PROJECT(${CMAKE_CURRENT_LIST_DIR})

ENDMACRO(RECURSE_CURRENT_DIRECTORY_ADD_PROJECT)
