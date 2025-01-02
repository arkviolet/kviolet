#
# 检测系统
#
IF (UNIX AND NOT ANDROID)

	MESSAGE(STATUS "Detected Unix System")

ELSEIF (ANDROID)

	MESSAGE(STATUS "Detected Android System")

ENDIF()
