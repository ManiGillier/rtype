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

#include <graphical_library/api/GraphicalLibrary.hpp>

class ColorBindMode : public Checkbox
{
public:
    ColorBindMode(gl::GraphicalLibrary &gl)
    : Checkbox(), gl(gl)
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

    inline auto update() -> void {
        this->checked = gl.getGrayscale();
        Checkbox::update();
    }

    auto onCheck() -> void {
        this->gl.setGrayscale(true);
    }

    auto onUncheck() -> void {
        this->gl.setGrayscale(false);
    }
private:
    gl::GraphicalLibrary &gl;
};

#endif /* COLORBIND_HPP */
