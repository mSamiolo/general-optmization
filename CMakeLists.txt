cmake_minimum_required(VERSION 3.22)

project(non-linear-constrained-opt C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

################################################################
#                     Compiler directives
################################################################

add_subdirectory(external/nlopt)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ggdb -Wall -fdiagnostics-color") # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -O1")

if (NOT CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER clang)
endif()

################################################################
#                  Download Git submodules
################################################################
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

# if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/repo/CMakeLists.txt")
#     message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
# endif()


################################################################
#                  Source file declaration
################################################################
set(SOURCES 
        optimization_algorithm/main.c
        optimization_algorithm/merit_function/merit_function.c
        optimization_algorithm/input_output/input_output.c
        optimization_algorithm/input_output/design_variable.c
        optimization_algorithm/merit_function/merit_function.c
        )

set(SOURCES_TOML_LIB 
                    external/tomlc99/toml.c
                    external/tomlc99/toml_cat.c  
                     )

##                              TO BE USED INSTEAD OF THE ABOVE

################################################################
#                  Library definition
################################################################                     
add_library(toml ${SOURCES_TOML_LIB})


################################################################
#                  Preprocessors definition
################################################################                     
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

## If you have precompiled headers you can add them like this
#target_precompiled_headers(easy-fem PRIVATE "${CMAKE_SOURCE_DIR}/src/pch.h")
target_link_libraries(${PROJECT_NAME} nlopt m toml)
