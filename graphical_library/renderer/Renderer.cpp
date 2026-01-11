/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Renderer.hpp"

Renderer::Renderer() {
    InitWindow(900, 600, "Wati-Fenêtre");
    SetTargetFPS(60);
    InitAudioDevice();
}

Renderer::~Renderer() {
    CloseWindow();
    CloseAudioDevice();
}


void Renderer::Draw()
{
    ClearBackground(RAYWHITE);
    for (auto &button : buttons)
        button.Draw();
    for (auto &checkbox : checkboxes)
        checkbox.Draw();
    for (auto &textbox : textboxes)
            textbox.Draw();
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
    (void)i;
}

void Renderer::DeleteCheckBox(size_t i)
{
    (void)i;
}

void Renderer::Clear()
{
    buttons.clear();
    checkboxes.clear();
    textboxes.clear();
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

void Renderer::DeleteTextBox(size_t i)
{
    (void)i;
}

gl::TextBox &Renderer::GetTextBox(int i)
{
    return textboxes.at(static_cast<size_t>(i));
}

const gl::TextBox &Renderer::GetTextBox(int i) const
{
    return textboxes.at(static_cast<size_t>(i));
}
