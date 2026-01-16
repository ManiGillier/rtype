
set(RCON_EXEC_NAME r-type_rcon)

file(GLOB_RECURSE rcon_src CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${PROJECT_ROOT}/shared/*.cpp
)

file(GLOB_RECURSE rcon_src_h CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${PROJECT_ROOT}/shared/*.hpp
)

add_executable(${RCON_EXEC_NAME} ${rcon_src} ${rcon_src_h})
target_include_directories(${RCON_EXEC_NAME} PUBLIC ${PROJECT_ROOT})
target_link_libraries(${RCON_EXEC_NAME} PRIVATE network)
