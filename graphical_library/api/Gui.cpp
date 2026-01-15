/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library gui
*/

#include "Gui.hpp"
#include "GraphicalLibrary.hpp"

gl::Gui::Gui(gl::GraphicalLibrary &gl)
: gl(gl) {}

auto gl::Gui::draw() -> void
{
    for (auto &button : this->buttons)
        button->draw();
    for (auto &checkbox : this->checkboxes)
        checkbox->draw();
    for (auto &textBox : this->textBoxes)
        textBox->draw();
    for (auto &inputBox : this->inputBoxes)
        inputBox->draw();
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
}

auto gl::Gui::addButton(std::unique_ptr<Button> button) -> void
{
    this->buttons.push_back(std::move(button));
}

auto gl::Gui::addCheckbox(std::unique_ptr<Checkbox> checkbox) -> void
{
    this->checkboxes.push_back(std::move(checkbox));
}

auto gl::Gui::addTextBox(std::unique_ptr<TextBox> textBox) -> void
{
    this->textBoxes.push_back(std::move(textBox));
}

auto gl::Gui::addInputBox(std::unique_ptr<InputBox> inputBox) -> void
{
    this->inputBoxes.push_back(std::move(inputBox));
}
