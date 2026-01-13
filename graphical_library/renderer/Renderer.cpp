/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Renderer.hpp"

Renderer::Renderer() {
    InitWindow(900, 600, "RType");
    SetTargetFPS(60);
    InitAudioDevice();
}

Renderer::~Renderer() {
    CloseWindow();
    CloseAudioDevice();
}

void Renderer::draw()
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

void Renderer::addButton(int posX, int posY, int sizeX, int sizeY,
                         int transparency, Color color,
                         const std::string &text)
{
    buttons.emplace_back(posX, posY, sizeX, sizeY,
                         color, color, transparency);
    buttons.back().setText(text);
}

void Renderer::addCheckBox(bool checked, int posX, int posY, int size,
                           int transparency, Color color,
                           const std::string &text)
{
    checkboxes.emplace_back(posX, posY, size, checked, transparency);
    checkboxes.back().setColor(color);
    checkboxes.back().setText(text);
}

void Renderer::deleteButton(size_t i)
{
    if (i < buttons.size())
        buttons.erase(buttons.begin() + (int)i);
}

void Renderer::deleteCheckBox(size_t i)
{
    if (i < checkboxes.size())
        checkboxes.erase(checkboxes.begin() + (int)i);
}

void Renderer::clear()
{
    buttons.clear();
    checkboxes.clear();
    textboxes.clear();
    inputboxes.clear();
}

gl::Button &Renderer::getButton(int i)
{
    return buttons.at(static_cast<size_t>(i));
}

const gl::Button &Renderer::getButton(int i) const
{
    return buttons.at(static_cast<size_t>(i));
}

gl::Checkbox &Renderer::getCheckBox(int i)
{
    return checkboxes.at(static_cast<size_t>(i));
}

const gl::Checkbox &Renderer::getCheckBox(int i) const
{
    return checkboxes.at(static_cast<size_t>(i));
}

void Renderer::addTextBox(int posX, int posY, int sizeX, int sizeY,
                          int transparency, Color color,
                          const std::string &text)
{
    textboxes.emplace_back(posX, posY, sizeX, sizeY,
                          color, color, transparency);
    textboxes.back().setText(text);
}

void Renderer::update()
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

void Renderer::deleteTextBox(size_t i)
{
    if (i < textboxes.size())
        textboxes.erase(textboxes.begin() + (int)i);
}

gl::TextBox &Renderer::getTextBox(int i)
{
    return textboxes.at(static_cast<size_t>(i));
}

const gl::TextBox &Renderer::getTextBox(int i) const
{
    return textboxes.at(static_cast<size_t>(i));
}

void Renderer::deleteInputBox(size_t i)
{
    if (i < inputboxes.size())
        inputboxes.erase(inputboxes.begin() + (int)i);
}

const gl::InputBox &Renderer::getInputBox(int i) const
{
    return inputboxes.at(static_cast<size_t>(i));
}

gl::InputBox &Renderer::getInputBox(int i)
{
    return inputboxes.at(static_cast<size_t>(i));
}

void Renderer::addInputBox(int posX, int posY, int sizeX, int sizeY,
                          int transparency, Color color,
                          const std::string &text)
{
    inputboxes.emplace_back(posX, posY, sizeX, sizeY,
                          color, color, transparency);
    (void)text;
}
