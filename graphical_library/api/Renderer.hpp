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
#include <graphical_library/api/MyInputBox.hpp>

namespace gl {
    class Renderer
    {
    public:
        Renderer() = default;
        virtual ~Renderer() = default;
        virtual void draw() = 0;
        virtual void addButton(int posX, int posY, int sizeX, int sizeY,
            int transparency, Color color, const std::string &text) = 0;
        virtual void addCheckBox(bool checked, int posX, int posY, int size,
            int transparency, Color color, const std::string &text) = 0;
        virtual auto update() -> void = 0;
        virtual void deleteButton(size_t i) = 0;
        virtual void deleteCheckBox(size_t i) = 0;
        virtual void clear() = 0;
        virtual const Button &getButton(int i) const = 0;
        virtual const Checkbox &getCheckBox(int i) const = 0;
        virtual Button &getButton(int i) = 0;
        virtual Checkbox &getCheckBox(int i) = 0;
        virtual void addTextBox(int posX, int posY, int sizeX, int sizeY,
            int transparency, Color color, const std::string& text) = 0;
        virtual void deleteTextBox(size_t i) = 0;
        virtual TextBox &getTextBox(int i) = 0;
        virtual const TextBox &getTextBox(int i) const = 0;
        virtual void addInputBox(int posX, int posY, int sizeX, int sizeY,
                    int transparency, Color color, const std::string& text) = 0;
        virtual void deleteInputBox(size_t i) = 0;
        virtual InputBox &getInputBox(int i) = 0;
        virtual const InputBox &getInputBox(int i) const = 0;
    };
}
#endif // RENDERER_HPP_
