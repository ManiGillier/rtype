set(CLIENT_EXEC_NAME r-type_client)

file(GLOB_RECURSE client_src CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${PROJECT_ROOT}/shared/*.cpp
)

file(GLOB_RECURSE client_src_h CONFIGURE_DEPENDS
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

add_executable(${CLIENT_EXEC_NAME} ${client_src} ${client_src_h})
target_include_directories(${CLIENT_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
target_link_libraries(${CLIENT_EXEC_NAME} PRIVATE ecs network SQLiteCpp graphical_library)
