/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** test lobby scene
*/

#ifndef TEST_LOBBY_SCENE_HPP
#define TEST_LOBBY_SCENE_HPP

#include "client/state_machine/states/lobby/gui/Background.hpp"
#include "client/state_machine/states/lobby/gui/SecondBackground.hpp"
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

#include "../Lobby.hpp"

class LobbyScene : public GuiScene
{
public:
    LobbyScene(gl::GraphicalLibrary &gl, Lobby &lobby)
    : GuiScene(gl), lobby(lobby) {}

    auto init() -> void
    {
        // this->add<TestLobbyButton>();
        this->add<Background>();
        this->add<SecondBackground>();
        this->add<Difficulty>();
        this->add<MinusDifficulty>(this->lobby);
        this->add<PlusDifficulty>(this->lobby);
        this->add<PlusLives>(this->lobby);
        this->add<Lives>();
        this->add<LivesNumber>(this->lobby);
        this->add<MinusLives>(this->lobby);
        this->add<DifficultyNumber>(this->lobby);
        this->add<StartButton>();
        this->add<RoomCode>(this->lobby.getCode());
    }
private:
    Lobby &lobby;
};

#endif /* TEST_LOBBY_SCENE_HPP */
