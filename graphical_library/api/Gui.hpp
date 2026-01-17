/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GUI
*/

#ifndef CLIENT_GUI_HPP
#define CLIENT_GUI_HPP

#include "Box.hpp"
#include "Button.hpp"
#include "Checkbox.hpp"
#include "KeybindSelect.hpp"
#include "TextBox.hpp"
#include "InputBox.hpp"
#include "GraphicalLibrary.hpp"

#include <memory>
#include <vector>

namespace gl {
    class Gui
    {
    public:
        Gui(GraphicalLibrary &gl);
        auto draw() -> void;
        auto update() -> void;
        auto add(std::unique_ptr<Button>) -> void;
        auto add(std::unique_ptr<Checkbox>) -> void;
        auto add(std::unique_ptr<TextBox>) -> void;
        auto add(std::unique_ptr<InputBox>) -> void;
        auto add(std::unique_ptr<KeybindSelect>) -> void;
        auto add(std::unique_ptr<Box>) -> void;
    private:
        [[maybe_unused]] GraphicalLibrary &gl;
        std::vector<std::unique_ptr<Button>> buttons;
        std::vector<std::unique_ptr<Checkbox>> checkboxes;
        std::vector<std::unique_ptr<TextBox>> textBoxes;
        std::vector<std::unique_ptr<InputBox>> inputBoxes;
        std::vector<std::unique_ptr<KeybindSelect>> keybindSelects;
        std::vector<std::unique_ptr<Box>> boxes;
    };
}

#endif // CLIENT_GUI_HPP
