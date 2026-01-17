/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby button
*/

#ifndef SAVE_KEYS_HPP
#define SAVE_KEYS_HPP

#include <graphical_library/raylib/buttons/Button.hpp>
#include <iostream>

class SaveKeys : public Button
{
public:
    SaveKeys()
    : Button()
    {
        this->x = 1000;
        this->y = 790;
        this->width = 350;
        this->height = 100;
        this->idleColor = {150, 150, 150, 255};
        this->hoverColor = {150, 150, 150, 255};
        this->pressedColor = {150, 150, 150, 255};
        this->text = "Save Keys";
    }

    auto onClick() -> void
    {
        std::cerr << "Just clicked the button !" << std::endl;
    }
};

#endif /* SAVE_KEYS_HPP */
