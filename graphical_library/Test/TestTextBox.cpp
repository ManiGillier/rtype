/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "TestTextBox.hpp"
#include <iostream>

TestTextBox::TestTextBox(int x, int y, int width, int height,
           gl::Color boxColor, gl::Color hoveredBoxColor, int transparency)
    : MyTextBox(x, y, width, height, boxColor, hoveredBoxColor, transparency)
{
}

void TestTextBox::update() {
    MyTextBox::update();

    if (isHovered()) {
        onHover();
    }
}

void TestTextBox::onHover() {
    std::cout << "Hover sur la textbox" << std::endl;
}
