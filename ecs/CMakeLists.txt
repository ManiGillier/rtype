file(GLOB_RECURSE ecs_src CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

list(FILTER ecs_src EXCLUDE REGEX "ecs_exemple\\.cpp$")

add_library(ecs STATIC ${ecs_src})

target_include_directories(ecs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
