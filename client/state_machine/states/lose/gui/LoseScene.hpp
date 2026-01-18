/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** winning scene
*/

#ifndef LOSE_SCENE_HPP
#define LOSE_SCENE_HPP

#include "client/state_machine/states/lose/Lose.hpp"
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
    LoseScene(gl::GraphicalLibrary &gl, Lose &lose)
    : GuiScene(gl), lose(lose) {}

    auto init() -> void
    {
        this->add<BackToLobbyButton>(lose);
        //this->add<DifficultyText>();
        //this->add<DifficultyValue>();
        this->add<LoseText>();
    }
private:
    Lose &lose;
};
#endif /* LOSE_SCENE_HPP */
