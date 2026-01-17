/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** settings scene
*/

#ifndef SETTINGS_SCENE_HPP
#define SETTINGS_SCENE_HPP

#include "client/state_machine/states/lobby/gui/Background.hpp"
#include "client/state_machine/states/settings/gui/ColorBlindCheckBox.hpp"
#include "client/state_machine/states/settings/gui/DeafCheckBox.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class SettingsScene : public GuiScene
{
public:
    SettingsScene(gl::GraphicalLibrary &gl)
    : GuiScene(gl) {}

    auto init() -> void
    {
        this->add<Background>();
        this->add<ColorBindMode>();
        this->add<DeafMode>();
    }
};
#endif /* SETTINGS_SCENE_HPP */
