/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** winning scene
*/

#ifndef LOSE_SCENE_HPP
#define LOSE_SCENE_HPP

#include "client/state_machine/states/lose/gui/BackToLobbyButton.hpp"
#include "client/state_machine/states/lose/gui/DifficultyText.hpp"
#include "client/state_machine/states/lose/gui/DifficultyValue.hpp"
// #include "client/state_machine/states/lose/gui/ScoreText.hpp"
// #include "client/state_machine/states/lose/gui/ScoreValue.hpp"
#include "client/state_machine/states/lose/gui/LoseText.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class LoseScene : public GuiScene
{
public:
    LoseScene(gl::GraphicalLibrary &gl)
    : GuiScene(gl) {}

    auto init() -> void
    {
        this->add<BackToLobbyButton>();
        this->add<DifficultyText>();
        this->add<DifficultyValue>();
        this->add<LoseText>();
    }
};
#endif /* LOSE_SCENE_HPP */
