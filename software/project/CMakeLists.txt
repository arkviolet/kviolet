#
# kviolet
#
TRAVERSE_LIBRARY_DIRECTORIES(/home/$ENV{USER}/software/kviolet/lib64)
INCLUDE_DIRECTORIES(AFTER SYSTEM /home/$ENV{USER}/software/kviolet/include)

INCLUDE_DIRECTORIES(AFTER SYSTEM /usr/include/glib-2.0)
INCLUDE_DIRECTORIES(AFTER SYSTEM /usr/include/gstreamer-1.0)
INCLUDE_DIRECTORIES(AFTER SYSTEM /usr/lib/x86_64-linux-gnu/glib-2.0/include/)


#
# 遍历当前目录添加项目
#
TRAVERSE_CURRENT_DIRECTORY_ADD_PROJECT()