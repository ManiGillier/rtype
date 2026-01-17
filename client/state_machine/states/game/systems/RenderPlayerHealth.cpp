/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** render player health in game
*/

#include "../Game.hpp"

auto renderHealth([[maybe_unused]] Registry &r,
    gl::GraphicalLibrary &gl,
    Game &game
)
{
    int const MAX_HEALTH = game.getMaxHealth();
    int const HEALTH = game.getCurrentHealth();

    int const WINDOW_WIDTH = gl.get_window_size().x;
    int const WINDOW_HEIGHT = gl.get_window_size().y;

    int const HEART_WIDTH = 50;
    int const SPACING = 20;

    int const POS_Y = WINDOW_HEIGHT - 100;
    int const START_X = WINDOW_WIDTH - (SPACING + HEART_WIDTH) * (MAX_HEALTH + 1);

    gl::AnimatedSprite sprite = {
        .name = "heart",
        .verticalChoices = 2,
        .animationSteps = 1,
        .finalHeight = HEART_WIDTH * 2,
        .pos = { START_X, POS_Y },
        .rotation = 0.0,
        .animationSpeed = 0,
        .verticalIndex = 0,
        .animationCurrentStep = 0,
        .timeUntilNextStep = 0,
    };

    int posX = START_X;
    for (int i = 0; i < MAX_HEALTH; i++) {
        sprite.pos.x = posX;
        sprite.verticalIndex = (i + 1) > HEALTH ? 1 : 0;
        gl.draw(sprite);
        posX += HEART_WIDTH + SPACING;
    }
}
