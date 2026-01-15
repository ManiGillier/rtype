/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GUI
*/

#ifndef CLIENT_GUI_HPP
#define CLIENT_GUI_HPP

#include "Button.hpp"
#include "Checkbox.hpp"
#include "TextBox.hpp"
#include "InputBox.hpp"
#include "GraphicalLibrary.hpp"

#include <memory>

namespace gl {
    class Gui
    {
    public:
        Gui(GraphicalLibrary &gl);
        auto draw() -> void;
        auto update() -> void;
        auto addButton(std::unique_ptr<Button>) -> void;
        auto addCheckbox(std::unique_ptr<Checkbox>) -> void;
        auto addTextBox(std::unique_ptr<TextBox>) -> void;
        auto addInputBox(std::unique_ptr<InputBox>) -> void;
    };
}

#endif // CLIENT_GUI_HPP
