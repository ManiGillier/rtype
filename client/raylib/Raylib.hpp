/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef RAYLIB_H_
#define RAYLIB_H_

#include "client/graphical_library/GraphicalLibrary.hpp"

class Raylib : public gl::GraphicalLibrary
{
public:
    auto init() -> void;
    auto deinit() -> void;

    auto should_close() -> bool;

    auto start_new_frame(gl::Color color = gl::BLACK) -> void;
    auto end_frame() -> void;

    auto draw(gl::Rectangle rect) -> void;
};

#endif // RAYLIB_H_
