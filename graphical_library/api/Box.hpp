/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_BOX_HPP
#define CLIENT_BOX_HPP

#include "Color.hpp"
#include <string>

namespace gl {
    class Box {
    public:
        virtual ~Box() = default;
        virtual auto draw() const -> void = 0;
        virtual auto update() -> void = 0;
    protected:
        int x;
        int y;
        int width;
        int height;
        Color color;
    };
}
#endif // CLIENT_BOX_HPP
