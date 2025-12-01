
#include "GraphicalLibInterface.hpp"
#include "raylib/Raylib.hpp"
#include <memory>

auto main() -> int
{
    std::unique_ptr<GraphicalLibAPI> gui = std::make_unique<Raylib>();

    if (not gui)
        return 84;
}
