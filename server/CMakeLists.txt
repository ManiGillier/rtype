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
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -g3 -Wpedantic -fsanitize=address -Wno-error=sign-conversion -Wno-sign-conversion")
else ()
    set(CPP_CC_FLAGS "-Wall -Werror -Wconversion -Wcast-align -Wunused -Wextra -Wpedantic")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPP_CC_FLAGS}")
message("-- CMake flags:" ${CMAKE_CXX_FLAGS}) 

# exec name
set(SERVER_EXEC_NAME r-type_server)
set(NETWORK_TEST_EXEC_NAME reseauTypeTester)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR}/..)

# all cpp file in src directory only
file(GLOB_RECURSE server_src *.cpp ${PROJECT_ROOT}/ecs/*.cpp ${PROJECT_ROOT}/shared/*.cpp)
file(GLOB_RECURSE server_src_h *.hpp ${PROJECT_ROOT}/ecs/*.hpp ${PROJECT_ROOT}/shared/*.hpp)

list(FILTER server_src EXCLUDE REGEX ".*/build/.*")
list(FILTER server_src EXCLUDE REGEX ".*CMakeCXXCompilerId\\.cpp$")
list(FILTER server_src EXCLUDE REGEX "ecs_exemple\\.cpp$")

add_subdirectory(${PROJECT_ROOT}/network ${CMAKE_BINARY_DIR}/network)

CPMAddPackage(
    NAME SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
    GIT_TAG 3.3.3
    OPTIONS
        "SQLITECPP_BUILD_EXAMPLES OFF"
)

add_executable(${SERVER_EXEC_NAME} ${server_src} ${server_src_h})
target_include_directories(${SERVER_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
target_link_libraries(${SERVER_EXEC_NAME} PRIVATE network_lib SQLiteCpp)

file(GLOB_RECURSE network_test_src ${PROJECT_ROOT}/network_test/src/*.cpp)
file(GLOB_RECURSE network_test_src_h ${PROJECT_ROOT}/network_test/src/*.hpp)

if(network_test_src)
    add_executable(${NETWORK_TEST_EXEC_NAME} EXCLUDE_FROM_ALL ${network_test_src} ${network_test_src_h})
    target_include_directories(${NETWORK_TEST_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
    target_link_libraries(${NETWORK_TEST_EXEC_NAME} PRIVATE network_lib)
    add_custom_target(reseau DEPENDS ${NETWORK_TEST_EXEC_NAME})
endif()
