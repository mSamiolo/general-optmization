cmake_minimum_required(VERSION 3.22)

project(non-linear-constrained-opt C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 23)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -Wall -fdiagnostics-color")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -O1")

# Set default compiler
if (NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER clang)
endif()

# Add main.c and mesh_generation.c to the source files
set(SOURCES 
        optimization_algorithm/main.c
        optimization_algorithm/merit_function/merit_function.c
        )

# Include directories (modify if needed)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(/usr/local/lib/nlopt-2.7.1/src/api/)  # Adjust path

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

## If you have precompiled headers you can add them like this
#target_precompiled_headers(easy-fem PRIVATE "${CMAKE_SOURCE_DIR}/src/pch.h")
target_link_libraries(${PROJECT_NAME} nlopt m)