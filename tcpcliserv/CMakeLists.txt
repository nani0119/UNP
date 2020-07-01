cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME TCPCLISERV)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/echo)

# 添加子目录
add_subdirectory(echo)


