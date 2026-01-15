/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef TEST_GUI_HPP
#define TEST_GUI_HPP

#include "../gui/Gui.hpp"

class TestGui : public Gui
{
public:
    TestGui();
    void init();
    void draw() override;
};

#endif // TEST_GUI_HPP
