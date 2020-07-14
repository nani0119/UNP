cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME LIB)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# ======================================================

set(FILES_LIST 
        "unp.cc"
        "error.cc"
        "sock_ntop.cc"
        "wrapsock.cc"
        "wrapunix.cc"
        "wraplib.cc"
        "wrapstdio.cc"
        "writen.cc"
        "str_echo.cc"
        "str_cli.cc"
        "readline.cc"
        "signal.cc"
        "sockfd_to_family.cc"
        "dg_cli.cc"
        "dg_echo.cc"
        "host_serv.cc"
        "tcp_connect.cc"
        "tcp_listen.cc"
        "udp_client.cc"
        "udp_connect.cc"
        "udp_server.cc"
        "read_fd.cc"
        "write_fd.cc"
)

# 自动包含当前目录代码文件
# aux_source_directory(. DIR_SRCS)
set(UNP_COMMON_LIB_FILE ${FILES_LIST})

# 生成动态库
add_library(unp SHARED ${UNP_COMMON_LIB_FILE})

# 设置动态版本，VERSION指代动态库版本，SOVERSION指代API版本
# set_target_properties(unp PROPERTIES VERSION 1.0 SOVERSION 1)

# 生成静态库
add_library(unp_static STATIC ${UNP_COMMON_LIB_FILE})

# 设置静态库与动态库输出同名
set_target_properties (unp_static PROPERTIES OUTPUT_NAME "unp")

# 安装设置
install(FILES unp.h DESTINATION include)
install(TARGETS unp unp_static LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
