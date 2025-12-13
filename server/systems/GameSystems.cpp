#include "GameSystems.hpp"
#include "shared/components/Position.hpp"

auto Systems::movement_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Velocity>,
                               SparseArray<Acceleration>>
        zipper,
    [[maybe_unused]] int i) -> void
{
    for (auto &&[i, pos, vel, acc] : zipper) {
        pos->x += vel->x;
        pos->y += vel->y;
        vel->x += acc->x;
        vel->y += acc->y;
    }
}

auto Systems::dependence_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<Dependence>,
                               SparseArray<Laser>>
        zipper,
    [[maybe_unused]] int i) -> void
{
    for (auto &&[i, pos, dep, laser] : zipper) {
        auto p_pos =
            r.get_components<Position>()[static_cast<std::size_t>(dep->id)];
        pos->x = p_pos->x;
        pos->y = p_pos->y;
    }
}

auto Systems::collision_system(
    [[maybe_unused]] Registry &r,
    containers::indexed_zipper<SparseArray<Position>, SparseArray<HitBox>>
        zipper,
    [[maybe_unused]] int i) -> void
{
    for (auto &&[i, pos, hitbox] : zipper) {
        for (auto &&[j, pos, hitbox] : zipper) {
            if (i != j) {
                // TODO: calcul collision here
            }
        }
    }
}

auto Systems::cleanup_system(Registry &r,
                    containers::indexed_zipper<SparseArray<Health>> zipper,
                    [[maybe_unused]] int i) -> void
{
    for (auto &&[i, health] : zipper) {
        if (health->pv <= 0)
            r.kill_entity(r.entity_from_index(i));
    }
}
