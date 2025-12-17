# ECS Usage Guide

An Entity Component System works with 3 types :
- Entities
- Components
- Systems

A Component is a small storage structure.  
It should define a single component out of a more complex set, representing an Entity.

As said, an Entity is represented by a set of components, which can be dynamically modified.

And a System is something that you would apply on all entities satisfying certain Components, to allow for modification, rendering, ...

For example, if you have a component Position and Velocity, you could have a System to update the Position based on the Velocity, and a lot of very different entities could end up with those components and be moved by the same System.

The goal is to separate every actions, and to maximize performances.

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
void logging_system(Registry& r,
    containers::indexed_zipper<SparseArray<Position>,
                               SparseArray<Velocity>> zipper)
{
    for (auto&& [i, pos, vel] : zipper)
        std::cerr << i << ": Position = { " << pos.value().x << ", "
                  << pos.value().y << " }" << std ::endl;
        std::cerr << i << ": Velocity = { " << vel->x << ", "
                  << vel->y << " }" << std ::endl;
}
```
3. Setup Registry  
The registry holds the ECS.
```cpp
Registry r;
r.register_component<Position>();
r.register_component<Velocity>();
```
4. Create Entities
```cpp
Entity player = r.spawn_entity();
```
5. Add Components to Entities
```cpp
r.emplace_component<Position>(player, 2, 23);
r.emplace_component<Velocity>(player, 1, 0);
```
6. Register and Run Systems
```cpp
r.add_{render/update}_system<Position, Velocity>(logging_system);
r.{render/update}();
```
7. Cleanup
```cpp
r.kill_entity(player);
```
## Complete Example

See the file `ecs/ecs_exemple.cpp`

## Iterating Over Components
Use zipper to iterate over multiple component arrays:
```cpp

// With index
for (auto&& [i, pos, vel] : containers::indexed_zipper(positions, velocities)) {
    // i is the entity ID
}
```

## Passing more parameters to systems

You can simply add more parameters to systems when registering them.

```cpp
void system([[maybe_unused]] Registry &r,
    [[maybe_unused]] containers::indexed_zipper<SparseArray<Position>> zipper,
    int bonus_parameter)
{
    std::cout << "Int value=" << bonus_parameter << std::endl;
}

// Inside function to register systems
registry.add_render_system<Position>(12); // 12 will be passed as bonus_parameter
```
