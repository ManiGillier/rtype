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
    window.GetButton(0).SetHoveredColor((Color){ 173, 42, 201, 255 });
    window.AddCheckBox(false, 150, 10, 40, 255, GREEN, "");
    window.GetCheckBox(0).SetText("const std::string &str");
    window.AddTextBox(400, 250, 60, 60, 255, badMoche, "");
    window.GetTextBox(0).SetText("12");
    window.GetTextBox(0).SetHoveredColor((Color){ 255, 255, 255, 255 });
    window.GetCheckBox(0).SetHoveredColor((Color){ 120, 12, 12, 255 });
    window.GetCheckBox(0).SetColor(GREEN);
    window.AddInputBox(50, 400, 600, 60, 12, RAYWHITE, "");
    window.AddButton(650, 400, 60, 60, 255, RAYWHITE, "OK");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        window.Update();
        if (window.GetButton(0).IsClicked())
            std::cout << "quoi ?" << std::endl;
        if (window.GetCheckBox(0).IsChecked()) {
            std::cout << "FEUR 😂😂😂😂😂😂😂" << std::endl;
        }
        if (window.GetButton(1).IsClicked())
            std::cout << window.GetInputBox(0).GetText() << std::endl;

        EndDrawing();
    }
    return 0;
}
