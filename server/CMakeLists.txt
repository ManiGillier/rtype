set(SERVER_EXEC_NAME r-type_server)

file(GLOB_RECURSE server_src CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${PROJECT_ROOT}/shared/*.cpp
)

file(GLOB_RECURSE server_src_h CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${PROJECT_ROOT}/shared/*.hpp
)

CPMAddPackage(
    NAME SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
    GIT_TAG 3.3.3
    OPTIONS
        "SQLITECPP_BUILD_EXAMPLES OFF"
)

CPMAddPackage(
    NAME libconfig
    GIT_REPOSITORY https://github.com/hyperrealm/libconfig
    GIT_TAG v1.8.2
    OPTIONS
        "BUILD_EXAMPLES OFF"
        "BUILD_CXX ON"
)

add_executable(${SERVER_EXEC_NAME} ${server_src} ${server_src_h})
target_include_directories(${SERVER_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
target_link_libraries(${SERVER_EXEC_NAME} PRIVATE ecs network SQLiteCpp config)
