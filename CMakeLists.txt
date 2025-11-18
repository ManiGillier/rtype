cmake_minimum_required(VERSION 3.10)

project(R-Type LANGUAGES CXX)

## set std 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## add executable to root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_CC_FLAGS}")
message("-- CMake flags:" ${CMAKE_CXX_FLAGS}) 

# exec name
set(SERVER_EXEC_NAME r-type_server)
set(CLIENT_EXEC_NAME r-type_client)

# all cpp file in src directory only
file(GLOB_RECURSE server_src server/src/*.cpp)
file(GLOB_RECURSE client_src client/src/*.cpp)

add_executable(${SERVER_EXEC_NAME} ${server_src})
add_executable(${CLIENT_EXEC_NAME} ${client_src})
