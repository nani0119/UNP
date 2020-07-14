cmake_minimum_required(VERSION 3.10)

set(MODULE_NAME MYCAT)

# 添加动态或者静态链接库路径
link_directories(${PROJECT_BINARY_DIR}/lib)
link_directories(${PROJECT_BINARY_DIR}/install/lib)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR}/install/include)

set(EXTRA_LIBS  ${EXTRA_LIBS}  "libunp.a")
# ======================================================
# 自动包含当前目录代码文件
set(UNP_UNIXDOMAIN_MYCAT_FILE "mycat.cc")

# 生成可执行文件
add_executable(mycat_exe ${UNP_UNIXDOMAIN_MYCAT_FILE})

# 链接库文件
target_link_libraries(mycat_exe ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS mycat_exe DESTINATION bin)

# ======================================================
# 自动包含当前目录代码文件
set(UNP_UNIXDOMAIN_OPENFILE_FILE "openfile.cc")

# 生成可执行文件
add_executable(openfile ${UNP_UNIXDOMAIN_OPENFILE_FILE})

# 链接库文件
target_link_libraries(openfile ${EXTRA_LIBS})

# 指定安装的文件信息
install(TARGETS openfile DESTINATION bin)