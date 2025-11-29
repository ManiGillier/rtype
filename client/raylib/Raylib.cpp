/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include <raylib.h>
#include <thread>


#include "Raylib.hpp"

Raylib::Raylib()
{
    this->openGlThread = std::thread(&Raylib::init, this);
}

auto Raylib::init() -> void
{
    InitWindow(this->window.getWidth(),
               this->window.getHeight(),
               this->window.getTitle());

    this->loop();
}
