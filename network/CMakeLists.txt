file(GLOB_RECURSE network_src CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# zlib v1.3.1 package
CPMAddPackage(
    NAME zlib
    GIT_REPOSITORY https://github.com/madler/zlib/
    GIT_TAG v1.3.1
    OPTIONS
        "ZLIB_BUILD_EXAMPLES OFF"
)

add_library(network STATIC ${network_src})

target_include_directories(network PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
target_link_libraries(network PUBLIC zlibstatic)

# network tester
set(NETWORK_TEST_EXEC_NAME reseauTypeTester)
file(GLOB_RECURSE network_test_src ${PROJECT_ROOT}/network_test/src/*.cpp)
file(GLOB_RECURSE network_test_src_h ${PROJECT_ROOT}/network_test/src/*.hpp)

if(network_test_src)
    add_executable(${NETWORK_TEST_EXEC_NAME} EXCLUDE_FROM_ALL ${network_test_src} ${network_test_src_h})
    target_include_directories(${NETWORK_TEST_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
    target_link_libraries(${NETWORK_TEST_EXEC_NAME} PRIVATE network)
    add_custom_target(reseau DEPENDS ${NETWORK_TEST_EXEC_NAME})
endif()
