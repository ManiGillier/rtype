/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/
#ifndef TEST_BUTTON_HPP
#define TEST_BUTTON_HPP

#include "../raylib/buttons/MyButton.hpp"

class TestButton : public MyButton
{
public:
    TestButton(int x, int y, int width, int height,
               gl::Color buttonColor, gl::Color hoveredButtonColor, int transparency = 255);
    void update() override;

private:
    void onClick();
    void onHover();
};

#endif // TEST_BUTTON_HPP
