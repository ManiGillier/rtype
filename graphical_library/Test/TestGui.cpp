/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "TestGui.hpp"

TestGui::TestGui() : Gui() {
    init();
}

void TestGui::init() {
    this->addButton(100, 100, 200, 50, 255,
                   gl::Color{0, 255, 0, 255},
                   "12 boutons");

    this->addCheckBox(false, 100, 200, 40, 255,
                     gl::Color{255, 0, 255, 255},
                     "12");
}

void TestGui::draw() {
    DrawText("12 aussi", 10, 10, 20, {255, 0, 0, 255});
    Gui::draw();
}
