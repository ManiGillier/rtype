cmake_minimum_required(VERSION 3.15)
project(R-Type LANGUAGES CXX)

include("${CMAKE_SOURCE_DIR}/../cmake/CPM.cmake")
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/../.cpm-cache")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/..)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic -fsanitize=address")
    set(RAYLIB_LOG_LEVEL "-DRAYLIB_LOG_LEVEL=LOG_DEBUG")
else ()
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -Wpedantic")
    set(RAYLIB_LOG_LEVEL "-DRAYLIB_LOG_LEVEL=LOG_ERROR")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_CC_FLAGS} ${RAYLIB_LOG_LEVEL}")
message("-- CMake flags:" ${CMAKE_CXX_FLAGS}) 

# exec name
set(CLIENT_EXEC_NAME r-type_client)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR}/..)

# all cpp file in src directory only
file(GLOB_RECURSE client_src *.cpp ${PROJECT_ROOT}/ecs/*.cpp ${PROJECT_ROOT}/shared/*.cpp)
file(GLOB_RECURSE client_src_h *.hpp ${PROJECT_ROOT}/ecs/*.hpp ${PROJECT_ROOT}/shared/*.hpp)

list(FILTER client_src EXCLUDE REGEX ".*/build/.*")
list(FILTER client_src EXCLUDE REGEX ".*CMakeCXXCompilerId\\.cpp$")
list(FILTER client_src EXCLUDE REGEX "ecs_exemple\\.cpp$")

add_subdirectory(${PROJECT_ROOT}/network ${CMAKE_BINARY_DIR}/network)

# raylib v5.5 package
CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    OPTIONS
        "BUILD_EXAMPLES OFF"
)

add_executable(${CLIENT_EXEC_NAME} ${client_src} ${client_src_h})
target_include_directories(${CLIENT_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
target_link_libraries(${CLIENT_EXEC_NAME} PRIVATE network_lib raylib)
