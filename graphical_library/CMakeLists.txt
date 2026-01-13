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
file(GLOB_RECURSE gl_src ${PROJECT_ROOT}/graphical_library/*.cpp)
file(GLOB_RECURSE gl_src_h ${PROJECT_ROOT}/graphical_library/*.hpp)

# raylib v5.5 package
CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    OPTIONS
        "BUILD_EXAMPLES OFF"
)

add_library(graphical_library STATIC ${gl_src} ${gl_src_h})
target_include_directories(graphical_library PUBLIC ${PROJECT_ROOT})
target_link_libraries(graphical_library PRIVATE raylib)
