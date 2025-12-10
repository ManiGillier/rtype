/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** gui
*/

#ifndef CLIENT_GUI_HPP
#define CLIENT_GUI_HPP

#include "ecs/regisrty/Registry.hpp"

class GUI {
public:
    virtual ~GUI() = default;

    virtual auto render(Registry &) -> void = 0;
};

#endif /* CLIENT_GUI_HPP */
