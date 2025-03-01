cmake_minimum_required(VERSION 3.15)
project(RasterizerProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(rasterizer
    src/main.cpp
    src/rasterizer.cpp
)

set_target_properties(rasterizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_compile_options(rasterizer PRIVATE -Wall -Wextra -pedantic)