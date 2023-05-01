#
# tinyToolkit
#
TRAVERSE_LIBRARY_DIRECTORIES(/home/$ENV{USER}/software/akviolet/tinyToolkit/lib64)
TRAVERSE_LIBRARY_DIRECTORIES(/home/$ENV{USER}/software/android/akviolet/tinyToolkit/lib64)
INCLUDE_DIRECTORIES(AFTER SYSTEM /home/$ENV{USER}/software/akviolet/tinyToolkit/include)

#
# 遍历当前目录添加项目
#
TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()