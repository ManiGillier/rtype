/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef RENDER_H_
#define RENDER_H_

#include <vector>
#include <graphical_library/api/Button.hpp>
#include <graphical_library/api/Check.hpp>

namespace rd {
    class Renderer
    {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;
        virtual void Draw() = 0;
        virtual void AddButton(int posX, int posY, int sizeX, int sizeY,
            int transparency, Color color, const std::string& text) = 0;
        virtual void AddCheckBox(bool checked, int posX, int posY, int size,
            int transparency, Color color, const std::string& text) = 0;
        virtual void DeleteButton(size_t i) = 0;
        virtual void DeleteCheckBox(size_t i) = 0;
        virtual void Clear() = 0;
        virtual auto &GetButton(int i) -> Button = 0;
        virtual auto &GetCheckBox(int i) -> CheckBox = 0;
    };
}
