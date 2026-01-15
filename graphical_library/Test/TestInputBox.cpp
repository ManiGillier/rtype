/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "TestInputBox.hpp"
#include <iostream>

TestInputBox::TestInputBox(int x, int y, int width, int height,
           gl::Color boxColor, gl::Color hoveredBoxColor, int transparency)
    : MyInputBox(x, y, width, height, boxColor, hoveredBoxColor, transparency)
{
}

void TestInputBox::update() {
    std::string oldText = getText();

    MyInputBox::update();

    if (getText() != oldText) {
        onTextChange();
    }
    if (isHovered()) {
        onHover();
    }
}


void TestInputBox::onTextChange() {
    std::cout << getText() << std::endl;
}

void TestInputBox::onHover() {
    std::cout << "La souris est sur moi 🥺" << std::endl;
}
