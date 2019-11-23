cmake_minimum_required(VERSION 3.15)
project(Maple)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Maple src/main.cpp)
target_compile_features(Maple PUBLIC cxx_std_17)
