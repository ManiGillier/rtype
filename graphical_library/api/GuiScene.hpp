/*
** EPITECH PROJECT, 2026
** rtyoe
** File description:
** gui scene
*/

#ifndef GRAPHICAL_LIBRARY_GUI_SCENE_HPP
#define GRAPHICAL_LIBRARY_GUI_SCENE_HPP

namespace gl {
class GuiScene
{
public:
    virtual ~GuiScene() = default;

    virtual auto init() -> void = 0;
    virtual auto draw() -> void = 0;
    virtual auto update() -> void = 0;
};
}

#endif /* GRAPHICAL_LIBRARY_GUI_SCENE_HPP */
