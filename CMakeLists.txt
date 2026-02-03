cmake_minimum_required(VERSION 4.2)

project(LoopOver
    VERSION 0.2.1
    LANGUAGES C)

# --- Standards and Features ---
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# --- Build Configuration ---
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG -fno-unwind-tables -fno-asynchronous-unwind-tables -flto")
set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")

# --- Source Files ---
set(SOURCES
    src/main.c
    src/plist.c
    src/bottle.c
)

add_executable(LoopOver ${SOURCES})

# --- Include Directories ---
target_include_directories(LoopOver PRIVATE include)

# --- Compilation Options ---
target_compile_options(LoopOver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
    -Wstrict-prototypes
    -Wmissing-prototypes
    -Werror=implicit-function-declaration
    -Wformat=2
)

# --- Dependencies ---
find_library(CORE_FOUNDATION_LIB CoreFoundation REQUIRED)
target_link_libraries(LoopOver PRIVATE ${CORE_FOUNDATION_LIB})
