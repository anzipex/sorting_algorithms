cmake_minimum_required(VERSION 3.5.0)
project(sorting_algorithms VERSION 0.1)

set(SOURCE_FILES src/main.cpp)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(main ${SOURCE_FILES})