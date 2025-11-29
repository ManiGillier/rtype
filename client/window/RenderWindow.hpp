/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** render window
*/

#ifndef RENDER_WINDOW_HPP
#define RENDER_WINDOW_HPP

#include <cstddef>
#include <string>

typedef int window_size_type;

class RenderWindow {
public:
    auto getWidth() const { return this->width; }
    auto getHeight() const { return this->height; }
    auto getTitle() const { return this->title.c_str(); }
    auto isMaximized() const { return this->maximized; }

    auto setWidth(window_size_type) -> void;
    auto setHeight(window_size_type) -> void;
    auto setTitle(const std::string &title) -> void;
    auto maximizeToggle() -> void;
private:
    window_size_type width = 800;
    window_size_type height = 600;
    std::string title = "R-Type";
    bool maximized = false;
};

#endif /* RENDER_WINDOW_HPP */
