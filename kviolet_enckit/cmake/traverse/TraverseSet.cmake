#
# 包含多个设置, TRAVERSE_SET(target name1 name2 ...)
#
MACRO(TRAVERSE_SET)

	#
	# 检测参数个数
	#
	IF(${ARGC} LESS 2)

		MESSAGE(FATAL_ERROR "Has and is greater than two parameter")

	ENDIF()

	#
	# 遍历参数
	#
	FOREACH(param ${ARGN})

		#
		# 判断是否为第一个参数
		#
		IF (NOT (${param} STREQUAL ${ARGV0}))

			#
			# 包含设置
			#
			SET(${ARGV0} "${${ARGV0}} ${param}")

		ENDIF()

	ENDFOREACH()

ENDMACRO(TRAVERSE_SET)
