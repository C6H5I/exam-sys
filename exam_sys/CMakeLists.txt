cmake_minimum_required(VERSION 3.10)

project(Example)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 手动指定 MySQL Connector/C++ 路径
set(MYSQLCPPCONN_INCLUDE_DIR /usr/include/mysql-cppconn)
set(MYSQLCPPCONN_LIBRARY /usr/lib64/libmysqlcppconn.so)

# 查找头文件
find_path(MYSQLCPPCONN_INCLUDE_DIR mysql_driver.h
    PATHS /usr/include/mysql-cppconn
    REQUIRED
)

# 动态库
find_library(MYSQLCPPCONN_LIB mysqlcppconn
    PATHS /usr/lib64
    REQUIRED
)

# 指定二进制程序产生位置
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 指定以可调试模式编译
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
endif()

# 将./src下源文件路径存入srcLIST
aux_source_directory(${PROJECT_SOURCE_DIR}/src/ srcLIST)

# 指定头文件目录
include_directories(${PROJECT_SOURCE_DIR}/include 
    /usr/include/mysql-cppconn/jdbc/)

# add_executable(example.out ${expLIST})
add_executable(exam.out ${srcLIST})

#############################

target_include_directories(exam.out PRIVATE ${MYSQLCPPCONN_INCLUDE_DIR})
target_link_libraries(exam.out
    ${MYSQLCPPCONN_LIB}
    pthread
    dl
    resolv  
)