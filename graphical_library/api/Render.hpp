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
    class Render
    {
    public:
        Render() = default;
        virtual ~Render() = default;
        virtual void Draw() = 0;
        virtual void AddButton(int posX, int posY, int sizeX, int sizeY,
            int transparency, Color color, const std::string& text) = 0;
        virtual void AddCheckBox(bool checked, int posX, int posY, int size,
            int transparency, Color color, const std::string& text) = 0;
        virtual void DeleteButton(size_t i) = 0;
        virtual void DeleteCheckBox(size_t i) = 0;
        virtual void Clear() = 0;
        virtual auto getButton(int i) -> Button = 0;
        virtual auto getCheckBox(int i) -> Button = 0;
    };
}
