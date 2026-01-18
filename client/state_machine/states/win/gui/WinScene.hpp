/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** winning scene
*/

#ifndef WIN_SCENE_HPP
#define WIN_SCENE_HPP

#include "client/state_machine/states/win/Win.hpp"
#include "client/state_machine/states/win/gui/BackToLobbyButton.hpp"
#include "client/state_machine/states/win/gui/DifficultyText.hpp"
#include "client/state_machine/states/win/gui/DifficultyValue.hpp"
// #include "client/state_machine/states/win/gui/ScoreText.hpp"
// #include "client/state_machine/states/win/gui/ScoreValue.hpp"
#include "client/state_machine/states/win/gui/WinText.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class WinScene : public GuiScene
{
public:
    WinScene(gl::GraphicalLibrary &gl, Win &win)
    : GuiScene(gl), win(win) {}

    auto init() -> void
    {
        this->add<BackToLobbyButton>(win);
        //this->add<DifficultyText>();
        //this->add<DifficultyValue>();
        this->add<WinText>();
    }
private:
    Win &win;
};
#endif /* WIN_SCENE_HPP */
