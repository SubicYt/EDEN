cmake_minimum_required(VERSION 3.20)

project(Eden)

set(CMAKE_CXX_STANDARD 17)

add_executable(eden main.cpp)

set_target_properties(eden PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)