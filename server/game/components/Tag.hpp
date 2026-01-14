/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** tag component
*/

#ifndef COMP_TAG_HPP
#define COMP_TAG_HPP

enum EntityTag {
   PLAYER = 0,
   BOSS,
   BULLET,
   LASER
};

struct Tag {
    EntityTag tag;
};

#endif /* COMP_TAG_HPP */
