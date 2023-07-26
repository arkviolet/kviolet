#
# kviolet
#
TRAVERSE_LIBRARY_DIRECTORIES(/home/$ENV{USER}/software/kviolet/lib64)
INCLUDE_DIRECTORIES(AFTER SYSTEM /home/$ENV{USER}/software/kviolet/include)

#
# 遍历当前目录添加项目
#
TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()