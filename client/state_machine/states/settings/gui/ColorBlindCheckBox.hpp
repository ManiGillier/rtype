/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** colorbind button
*/

#ifndef COLORBIND_HPP
#define COLORBIND_HPP

#include "graphical_library/api/Color.hpp"
#include <graphical_library/raylib/checkbox/Checkbox.hpp>

class ColorBindMode : public Checkbox
{
public:
    ColorBindMode()
    : Checkbox()
    {
        this->x = 100;
        this->y = 230;
        this->text = "Colorblind Mode";
        this->idleColor = {200, 0, 0, 255};
        this->hoverColor = {150, 0, 0, 255};
        this->pressedColor =  {200, 200, 0, 200};
        this->checkedColor = {0, 200, 0, 255};
        this->textColor = {255, 255, 255, 255};
        this->size = 75;
    }

    // auto onClick() -> void
    // {
    //     std::cerr << this->text << std::endl;
    // }
};

#endif /* COLORBIND_HPP */
