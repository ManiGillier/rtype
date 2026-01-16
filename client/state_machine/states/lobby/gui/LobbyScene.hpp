/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby scene
*/

#ifndef TEST_LOBBY_SCENE_HPP
#define TEST_LOBBY_SCENE_HPP

#include "client/state_machine/states/lobby/gui/Difficulty.hpp"
#include "client/state_machine/states/lobby/gui/DifficultyNumber.hpp"
#include "client/state_machine/states/lobby/gui/Lives.hpp"
#include "client/state_machine/states/lobby/gui/LivesNumber.hpp"
#include "client/state_machine/states/lobby/gui/MinusDifficulty.hpp"
#include "client/state_machine/states/lobby/gui/MinusLives.hpp"
#include "client/state_machine/states/lobby/gui/PlusDifficulty.hpp"
#include "client/state_machine/states/lobby/gui/PlusLives.hpp"
#include "client/state_machine/states/lobby/gui/RoomCode.hpp"
#include "client/state_machine/states/lobby/gui/StartButton.hpp"
#include <graphical_library/raylib/GuiScene.hpp>

class LobbyScene : public GuiScene
{
public:
    LobbyScene(gl::GraphicalLibrary &gl) : GuiScene(gl) {}

    auto init() -> void
    {
        // this->add<TestLobbyButton>();
        this->add<Difficulty>();
        this->add<MinusDifficulty>();
        this->add<PlusDifficulty>();
        this->add<PlusLives>();
        this->add<Lives>();
        this->add<LivesNumber>();
        this->add<MinusLives>();
        this->add<DifficultyNumber>();
        this->add<StartButton>();
        this->add<RoomCode>();
    }
};

#endif /* TEST_LOBBY_SCENE_HPP */
