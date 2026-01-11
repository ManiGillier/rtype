/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#ifndef CLIENT_CHECKBOX_HPP
#define CLIENT_CHECKBOX_HPP
#include <raylib.h>
#include <string>


namespace gl {
    class Checkbox {
    public:
        virtual ~Checkbox() = default;
        virtual auto Draw() const -> void = 0;
        virtual auto Update() -> void = 0;
        virtual auto IsClicked(int mouseX, int mouseY) -> bool = 0;
        virtual auto IsHovered(int mouseX, int mouseY) -> bool = 0;
        virtual auto IsChecked() const -> bool = 0;
        virtual auto SetChecked(bool checked) -> void = 0;
        virtual auto Toggle() -> void = 0;
        virtual auto SetPosition(int x, int y) -> void = 0;
        virtual auto SetSize(int size) -> void = 0;
        virtual auto SetTransparency(int transparency) -> void = 0;
        virtual auto SetColor(Color color) -> void = 0;
        virtual auto SetText(const std::string& str) -> void = 0;
        virtual auto OnClick() -> void = 0;
    };
}
#endif
