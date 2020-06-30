# 设置需要的cmake版本
cmake_minimum_required(VERSION 3.10)

# 设置工程名称
project(StlProject)

# 设置版本信息，在.in文件中通过@<name>@替换对应值
set(UNP_VERSION_MAJOR 1)
set(UNP_VERSION_MINOR 0)
set(CPU ${CMAKE_SYSTEM_PROCESSOR})
set(VENDOR ${CMAKE_CXX_COMPILER_ID})
set(OS ${CMAKE_SYSTEM_NAME})

# 设置需要链接的系统库
# set(REQ_LIBS ${REQ_LIBS} "m")
# set(CMAKE_REQUIRED_LIBRARIES ${REQ_LIBS})

# 检查函数功能是否存在，在配置.in文件定义该宏值
# include(CheckFunctionExists)
# check_function_exists(log HAVE_LOG)
# check_function_exists(exp HAVE_EXP)

# 定义默认选项
# option(USE_MYMATH
#	    "Use tutorial provided math implementation"
#	    on)
option(BUILD_DEBUG_TYPE
	   "build debug type"
	   on)

option(IPV4
	   "ipv4"
	   on)

option(IPV6
	   "ipv6"
	   on)

option(HAVE_VSNPRINTF
	   "vsnprintf"
	   on)
# 设置编译选项
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIE -pie")
#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fPIE -pie")

# 生成编译时的配置文件.h(包含各种宏)
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
	)
include_directories(${PROJECT_BINARY_DIR})

# 检查对应选项是否打开
if (BUILD_DEBUG_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")
endif (BUILD_DEBUG_TYPE)

# if (USE_MYMATH)
#     add_subdirectory(MathFunctions)
#     include_directories(${PROJECT_SOURCE_DIR}/MathFunctions)
#     set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
# endif(USE_MYMATH)

# ==============================================================
# 添加头文件路径
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

#添加子目录
add_subdirectory(lib)
add_subdirectory(intro)
# =============================================================

#指定安装时使用的路径前缀
set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install")

