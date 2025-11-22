#include "Registry.hpp"

Entity Registry::spawn_entity()
{
    if (!_dead_entities.empty()) {
        size_t id = _dead_entities.front();
        _dead_entities.pop();
        return Entity(id);
    }
    return Entity(_next_entity_id++);
}

Entity Registry::entity_from_index(std::size_t idx)
{
    return Entity(idx);
}

void Registry::kill_entity(Entity const& e)
{
    size_t id = static_cast<size_t>(e);

    for (auto& erase_fn : _erase_functions) {
        erase_fn(*this, e);
    }
    _dead_entities.push(id);
}

void Registry::run_systems()
{
    for (auto& system : _systems) {
        system(*this);
    }
}
