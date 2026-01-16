/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** gui scene raylib
*/

#include "GuiScene.hpp"

#include <memory>

GuiScene::GuiScene(gl::GraphicalLibrary &gl)
    : gl::GuiScene(), gui(gl) {}

auto GuiScene::draw() -> void
{
    this->gui.draw();
}

auto GuiScene::update() -> void
{
    this->gui.update();
}
