/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CLIENT_RENDERER_HPP
#define CLIENT_RENDERER_HPP

#include <graphical_library/api/MyButton.hpp>
#include <graphical_library/api/MyCheck.hpp>
#include <graphical_library/api/MyTextBox.hpp>

namespace gl {
    class Renderer
    {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;
        virtual void Draw() = 0;
        virtual void AddButton(int posX, int posY, int sizeX, int sizeY,
            int transparency, Color color, const std::string &text) = 0;
        virtual void AddCheckBox(bool checked, int posX, int posY, int size,
            int transparency, Color color, const std::string &text) = 0;
        virtual auto Update() -> void = 0;
        virtual void DeleteButton(size_t i) = 0;
        virtual void DeleteCheckBox(size_t i) = 0;
        virtual void Clear() = 0;
        virtual const Button &GetButton(int i) const = 0;
        virtual const Checkbox &GetCheckBox(int i) const = 0;
        virtual Button &GetButton(int i) = 0;
        virtual Checkbox &GetCheckBox(int i) = 0;
        virtual void AddTextBox(int posX, int posY, int sizeX, int sizeY,
            int transparency, Color color, const std::string& text) = 0;
        virtual void DeleteTextBox(size_t i) = 0;
        virtual TextBox &GetTextBox(int i) = 0;
        virtual const TextBox &GetTextBox(int i) const = 0;
    };
}
#endif // RENDERER_HPP_
