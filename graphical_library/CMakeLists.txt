file(GLOB_RECURSE gl_src CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# raylib v5.5 package
CPMAddPackage(
    NAME raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    OPTIONS
        "BUILD_EXAMPLES OFF"
)

add_library(graphical_library STATIC ${gl_src})

target_include_directories(graphical_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(graphical_library PUBLIC raylib)
