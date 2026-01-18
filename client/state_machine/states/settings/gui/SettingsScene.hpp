/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** settings scene
*/

#ifndef SETTINGS_SCENE_HPP
#define SETTINGS_SCENE_HPP

#include "client/state_machine/states/settings/gui/ColorBlindCheckBox.hpp"
#include "client/state_machine/states/settings/gui/DownInput.hpp"
#include "client/state_machine/states/settings/gui/DownText.hpp"
#include "client/state_machine/states/settings/gui/FireText.hpp"
#include "client/state_machine/states/settings/gui/LeftInput.hpp"
#include "client/state_machine/states/settings/gui/LeftText.hpp"
#include "client/state_machine/states/settings/gui/RightInput.hpp"
#include "client/state_machine/states/settings/gui/RightText.hpp"
#include "client/state_machine/states/settings/gui/DeafCheckBox.hpp"
#include "client/state_machine/states/settings/gui/FireInput.hpp"
#include "client/state_machine/states/settings/gui/UpInput.hpp"
#include "client/state_machine/states/settings/gui/UpText.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class SettingsScene : public GuiScene
{
public:
    SettingsScene(gl::GraphicalLibrary &gl)
    : GuiScene(gl), gl(gl) {}

    auto init() -> void
    {
        this->add<ColorBindMode>();
        // this->add<DeafMode>();
        this->add<FireText>();
        this->add<FireInput>(this->gl);
        this->add<DownText>();
        this->add<DownInput>(this->gl);
        this->add<UpText>();
        this->add<UpInput>(this->gl);
        this->add<RightText>();
        this->add<RightInput>(this->gl);
        this->add<LeftText>();
        this->add<LeftInput>(this->gl);
    }
private:
    gl::GraphicalLibrary &gl;
};
#endif /* SETTINGS_SCENE_HPP */
