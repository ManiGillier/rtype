#include "./regisrty/Registry.hpp"
#include "zipper/IndexedZipper.hpp"
#include "zipper/Zipper.hpp"
#include <iostream>

// here we define a component
typedef struct Position {
    int x;
    int y;
} Position;

// define system to interact with entity
void logging_system(Registry& r, SparseArray<Position> const& positions)
{
    (void)r;

    // with indexed iterator
    for (auto&& [i, pos] : containers::indexed_zipper(positions))
        std::cerr << i << ": Position = { " << pos.value().x << ", "
                  << pos.value().y << " }" << std ::endl;
    // without index
    for (auto&& [pos] : containers::zipper(positions))
        std::cerr << ": Position = { " << pos.value().x << ", " << pos.value().y
                  << " }" << std ::endl;
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
    r.add_system<Position>(logging_system);
    r.run_systems();
    // kill player
    r.kill_entity(player);
    return 0;
}
