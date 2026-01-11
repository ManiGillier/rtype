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
    InitAudioDevice();
}

auto Raylib::deinit() -> void
{
    CloseWindow();
    CloseAudioDevice();
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

auto Raylib::draw(gl::Text text) -> void
{
    DrawText(text.text.c_str(), text.pos.x, text.pos.y, text.charSize,
        Color {text.color.r, text.color.g, text.color.b, text.color.a});
}

auto Raylib::getTextWidth(gl::Text text) -> int
{
    return MeasureText(text.text.c_str(), text.charSize);
}

auto Raylib::getTextWidth(const std::string &txt, int fontSize) -> int
{
    return MeasureText(txt.c_str(), fontSize);
}
