cmake_minimum_required(VERSION 4.2)
project(LoopOver
    VERSION 0.2.0
    LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

file(GLOB SOURCES "src/*.c")
add_executable(LoopOver ${SOURCES})
target_include_directories(LoopOver PRIVATE include)

target_compile_options(LoopOver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion)

find_library(CORE_FOUNDATION_LIB CoreFoundation REQUIRED)
target_link_libraries(LoopOver PRIVATE ${CORE_FOUNDATION_LIB})
