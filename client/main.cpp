

#include "graphical_library/Color.hpp"
#include "graphical_library/GraphicalLibrary.hpp"
#include "graphical_library/shapes/Rectangle.hpp"
#include "graphical_library/Vector.hpp"
#include "raylib/Raylib.hpp"
#include <memory>

auto main() -> int
{
    std::unique_ptr<gl::GraphicalLibrary> gl = std::make_unique<Raylib>();

    gl::Rectangle rect {gl::WorldPosition {10, 10}, gl::Vector2ui {20, 20}, gl::WHITE};

    gl->init();
    while (!gl->should_close()) {
        gl->start_new_frame();
        gl->draw(rect);
        gl->end_frame();
    }
}
