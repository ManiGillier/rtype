/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef TEST_INPUTBOXES_HPP
#define TEST_INPUTBOXES_HPP

#include "../raylib/inputbox/MyInputBox.hpp"

class TestInputBox : public MyInputBox
{
public:
    TestInputBox(int x, int y, int width, int height,
               gl::Color boxColor, gl::Color hoveredBoxColor, int transparency = 255);
    void update() override;

private:
    void onTextChange();
    void onHover();
};

#endif // TEST_INPUTBOXES_HPP
