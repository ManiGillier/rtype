#include "./regisrty/Registry.hpp"
#include "zipper/IndexedZipper.hpp"
#include "zipper/Zipper.hpp"
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <utility>

// here we define a component
typedef struct Position {
    int x;
    int y;
} Position;

// define system to interact with entity
void logging_system(Registry& r,
                    std::unordered_map<std::size_t, std::tuple<Position>> result)
{
    (void)r;

    for (auto&& [i, res] : result) {
        Position &pos = std::get<Position>(res);
        std::cerr << i << ": Position = { " << pos.x << ", "
                  << pos.y << " }" << std ::endl;
    }
}

int main(void)
{
    Registry r;

    // register all components we use
    r.register_component<Position>();

    // create entity
    Entity player = r.spawn_entity();

    // define the components of this entity ex: player -> position, velocity,
    // networkInfo ...
    r.emplace_component<Position>(player, 2, 23);

    // create system then add id to the registry
    r.add_update_system<Position>(logging_system);
    r.update();
    // kill player
    r.kill_entity(player);
    return 0;
}
