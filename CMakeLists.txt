cmake_minimum_required(VERSION 3.28)

project(Ray_Tracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(Ray_Tracing
    src/main.cpp
)

target_include_directories(Ray_Tracing PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)