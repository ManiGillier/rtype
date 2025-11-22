# ECS Usage Guide

## Basic usage

1. Define Components
Components are simple data structures.
```cpp
struct Position {
    int x;
    int y;
};
```
2. Create Systems
Systems are functions that process components.
```cpp
void logging_system(Registry& r, SparseArray<Position> const& positions)
{
    for (auto&& [i, pos] : containers::indexed_zipper(positions))
        std::cerr << i << ": Position = { " << pos.value().x << ", "
                  << pos.value().y << " }" << std ::endl;
}
```
3. Setup Registry
```cpp
Registry r;
r.register_component<Position>();
```
4. Create Entities
```cpp
Entity player = r.spawn_entity();
```
5. Add Components to Entities
```cpp
r.emplace_component<Position>(player, 2, 23);
```
6. Register and Run Systems
```cpp
r.add_system<Position, Position>(logging_system);
r.run_systems();
```
7. Cleanup
```cpp
r.kill_entity(player);
```
## Complete Example

[see file](../../ecs/ecs_exemple.cpp)

```cpp

// here we define a component
typedef struct Position {
    int x;
    int y;
} Position;

// define system to interact with component
void logging_system(Registry& r, SparseArray<Position> const& positions)
{
    (void)r;

    // with indexed iterator
    for (auto&& [i, pos] : containers::indexed_zipper(positions))
        std::cerr << i << ": Position = { " << pos.value().x << ", "
                  << pos.value().y << " }" << std ::endl;
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

```
## Iterating Over Components
Use zipper to iterate over multiple component arrays:
```cpp

// Without index
for (auto&& [pos, vel] : containers::zipper(positions, velocities)) {
    // Access with pos.value() and vel.value()
}

// With index
for (auto&& [i, pos, vel] : containers::indexed_zipper(positions, velocities)) {
    // i is the entity ID
}
```
