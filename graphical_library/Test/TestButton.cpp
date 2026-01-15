/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "TestButton.hpp"
#include <iostream>

TestButton::TestButton(int x, int y, int width, int height, 
           gl::Color buttonColor, gl::Color hoveredButtonColor, int transparency)
    : MyButton(x, y, width, height, buttonColor, hoveredButtonColor, transparency) 
{
}

void TestButton::update() {
    MyButton::update();
    
    if (isClicked()) {
        onClick();
    }
    if (isHovered()) {
        onHover();
    }
}

void TestButton::onClick() {
    std::cout << "il a cliqué sur le bouton quel banger" << std::endl;
}

void TestButton::onHover() {
    std::cout << "le gars hover :O" << std::endl;
}

