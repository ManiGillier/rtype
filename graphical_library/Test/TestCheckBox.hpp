/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef TEST_CHECKBOX_HPP
#define TEST_CHECKBOX_HPP
#include "../raylib/checkbox/Check.hpp"

class TestCheckbox : public MyCheckBox
{
public:
    TestCheckbox(int x, int y, int size, bool checked, int transparency = 255);
    void update() override;

private:
    void onCheck();
    void onHover();
};

#endif // TEST_CHECKBOX_HPP
