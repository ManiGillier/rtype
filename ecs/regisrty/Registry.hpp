#ifndef _REGISTRY_HPP_
#define _REGISTRY_HPP_

#include "../sparse_array/SparseArray.hpp"
#include "../entity/Entity.hpp"
#include <any>
#include <cstddef>
#include <functional>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include <vector>

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

    Entity spawn_entity();
    Entity entity_from_index(std::size_t idx);
    void kill_entity(Entity const& e);

    template <class Component>
    typename SparseArray<Component>::reference_type
    add_component(Entity const& to, Component&& c);

    template <class Component, typename... Params>
    typename SparseArray<Component>::reference_type
    emplace_component(Entity const& to, Params&&... p);

    template <class Component>
    void remove_component(Entity const& from);

    template <class... Components, typename Function>
    void add_system(Function&& f);
    template <class... Components, typename Function>
    void add_system(Function const& f);
    void run_systems();

  private:
    std::unordered_map<std::type_index, std::any> _components_arrays;
    std::vector<erase_function_t> _erase_functions;
    std::size_t _next_entity_id = 0;
    std::queue<size_t> _dead_entities;
    std::vector<system_function_t> _systems;

    template <typename Function, typename... Components>
    static void call_system(Registry& reg, Function& f);
};

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

    return std::any_cast<SparseArray<Component>&>(_components_arrays[type_idx]);
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
Registry::add_component(Entity const& to, Component&& c)
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

template <class... Components, typename Function>
void Registry::add_system(Function&& f)
{
    system_function_t wrapped_system =
        [f = std::forward<Function>(f)](Registry& r) mutable {
            f(r, r.get_components<Components>()...);
        };
    _systems.push_back(std::move(wrapped_system));
}

template <class... Components, typename Function>
void Registry::add_system(Function const& f)
{
    system_function_t wrapped_system = [f](Registry& r) {
        f(r, r.get_components<Components>()...);
    };
    _systems.push_back(wrapped_system);
}

#endif
