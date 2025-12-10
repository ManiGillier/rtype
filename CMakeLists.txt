cmake_minimum_required(VERSION 3.15)

project(R-Type LANGUAGES CXX)

# cmake package manager
include(${CMAKE_SOURCE_DIR}/cmake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/.cpm-cache")

## set std 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_EXTENSIONS OFF)

## add executable to root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic")
    set(RAYLIB_LOG_LEVEL "-DRAYLIB_LOG_LEVEL=LOG_DEBUG")
else ()
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -Wpedantic")
    set(RAYLIB_LOG_LEVEL "-DRAYLIB_LOG_LEVEL=LOG_ERROR")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_CC_FLAGS} ${RAYLIB_LOG_LEVEL}")
message("-- CMake flags:" ${CMAKE_CXX_FLAGS}) 

# exec name
set(SERVER_EXEC_NAME r-type_server)
set(CLIENT_EXEC_NAME r-type_client)

# all cpp file in src directory only
file(GLOB_RECURSE server_src server/*.cpp ecs/*.cpp shared/*.cpp)
file(GLOB_RECURSE client_src client/*.cpp ecs/*.cpp shared/*.cpp)

# get all cpp files from network library
file(GLOB_RECURSE network_src network/*.cpp)
file(GLOB_RECURSE network_src_h network/*.hpp)

# Get all subdirectories for includes
file(GLOB_RECURSE ALL_HEADERS 
    ${CMAKE_SOURCE_DIR}/*.hpp
    ${CMAKE_SOURCE_DIR}/*.h
)

add_library(network_lib STATIC ${network_src} ${network_src_h})
target_include_directories(network_lib PUBLIC ${CMAKE_SOURCE_DIR})

# headers file
file(GLOB_RECURSE server_src_h server/*.hpp ecs/*.hpp)
file(GLOB_RECURSE client_src_h client/*.hpp ecs/*.hpp)

list(FILTER server_src EXCLUDE REGEX "ecs_exemple\\.cpp$")
list(FILTER client_src EXCLUDE REGEX "ecs_exemple\\.cpp$")

# Raylib v5.5 package
CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    OPTIONS
      "BUILD_EXAMPLES OFF"
)

add_executable(${SERVER_EXEC_NAME} ${server_src} ${server_src_h})
add_executable(${CLIENT_EXEC_NAME} ${client_src} ${client_src_h})

target_include_directories(${SERVER_EXEC_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
target_include_directories(${CLIENT_EXEC_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(${SERVER_EXEC_NAME} PRIVATE network_lib)
target_link_libraries(${CLIENT_EXEC_NAME} PRIVATE network_lib raylib)
