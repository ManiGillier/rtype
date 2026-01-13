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
#include "../raylib/inputbox/MyInputBox.hpp"
#include <graphical_library/api/Renderer.hpp>
#include <raylib.h>
#include <vector>

class Renderer : public gl::Renderer
{
public:
    Renderer();
    ~Renderer() override;
    void draw() override;
    void addButton(int posX, int posY, int sizeX, int sizeY,
        int transparency, Color color, const std::string& text) override;
    void addCheckBox(bool checked, int posX, int posY, int size,
        int transparency, Color color, const std::string& text) override;
    void addTextBox(int posX, int posY, int sizeX, int sizeY,
        int transparency, Color color, const std::string& text) override;
    void addInputBox(int posX, int posY, int sizeX, int sizeY,
        int transparency, Color color, const std::string& text) override;
    void update() override;
    void deleteButton(size_t i) override;
    void deleteCheckBox(size_t i) override;
    void deleteTextBox(size_t i) override;
    void deleteInputBox(size_t i) override;
    void clear() override;
    gl::Button &getButton(int i) override;
    const gl::Button &getButton(int i) const override;
    gl::Checkbox &getCheckBox(int i) override;
    const gl::Checkbox &getCheckBox(int i) const override;
    gl::TextBox &getTextBox(int i) override;
    const gl::TextBox &getTextBox(int i) const override;
    gl::InputBox &getInputBox(int i) override;
    const gl::InputBox &getInputBox(int i) const override;

private:
    std::vector<MyCheckBox> checkboxes;
    std::vector<MyButton> buttons;
    std::vector<MyTextBox> textboxes;
    std::vector<MyInputBox> inputboxes;
};

#endif
