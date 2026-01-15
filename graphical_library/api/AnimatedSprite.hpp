/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** graphical library animated sprite
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_ANIMATED_SPRITE_HPP
#define CLIENT_GRAPHICAL_LIBRARY_ANIMATED_SPRITE_HPP

#include "Vector.hpp"
#include <cstdint>
#include <string>
namespace gl {
    struct AnimatedSprite {
        std::string name;
        uint32_t verticalChoices;
        uint32_t animationSteps;
        uint32_t finalHeight;
        Vector2i pos;
        float rotation;
        float animationSpeed; // step.s⁻¹

        uint32_t verticalIndex;
        uint32_t animationCurrentStep;
        float timeUntilNextStep; // s
    };
};

#endif /* CLIENT_GRAPHICAL_LIBRARY_ANIMATED_SPRITE_HPP */
