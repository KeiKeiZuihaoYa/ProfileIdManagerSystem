cmake_minimum_required(VERSION 3.10)  # CMake 最低版本要求
project(ProfileIdManagerSystem)       # 项目名称

set(CMAKE_CXX_STANDARD 17)            # 使用 C++17 标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # 强制要求支持 C++17

# 添加头文件目录
include_directories(include)

# 自动收集所有源文件（包括 main.cpp 和 src 目录下的 .cpp）
file(GLOB SOURCES
    "src/*.cpp"
    "main.cpp"
)

# 设置可执行文件和库的输出目录（非必须，但可统一管理）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# 设置编码参数
if (MSVC)
    add_compile_options("/utf-8")
else()
    add_compile_options("-finput-charset=UTF-8" "-fexec-charset=UTF-8")
endif()

# 生成可执行文件
add_executable(main ${SOURCES})