#ifndef _REGISTRY_HPP_
#define _REGISTRY_HPP_

#include "../sparse_array/SparseArray.hpp"
#include "../entity/Entity.hpp"
#include <any>
#include <cstddef>
#include <functional>
#include <optional>
#include <queue>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <optional>

class Registry
{
  public:
    using erase_function_t = std::function<void(Registry&, Entity const&)>;
    using system_function_t = std::function<void(Registry&)>;

    template <class Component>
    SparseArray<Component>& register_component();
    template <class Component>
    SparseArray<Component>& get_components();
    template <class Component>
    SparseArray<Component> const& get_components() const;

    template <class Component>
    std::optional<Component> get(Entity) const;
    template <class Component>
    std::optional<Component> get(std::size_t) const;

    template <class Component, class... Args>
    void set(std::size_t, Args...);
    template <class Component, class... Args>
    void set(Entity, Args...);

    SparseArray<std::any>& get_components_by_id(const std::type_index &);
    SparseArray<std::any> const&
        get_components_by_id(const std::type_index &) const;

    Entity spawn_entity();
    Entity spawn_named_entity(std::string name);
    Entity entity_from_index(std::size_t idx);
    std::optional<Entity> entity_from_name(std::string name);
    void kill_entity(Entity const& e);
    void kill_entity(std::string name);

    template <class Component>
    typename SparseArray<Component>::reference_type
    add_component(Entity const& to, Component c);

    template <class Component, typename... Params>
    typename SparseArray<Component>::reference_type
    emplace_component(Entity const& to, Params&&... p);

    template <class Component>
    void remove_component(Entity const& from);

    template <class... Components, typename Function, class... Args>
    void add_update_system(Function&& f, Args&&...);
    template <class... Components, typename Function, class... Args>
    void add_render_system(Function&& f, Args&&...);

    template <typename Function, class... Args>
    void add_global_render_system(Function&& f, Args&&...);
    template <typename Function, class... Args>
    void add_global_update_system(Function&& f, Args&&...);

    void reset_update_systems();
    void reset_render_systems();

    void update();
    void render();

    std::size_t max_id() const { return _next_entity_id; }

    template <class... Components>
    auto get_components_from_id(std::size_t id)
        -> std::optional<std::tuple<Components*...>>;

    template <class... Components>
    auto get_filtered_components()
        -> std::unordered_map<std::size_t, std::tuple<Components*...>>;

  private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::vector<erase_function_t> _erase_functions;
    std::size_t _next_entity_id = 0;
    std::queue<size_t> _dead_entities;
    std::vector<system_function_t> _update_systems;
    std::vector<system_function_t> _render_systems;
    std::unordered_map<std::string, std::size_t> named_entities_ids;
    std::unordered_map<std::size_t, std::string> named_entities_names;
};

template <class... Components>
auto Registry::get_components_from_id(std::size_t id)
-> std::optional<std::tuple<Components*...>>
{
    std::vector<std::size_t> sizes = {get_components<Components>().size()...};
    for (auto &size : sizes)
        if (size <= id)
            return std::nullopt;
    std::vector<bool> have_values = {get_components<Components>()[id].has_value()...};
    for (auto have_value : have_values)
        if (!have_value)
            return std::nullopt;
    return std::make_tuple(&get_components<Components>()[id].value()...);
}

template <class... Components>
auto Registry::get_filtered_components()
-> std::unordered_map<std::size_t, std::tuple<Components*...>>
{
    std::unordered_map<std::size_t, std::tuple<Components*...>> map;

    for (std::size_t id = 0; id < this->max_id(); id++) {
        auto result = this->get_components_from_id<Components...>(id);
        if (!result)
            continue;
        map[id] = result.value();
    }
    return map;
}

template <class Component>
SparseArray<Component>& Registry::register_component()
{
    std::type_index type_idx(typeid(Component));
    _components_arrays[type_idx] = SparseArray<Component>();

    erase_function_t erase_fn = [](Registry& reg, Entity const& entity) {
        auto& components = reg.get_components<Component>();
        components.erase(static_cast<size_t>(entity));
    };

    _erase_functions.push_back(erase_fn);

    return this->get_components<Component>();
}

template <class Component>
SparseArray<Component>& Registry::get_components()
{
    std::type_index type_idx(typeid(Component));
    return std::any_cast<SparseArray<Component>&>(_components_arrays[type_idx]);
}

template <class Component>
SparseArray<Component> const& Registry::get_components() const
{
    std::type_index type_idx(typeid(Component));
    return std::any_cast<const SparseArray<Component>&>(
        _components_arrays.at(type_idx));
}

template <class Component>
typename SparseArray<Component>::reference_type
Registry::add_component(Entity const& to, Component c)
{
    auto& components = get_components<Component>();
    size_t id = static_cast<size_t>(to);
    return components.insert_at(id, std::forward<Component>(c));
}

template <class Component, typename... Params>
typename SparseArray<Component>::reference_type
Registry::emplace_component(Entity const& to, Params&&... p)
{
    auto& components = get_components<Component>();
    size_t id = static_cast<size_t>(to);
    return components.emplace_at(id, std::forward<Params>(p)...);
}

template <class Component>
void Registry::remove_component(Entity const& from)
{
    auto& components = get_components<Component>();
    size_t id = static_cast<size_t>(from);
    components.erase(id);
}

#include "ecs/zipper/IndexedZipper.hpp"

template <class... Components, typename Function, class... Args>
void Registry::add_update_system(Function&& f, Args&&... args)
{
    system_function_t wrapped_system =
        [this, f = std::forward<Function>(f), args...](Registry& r) mutable {
            f(r, containers::indexed_zipper(this->get_components<Components>()...),
              args...);
        };
    _update_systems.push_back(std::move(wrapped_system));
}

template <class... Components, typename Function, class... Args>
void Registry::add_render_system(Function&& f, Args&&... args)
{
    system_function_t wrapped_system =
        [this, f = std::forward<Function>(f), args...](Registry& r) mutable {
            f(r, containers::indexed_zipper(this->get_components<Components>()...),
              args...);
        };
    _render_systems.push_back(std::move(wrapped_system));
}

template <typename Function, class... Args>
void Registry::add_global_update_system(Function&& f, Args&&... args)
{
    system_function_t wrapped_system =
        [f = std::forward<Function>(f), args...](Registry& r) mutable {
            f(r, args...);
        };
    _update_systems.push_back(std::move(wrapped_system));
}

template <typename Function, class... Args>
void Registry::add_global_render_system(Function&& f, Args&&... args)
{
    system_function_t wrapped_system =
        [f = std::forward<Function>(f), args...](Registry& r) mutable {
            f(r, args...);
        };
    _render_systems.push_back(std::move(wrapped_system));
}

template <class Component>
std::optional<Component> Registry::get(Entity entity) const
{
    return this->get<Component>(entity.getId());
}

template <class Component>
std::optional<Component> Registry::get(std::size_t id) const
{
    SparseArray<Component> const &arr = this->get_components<Component>();

    if (arr.size() <= id)
        return std::nullopt;
    return arr[id];
}

template <class Component, class... Args>
void Registry::set(Entity entity, Args... args)
{
    this->emplace_component<Component>(entity, args...);
}

template <class Component, class... Args>
void Registry::set(std::size_t id, Args... args)
{
    this->emplace_component<Component>(this->entity_from_index(id), args...);
}


#endif
