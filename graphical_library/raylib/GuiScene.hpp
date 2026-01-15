/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** gui scene raylib
*/

#ifndef RAYLIB_GUI_SCENE_HPP
#define RAYLIB_GUI_SCENE_HPP

#include <graphical_library/api/GuiScene.hpp>
#include <graphical_library/api/Gui.hpp>

class GuiScene : public gl::GuiScene
{
public:
    GuiScene(gl::GraphicalLibrary &gl);

    auto draw() -> void;
    auto update() -> void;

    template<class Type, class... Args>
    auto add(Args&&... args) {
        this->gui.add(std::make_unique<Type>(args...));
    }
private:
    gl::Gui gui;
};

#endif /* RAYLIB_GUI_SCENE_HPP */
