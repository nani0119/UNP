cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME UNIXDOMAIN)

# 添加动态或者静态链接库路径
link_directories(${PROJECT_BINARY_DIR}/lib)
link_directories(${PROJECT_BINARY_DIR}/install/lib)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR}/install/include)

set(EXTRA_LIBS  ${EXTRA_LIBS}  "libunp.a")
# ======================================================
# 自动包含当前目录代码文件
set(UNP_UNIXDOMAIN_ECHO_SERV_FILE "unixstrechoserv.cc")

# 生成可执行文件
add_executable(unixdomainserv_echo_exe ${UNP_UNIXDOMAIN_ECHO_SERV_FILE})

# 链接库文件
target_link_libraries(unixdomainserv_echo_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS unixdomainserv_echo_exe DESTINATION bin)

# ======================================================
# 自动包含当前目录代码文件
set(UNP_UNIXDOMAIN_ECHO_CLI_FILE "unixstrechocli.cc")

# 生成可执行文件
add_executable(unixdomaincli_echo_exe ${UNP_UNIXDOMAIN_ECHO_CLI_FILE})

# 链接库文件
target_link_libraries(unixdomaincli_echo_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS unixdomaincli_echo_exe DESTINATION bin)
