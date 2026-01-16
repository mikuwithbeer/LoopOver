cmake_minimum_required(VERSION 4.1)


# Project details
project(LoopOver
    VERSION 0.1.1
    LANGUAGES C)


# C standards
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


# Add files
set(SOURCES
    src/main.c
    src/plist.c
    src/bottle.c)
set(HEADERS
    src/plist.h
    src/bottle.h)

add_executable(LoopOver ${SOURCES} ${HEADERS})


# Enable compiler warnings
target_compile_options(LoopOver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion)


# Link core foundation
find_library(CORE_FOUNDATION_LIB CoreFoundation REQUIRED)
target_link_libraries(LoopOver PRIVATE ${CORE_FOUNDATION_LIB})
