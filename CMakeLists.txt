cmake_minimum_required(VERSION 3.1)

# 设置C++标准为 C++ 17或11
set(CMAKE_CXX_STANDARD 11)

project(DEMO VERSION 0.1.0)

# 可以使用make test
enable_testing()

add_subdirectory(src)

add_subdirectory(tests)