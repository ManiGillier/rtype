/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../raylib/buttons/MyButton.hpp"
#include "../raylib/checkbox/Check.hpp"
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
    void DeleteButton(size_t i) override;
    void DeleteCheckBox(size_t i) override;
    void Clear() override;
    gl::Button &GetButton(int i) override;
        const gl::Button &GetButton(int i) const override;
        gl::Checkbox &GetCheckBox(int i) override;
        const gl::Checkbox &GetCheckBox(int i) const override;
private:
    std::vector<MyCheckBox> checkboxes;
    std::vector<MyButton> buttons;
};

#endif // RENDERER_HPP_
