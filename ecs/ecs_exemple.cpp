
#include "manager/ClientManager.hpp"
#include <iostream>

struct A {
    int a;
};

struct B {
    int b;
};

struct C {
    int c;
};

#include "ecs/zipper/Zipper.hpp"
#include "ecs/zipper/IndexedZipper.hpp"

void test(Registry &reg, int i)
{
    (void) reg;
    std::cout << "I : " << i << std::endl;
}

auto main() -> int
{
    Registry reg;

    reg.register_component<A>();
    reg.register_component<B>();
    reg.register_component<C>();

    Entity a = reg.spawn_entity();
    reg.add_component<A>(a, {0});
    Entity ab = reg.spawn_entity();
    reg.add_component<A>(ab, {1});
    reg.add_component<B>(ab, {1});
    Entity bc = reg.spawn_entity();
    reg.add_component<B>(bc, {2});
    reg.add_component<C>(bc, {2});
    Entity abc = reg.spawn_entity();
    reg.add_component<A>(abc, {3});
    reg.add_component<B>(abc, {3});
    reg.add_component<C>(abc, {3});

    auto &comp_a = reg.get_components<A>();
    auto &comp_b = reg.get_components<B>();
    auto &comp_c = reg.get_components<C>();

    auto a_zip = containers::zipper(comp_a);
    auto ab_zip = containers::zipper(comp_a, comp_b);
    auto bc_zip = containers::zipper(comp_b, comp_c);
    auto abc_zip = containers::zipper(comp_a, comp_b, comp_c);

    std::cout << "A TEST" << std::endl;
    for (auto&& [_a] : a_zip) {
        std::cout << "A : " << _a.value().a << std::endl;
    }
    std::cout << std::endl;
    std::cout << "AB TEST" << std::endl;
    for (auto&& [_a, _b] : ab_zip) {
        std::cout << "A : " << _a.value().a << std::endl;
        std::cout << "B : " << _b.value().b << std::endl;
    }
    std::cout << std::endl;
    std::cout << "CB TEST" << std::endl;
    for (auto&& [_b, _c] : bc_zip) {
        std::cout << "B : " << _b.value().b << std::endl;
        std::cout << "C : " << _c.value().c << std::endl;
    }
    std::cout << std::endl;
    std::cout << "ABC TEST" << std::endl;
    for (auto&& [_a, _b, _c] : abc_zip) {
        std::cout << "A : " << _a.value().a << std::endl;
        std::cout << "B : " << _b.value().b << std::endl;
        std::cout << "C : " << _c.value().c << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    reg.add_global_render_system(test, 10);

    reg.render();
}
