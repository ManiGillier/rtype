/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Gui.hpp"

Gui::Gui() {
    InitWindow(900, 600, "RType");
    SetTargetFPS(60);
    InitAudioDevice();
}

Gui::~Gui() {
    CloseWindow();
    CloseAudioDevice();
}

void Gui::draw()
{
    for (auto &button : buttons)
        button.draw();
    for (auto &checkbox : checkboxes)
        checkbox.draw();
    for (auto &textbox : textboxes)
        textbox.draw();
    for (auto &inputbox : inputboxes)
        inputbox.draw();
}

void Gui::addButton(int posX, int posY, int sizeX, int sizeY,
                         int transparency, gl::Color color,
                         const std::string &text)
{
    buttons.emplace_back(posX, posY, sizeX, sizeY,
                         color, color, transparency);
    buttons.back().setText(text);
}

void Gui::addCheckBox(bool checked, int posX, int posY, int size,
                           int transparency, gl::Color color,
                           const std::string &text)
{
    checkboxes.emplace_back(posX, posY, size, checked, transparency);
    checkboxes.back().setColor(color);
    checkboxes.back().setText(text);
}

void Gui::deleteButton(size_t i)
{
    if (i < buttons.size())
        buttons.erase(buttons.begin() + (int)i);
}

void Gui::deleteCheckBox(size_t i)
{
    if (i < checkboxes.size())
        checkboxes.erase(checkboxes.begin() + (int)i);
}

void Gui::clear()
{
    buttons.clear();
    checkboxes.clear();
    textboxes.clear();
    inputboxes.clear();
}

gl::Button &Gui::getButton(int i)
{
    return buttons.at(static_cast<size_t>(i));
}

const gl::Button &Gui::getButton(int i) const
{
    return buttons.at(static_cast<size_t>(i));
}

gl::Checkbox &Gui::getCheckBox(int i)
{
    return checkboxes.at(static_cast<size_t>(i));
}

const gl::Checkbox &Gui::getCheckBox(int i) const
{
    return checkboxes.at(static_cast<size_t>(i));
}

void Gui::addTextBox(int posX, int posY, int sizeX, int sizeY,
                          int transparency, gl::Color color,
                          const std::string &text)
{
    textboxes.emplace_back(posX, posY, sizeX, sizeY,
                          color, color, transparency);
    textboxes.back().setText(text);
}

void Gui::update()
{
    for (auto &button : buttons)
        button.update();
    for (auto &checkbox : checkboxes)
        checkbox.update();
    for (auto &textbox : textboxes)
            textbox.update();
    for (auto &inputbox : inputboxes)
            inputbox.update();
    this->draw();
    return;
}

void Gui::deleteTextBox(size_t i)
{
    if (i < textboxes.size())
        textboxes.erase(textboxes.begin() + (int)i);
}

gl::TextBox &Gui::getTextBox(int i)
{
    return textboxes.at(static_cast<size_t>(i));
}

const gl::TextBox &Gui::getTextBox(int i) const
{
    return textboxes.at(static_cast<size_t>(i));
}

void Gui::deleteInputBox(size_t i)
{
    if (i < inputboxes.size())
        inputboxes.erase(inputboxes.begin() + (int)i);
}

const gl::InputBox &Gui::getInputBox(int i) const
{
    return inputboxes.at(static_cast<size_t>(i));
}

gl::InputBox &Gui::getInputBox(int i)
{
    return inputboxes.at(static_cast<size_t>(i));
}

void Gui::addInputBox(int posX, int posY, int sizeX, int sizeY,
                          int transparency, gl::Color color,
                          const std::string &text)
{
    inputboxes.emplace_back(posX, posY, sizeX, sizeY,
                          color, color, transparency);
    (void)text;
}
