/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include "../raylib/buttons/MyButton.hpp"
#include "../raylib/checkbox/Check.hpp"
#include "../raylib/textbox/MyTextBox.hpp"
#include <graphical_library/api/Renderer.hpp>
#include <raylib.h>
#include <vector>

class Renderer : public gl::Renderer
{
public:
    Renderer();
    ~Renderer() override;
    void Draw() override;
    void AddButton(int posX, int posY, int sizeX, int sizeY,
        int transparency, Color color, const std::string& text) override;
    void AddCheckBox(bool checked, int posX, int posY, int size,
        int transparency, Color color, const std::string& text) override;
    void AddTextBox(int posX, int posY, int sizeX, int sizeY,
        int transparency, Color color, const std::string& text) override;
    void Update() override;
    void DeleteButton(size_t i) override;
    void DeleteCheckBox(size_t i) override;
    void DeleteTextBox(size_t i) override;
    void Clear() override;
    gl::Button &GetButton(int i) override;
    const gl::Button &GetButton(int i) const override;
    gl::Checkbox &GetCheckBox(int i) override;
    const gl::Checkbox &GetCheckBox(int i) const override;
    gl::TextBox &GetTextBox(int i) override;
    const gl::TextBox &GetTextBox(int i) const override;

private:
    std::vector<MyCheckBox> checkboxes;
    std::vector<MyButton> buttons;
    std::vector<MyTextBox> textboxes;
};

#endif // RENDERER_HPP_
