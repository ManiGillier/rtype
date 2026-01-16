cmake_minimum_required(VERSION 3.15)
project(R-Type LANGUAGES CXX)

include("${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/.cpm-cache")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

option(BUILD_SERVER "Build server" ON)
option(BUILD_CLIENT "Build client" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic -fsanitize=address -Wno-error=sign-conversion -Wno-sign-conversion")
    set(RAYLIB_LOG_LEVEL "-DRAYLIB_LOG_LEVEL=LOG_DEBUG")
else ()
    set(CPP_CC_FLAGS "-O3")
    set(RAYLIB_LOG_LEVEL "-DRAYLIB_LOG_LEVEL=LOG_ERROR")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_CC_FLAGS} ${RAYLIB_LOG_LEVEL}")
message("-- CMake flags:" ${CMAKE_CXX_FLAGS}) 

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

add_subdirectory(network)
add_subdirectory(ecs)

if(BUILD_SERVER)
    add_subdirectory(server)
endif(BUILD_SERVER)

if(BUILD_CLIENT)
    add_subdirectory(graphical_library)
    add_subdirectory(client)
endif(BUILD_CLIENT)

