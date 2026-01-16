#include ".cpm-cache/raylib/cebd/src/raylib.h"
#include "graphical_library/renderer/Renderer.hpp"
#include <cstdio>
#include <raylib.h>
#include <iostream>

int main()
{
    Renderer window;
    Color badMoche = {74, 65, 42, 255};
    window.addButton(0, 0, 120, 60, 255, BLUE, "boo-ton");
    window.getButton(0).setHoveredColor((Color){ 173, 42, 201, 255 });
    window.addCheckBox(false, 150, 10, 40, 255, GREEN, "");
    window.getCheckBox(0).setText("const std::string &str");
    window.addTextBox(400, 250, 60, 60, 255, badMoche, "");
    window.getTextBox(0).setText("12");
    window.getTextBox(0).setHoveredColor({ 255, 255, 255, 255 });
    window.getCheckBox(0).setHoveredColor({ 120, 12, 12, 255 });
    window.getCheckBox(0).setColor(GREEN);
    window.addInputBox(50, 400, 600, 60, 12, RAYWHITE, "");
    window.addButton(650, 400, 60, 60, 255, RAYWHITE, "OK");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        window.update();
        if (window.getButton(0).isClicked())
            std::cout << "quoi ?" << std::endl;
        if (window.getCheckBox(0).isChecked()) {
            std::cout << "FEUR 😂😂😂😂😂😂😂" << std::endl;
        }
        if (window.getButton(1).isClicked())
            std::cout << window.getInputBox(0).getText() << std::endl;

        EndDrawing();
    }
    return 0;
}
