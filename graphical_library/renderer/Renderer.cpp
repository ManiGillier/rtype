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

void Renderer::Draw()
{
    for (auto &button : buttons)
        button.Draw();
    for (auto &checkbox : checkboxes)
        checkbox.Draw();
    for (auto &textbox : textboxes)
        textbox.Draw();
    for (auto &inputbox : inputboxes)
        inputbox.Draw();
}

void Renderer::AddButton(int posX, int posY, int sizeX, int sizeY,
                         int transparency, Color color,
                         const std::string &text)
{
    buttons.emplace_back(posX, posY, sizeX, sizeY,
                         color, color, transparency);
    buttons.back().SetText(text);
}

void Renderer::AddCheckBox(bool checked, int posX, int posY, int size,
                           int transparency, Color color,
                           const std::string &text)
{
    checkboxes.emplace_back(posX, posY, size, checked, transparency);
    checkboxes.back().SetColor(color);
    checkboxes.back().SetText(text);
}

void Renderer::DeleteButton(size_t i)
{
    if (i < buttons.size())
        buttons.erase(buttons.begin() + i);
}

void Renderer::DeleteCheckBox(size_t i)
{
    if (i < checkboxes.size())
        checkboxes.erase(checkboxes.begin() + i);
}

void Renderer::Clear()
{
    buttons.clear();
    checkboxes.clear();
    textboxes.clear();
    inputboxes.clear();
}

gl::Button &Renderer::GetButton(int i)
{
    return buttons.at(static_cast<size_t>(i));
}

const gl::Button &Renderer::GetButton(int i) const
{
    return buttons.at(static_cast<size_t>(i));
}

gl::Checkbox &Renderer::GetCheckBox(int i)
{
    return checkboxes.at(static_cast<size_t>(i));
}

const gl::Checkbox &Renderer::GetCheckBox(int i) const
{
    return checkboxes.at(static_cast<size_t>(i));
}

void Renderer::AddTextBox(int posX, int posY, int sizeX, int sizeY,
                          int transparency, Color color,
                          const std::string &text)
{
    textboxes.emplace_back(posX, posY, sizeX, sizeY,
                          color, color, transparency);
    textboxes.back().SetText(text);
}

void Renderer::Update()
{
    for (auto &button : buttons)
        button.Update();
    for (auto &checkbox : checkboxes)
        checkbox.Update();
    for (auto &textbox : textboxes)
            textbox.Update();
    for (auto &inputbox : inputboxes)
            inputbox.Update();
    this->Draw();
    return;
}

void Renderer::DeleteTextBox(size_t i)
{
    if (i < textboxes.size())
        textboxes.erase(textboxes.begin() + i);
}

gl::TextBox &Renderer::GetTextBox(int i)
{
    return textboxes.at(static_cast<size_t>(i));
}

const gl::TextBox &Renderer::GetTextBox(int i) const
{
    return textboxes.at(static_cast<size_t>(i));
}

void Renderer::DeleteInputBox(size_t i)
{
    if (i < inputboxes.size())
        inputboxes.erase(inputboxes.begin() + i);
}

const gl::InputBox &Renderer::GetInputBox(int i) const
{
    return inputboxes.at(static_cast<size_t>(i));
}

gl::InputBox &Renderer::GetInputBox(int i)
{
    return inputboxes.at(static_cast<size_t>(i));
}

void Renderer::AddInputBox(int posX, int posY, int sizeX, int sizeY,
                          int transparency, Color color,
                          const std::string &text)
{
    inputboxes.emplace_back(posX, posY, sizeX, sizeY,
                          color, color, transparency);
    (void)text;
}
