/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef RAYLIB_H_
#define RAYLIB_H_

#include <graphical_library/api/GraphicalLibrary.hpp>

class Raylib : public gl::GraphicalLibrary
{
public:
    auto init() -> void;
    auto deinit() -> void;

    auto should_close() -> bool;

    auto start_new_frame(gl::Color color = gl::BLACK) -> void;
    auto end_frame() -> void;

    auto draw(gl::Rectangle rect) -> void;
    auto draw(gl::Text text) -> void;

    auto getTextWidth(gl::Text text) -> int;
    auto getTextWidth(const std::string &txt, int fontSize) -> int;
};

#endif // RAYLIB_H_
