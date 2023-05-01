#
# 检测系统
#
IF (WIN32 AND MINGW)

	MESSAGE(STATUS "Detected Mingw System")

ELSEIF (WIN32 AND NOT MINGW)

	MESSAGE(STATUS "Detected Windows System")

ELSEIF (APPLE)

	MESSAGE(STATUS "Detected Apple System")

ELSEIF (UNIX AND NOT ANDROID)

	MESSAGE(STATUS "Detected Unix System")

ELSEIF (ANDROID)

	MESSAGE(STATUS "Detected Android System")

ENDIF()