/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include <graphical_library/api/MyCheck.hpp>
#include <string>
#include <raylib.h>

class MyCheckBox : public gl::Checkbox
{
public:
    MyCheckBox(int x, int y, int size, bool checked = false, int transparency = 255);
    void Draw() const override;
    void Update() override;
    bool IsClicked(int mouseX, int mouseY) override;
    bool IsHovered(int mouseX, int mouseY) override;
    bool IsChecked() const override;
    void SetChecked(bool checked) override;
    void Toggle() override;
    void SetPosition(int x, int y) override;
    void SetSize(int size) override;
    void SetTransparency(int transparency) override;
    void SetColor(Color aColor) override;
    void SetText(const std::string& str) override;
    void OnClick() override;
private:
    bool hovered = 0;
    bool checked = 0;
    int posX;
    int posY;
    int size;
    int transparency;
    Color color;
    std::string text;
};

#endif
