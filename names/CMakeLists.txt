cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME NAMES)

# 添加动态或者静态链接库路径
link_directories(${PROJECT_BINARY_DIR}/lib)
link_directories(${PROJECT_BINARY_DIR}/install/lib)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR}/install/include)

set(EXTRA_LIBS  ${EXTRA_LIBS}  "libunp.a")
# ======================================================
# 自动包含当前目录代码文件
set(UNP_NAMES_HOSTENT_FILE "hostent.cc")

# 生成可执行文件
add_executable(hostent_exe ${UNP_NAMES_HOSTENT_FILE})

# 链接库文件
target_link_libraries(hostent_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS hostent_exe DESTINATION bin)

# ======================================================
# 自动包含当前目录代码文件
set(UNP_NAMES_HOSTNAME_FILE "hostname.cc")

# 生成可执行文件
add_executable(hostname_exe ${UNP_NAMES_HOSTNAME_FILE})

# 链接库文件
target_link_libraries(hostname_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS hostname_exe DESTINATION bin)
# ======================================================
# 自动包含当前目录代码文件
set(UNP_NAMES_SERVPORT_FILE "servport.cc")

# 生成可执行文件
add_executable(getservport_exe ${UNP_NAMES_SERVPORT_FILE})

# 链接库文件
target_link_libraries(getservport_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS getservport_exe DESTINATION bin)

# ======================================================
# 自动包含当前目录代码文件
set(UNP_NAMES_PORT2SERV_FILE "port2serv.cc")

# 生成可执行文件
add_executable(port2serv_exe ${UNP_NAMES_PORT2SERV_FILE})

# 链接库文件
target_link_libraries(port2serv_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS port2serv_exe DESTINATION bin)