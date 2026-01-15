/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef TEST_TEXTBOXES_HPP
#define TEST_TEXTBOXES_HPP

#include "../raylib/textbox/MyTextBox.hpp"

class TestTextBox : public MyTextBox
{
public:
    TestTextBox(int x, int y, int width, int height,
               gl::Color boxColor, gl::Color hoveredBoxColor, int transparency = 255);
    void update() override;

private:
    void onHover();
};

#endif // TEST_TEXTBOXES_HPP
