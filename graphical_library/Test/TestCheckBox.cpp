/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "TestCheckBox.hpp"
#include <iostream>
#include <raylib.h>

TestCheckbox::TestCheckbox(int x, int y, int size, bool checked, int transparency)
    : MyCheckBox(x, y, size, checked, transparency)
{
}

void TestCheckbox::update() {
    MyCheckBox::update();

    if (isChecked()) {
        onCheck();
    }
    if (isHovered()) {
        onHover();
    }
}

void TestCheckbox::onCheck() {
    std::cout << "Je suis coché" << std::endl;
}

void TestCheckbox::onHover() {
    std::cout << "La souris est sur moi 🥺" << std::endl;
}
