#include "Registry.hpp"
#include <optional>

Entity Registry::spawn_entity()
{
    if (!_dead_entities.empty()) {
        size_t id = _dead_entities.front();
        _dead_entities.pop();
        return Entity(id);
    }
    return Entity(_next_entity_id++);
}

Entity Registry::spawn_named_entity(std::string name)
{
    Entity entity = this->spawn_entity();

    this->named_entities_ids[name] = entity.getId();
    this->named_entities_names[entity.getId()] = name;
    return entity;
}

std::optional<Entity> Registry::entity_from_name(std::string name)
{
    if (!this->named_entities_ids.contains(name))
        return std::nullopt;
    return this->entity_from_index(this->named_entities_ids.at(name));
}

Entity Registry::entity_from_index(std::size_t idx)
{
    return Entity(idx);
}

void Registry::kill_entity(std::string name)
{
    std::optional<Entity> entity = this->entity_from_name(name);
    if (!entity)
        return;
    this->kill_entity(*entity);
}

void Registry::kill_entity(Entity const& e)
{
    size_t id = static_cast<size_t>(e);

    for (auto& erase_fn : _erase_functions) {
        erase_fn(*this, e);
    }
    _dead_entities.push(id);
    if (!this->named_entities_names.contains(id))
        return;
    this->named_entities_ids.erase(this->named_entities_names.at(id));
    this->named_entities_names.erase(id);
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
