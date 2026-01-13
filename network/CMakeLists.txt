cmake_minimum_required(VERSION 3.15)
project(R-Type LANGUAGES CXX)

include("${CMAKE_SOURCE_DIR}/../cmake/CPM.cmake")
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/../.cpm-cache")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_EXTENSIONS OFF)

## add executable to root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic -fsanitize=address")
else ()
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -Wpedantic")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_CC_FLAGS}")
message("-- CMake flags:" ${CMAKE_CXX_FLAGS}) 

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR}/..)

# get all cpp files from network library
file(GLOB_RECURSE network_src ${PROJECT_ROOT}/network/*.cpp)
file(GLOB_RECURSE network_src_h ${PROJECT_ROOT}/network/*.hpp)

# zlib v1.3.1 package
CPMAddPackage(
    NAME zlib
    GIT_REPOSITORY https://github.com/madler/zlib/
    GIT_TAG v1.3.1
    OPTIONS
        "ZLIB_BUILD_EXAMPLES OFF"
)

add_library(network_lib STATIC ${network_src} ${network_src_h})
target_link_libraries(network_lib PUBLIC zlibstatic)

target_include_directories(network_lib PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>"
    "$<BUILD_INTERFACE:${zlib_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${zlib_BINARY_DIR}>"
)
