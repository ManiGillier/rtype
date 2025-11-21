#include "./components/Position.hpp"
#include "./regisrty/Registry.hpp"
#include "zipper/Zipper.hpp"
#include <iostream>

void logging_system(Registry& r, SparseArray<Position> const& positions,
                    SparseArray<Position> const& velocities)
{
    (void)r;
    // for (auto&& [i, pos, vel] : indexed_zipper(positions, velocities))
    //     std::cerr << i << ": Position = { " << pos.x << ", " << pos.y
    //               << " } , Velocity = { " << vel.x << ", " << vel.y << "}"
    //               << std ::endl;
    for (size_t i = 0; i < positions.size() && i < velocities.size(); ++i) {
        auto const& pos = positions[i];
        auto const& vel = velocities[i];
        if (pos && vel) {
            std ::cerr << i << ": Position = { " << pos.value().x << ", "
                       << pos.value().y << " } , Velocity = { " << vel.value().x
                       << ", " << vel.value().y << " }" << std ::endl;
        }
    }
}

int main(void)
{
    Registry r;
    r.register_component<Position>();

    Entity entity1 = r.spawn_entity();
    r.add_component(entity1, Position{2, 4});

    r.kill_entity(entity1);
    entity1 = r.spawn_entity();
    r.add_component(entity1, Position{99, 99});

    r.add_system<Position, Position>(logging_system);
    r.run_systems();
    return 0;
}
