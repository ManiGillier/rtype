/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Raylib.hpp"

#include <raylib.h>

auto Raylib::init() -> void
{
    InitWindow(900, 600, "TODO: Change title");
    SetTargetFPS(60);
}

auto Raylib::deinit() -> void
{
    CloseWindow();
}

auto Raylib::should_close() -> bool
{
    return WindowShouldClose();
}

auto Raylib::start_new_frame(gl::Color color) -> void
{
    BeginDrawing();
    ClearBackground(Color {color.r, color.g, color.b, color.a});
}

auto Raylib::end_frame() -> void
{
    EndDrawing();
}

auto Raylib::draw(gl::Rectangle rect) -> void
{
    DrawRectangle((int) rect.position.x, (int) rect.position.y,
                  (int) rect.size.x, (int) rect.size.y,
                  Color {rect.color.r, rect.color.g, rect.color.b, rect.color.a});
}
