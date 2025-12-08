/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** position component
*/

#ifndef ENTITY_TYPE_HPP
#define ENTITY_TYPE_HPP

enum class EntityType {
    PLAYER,
    BOSS,
    PLAYER_BULLET,
    ENEMY_BULLET,
};

struct EntityTag {
    EntityType type;
};

#endif /* ENTITY_TYPE_HPP */
