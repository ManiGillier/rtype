#include ".cpm-cache/raylib/cebd/src/raylib.h"
#include "graphical_library/renderer/Renderer.hpp"
#include <cstdio>
#include <raylib.h>
#include <iostream>

int main()
{
    Renderer window;
    Color badMoche = {74, 65, 42, 255};
    window.AddButton(0, 0, 120, 60, 255, BLUE, "boo-ton");
    window.AddCheckBox(false, 150, 10, 40, 255, GREEN, "");
    window.GetCheckBox(0).SetText("const std::string &str");
    window.AddTextBox(400, 250, 60, 60, 255, badMoche, "");
    window.GetTextBox(0).SetText("12");
    while (!WindowShouldClose())
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        bool isButtonHover = window.GetButton(0).IsHovered(mouseX, mouseY);
        bool isButtonClicked = window.GetButton(0).IsClicked(mouseX, mouseY);
        bool isCheckHover = window.GetCheckBox(0).IsHovered(mouseX, mouseY);
        bool isCheckClicked = window.GetCheckBox(0).IsClicked(mouseX, mouseY);
        if (isButtonHover) {
            window.GetButton(0).SetHoveredColor((Color){ 173, 42, 201, 255 });
        } else {
            window.GetButton(0).SetHoveredColor(BLUE);
        }
        if (isButtonClicked)
            std::cout << "quoi ?" << std::endl;
        if (isCheckHover) {
            window.GetCheckBox(0).SetColor((Color){ 120, 12, 12, 255 });
        } else {
            window.GetCheckBox(0).SetColor(GREEN);
        }
        if (window.GetCheckBox(0).IsChecked()) {
            std::cout << "FEUR 😂😂😂😂😂😂😂" << std::endl;
        }

        window.Draw();
        EndDrawing();
    }
    return 0;
}
