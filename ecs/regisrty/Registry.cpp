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

void Registry::update()
{
    for (auto& system : _update_systems) {
        system(*this);
    }
}

void Registry::render()
{
    for (auto& system : _render_systems) {
        system(*this);
    }
}

SparseArray<std::any>& Registry::get_components_by_id(const std::type_index &id)
{
    return std::any_cast<SparseArray<std::any>&>(_components_arrays[id]);
}

SparseArray<std::any> const& Registry::get_components_by_id
(const std::type_index &id) const
{
    return std::any_cast<SparseArray<std::any> const&>(_components_arrays.at(id));
}

void Registry::reset_update_systems()
{
    this->_update_systems = {};
}

void Registry::reset_render_systems()
{
    this->_render_systems = {};
}
