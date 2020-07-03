cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME SERVPOLLECHO)

# 添加动态或者静态链接库路径
link_directories(${PROJECT_BINARY_DIR}/lib)
link_directories(${PROJECT_BINARY_DIR}/install/lib)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR}/install/include)

set(EXTRA_LIBS  ${EXTRA_LIBS}  "libunp.a")
# ======================================================
# 自动包含当前目录代码文件
set(UNP_TCP_ECHO_SERV_FILE "tcppollechoserv.cc")

# 生成可执行文件
add_executable(tcpserv_poll_echo_exe ${UNP_TCP_ECHO_SERV_FILE})

# 链接库文件
target_link_libraries(tcpserv_poll_echo_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS tcpserv_poll_echo_exe DESTINATION bin)
