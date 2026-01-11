/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_HPP
#define CLIENT_GRAPHICAL_LIBRARY_HPP

#include "Color.hpp"
#include "shapes/Rectangle.hpp"
#include "Text.hpp"

namespace gl {
    class GraphicalLibrary
    {
    public:
        virtual ~GraphicalLibrary() = default;

        virtual auto init() -> void = 0;
        virtual auto deinit() -> void = 0;

        virtual auto should_close() -> bool = 0;

        virtual auto start_new_frame(gl::Color color = gl::BLACK) -> void = 0;
        virtual auto end_frame() -> void = 0;

        virtual auto draw(gl::Rectangle rect) -> void = 0;
        virtual auto draw(gl::Text text) -> void = 0;

        virtual auto getTextWidth(gl::Text text) -> int = 0;
        virtual auto getTextWidth(const std::string &txt, int fontSize)
            -> int = 0;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_HPP */
