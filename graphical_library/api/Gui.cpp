/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library gui
*/

#include "Gui.hpp"
#include "GraphicalLibrary.hpp"
#include "KeybindSelect.hpp"

gl::Gui::Gui(gl::GraphicalLibrary &gl)
: gl(gl) {}

auto gl::Gui::draw() -> void
{
    for (auto &box : this->boxes)
        box->draw();
    for (auto &button : this->buttons)
        button->draw();
    for (auto &checkbox : this->checkboxes)
        checkbox->draw();
    for (auto &inputBox : this->inputBoxes)
        inputBox->draw();
    for (auto &keybindSelect : this->keybindSelects)
        keybindSelect->draw();
    for (auto &textBox : this->textBoxes)
        textBox->draw();
}

auto gl::Gui::update() -> void
{
    for (auto &button : this->buttons)
        button->update();
    for (auto &checkbox : this->checkboxes)
        checkbox->update();
    for (auto &textBox : this->textBoxes)
        textBox->update();
    for (auto &inputBox : this->inputBoxes)
        inputBox->update();
    for (auto &keybindSelect : this->keybindSelects)
        keybindSelect->update();
    for (auto &box : this->boxes)
        box->update();
}

auto gl::Gui::add(std::unique_ptr<Button> button) -> void
{
    this->buttons.push_back(std::move(button));
}

auto gl::Gui::add(std::unique_ptr<Checkbox> checkbox) -> void
{
    this->checkboxes.push_back(std::move(checkbox));
}

auto gl::Gui::add(std::unique_ptr<TextBox> textBox) -> void
{
    this->textBoxes.push_back(std::move(textBox));
}

auto gl::Gui::add(std::unique_ptr<InputBox> inputBox) -> void
{
    this->inputBoxes.push_back(std::move(inputBox));
}

auto gl::Gui::add(std::unique_ptr<KeybindSelect> keybindSelect) -> void
{
    this->keybindSelects.push_back(std::move(keybindSelect));
}

auto gl::Gui::add(std::unique_ptr<Box> box) -> void
{
    this->boxes.push_back(std::move(box));
}
