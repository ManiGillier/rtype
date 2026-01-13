/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** initialisation of graphical library
*/

#ifndef GRAPHICAL_LIBRARY_RAYLIB_INIT_HPP
#define GRAPHICAL_LIBRARY_RAYLIB_INIT_HPP

#include <memory>

#include <graphical_library/api/GraphicalLibrary.hpp>

std::unique_ptr<gl::GraphicalLibrary> init_raylib();

#endif /* GRAPHICAL_LIBRARY_RAYLIB_INIT_HPP */
