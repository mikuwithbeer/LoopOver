cmake_minimum_required(VERSION 4.1)

# Project Detail
project(LoopOver C)

# C Standards
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Add files
add_executable(LoopOver src/main.c)
target_sources(LoopOver PRIVATE
    src/plist.c
    src/plist.h
)

# Link CoreFoundation
find_library(CORE_FOUNDATION_LIB CoreFoundation REQUIRED)
target_link_libraries(LoopOver PRIVATE ${CORE_FOUNDATION_LIB})
