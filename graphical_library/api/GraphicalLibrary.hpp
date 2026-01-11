/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** client graphical lib
*/

#ifndef CLIENT_GRAPHICAL_LIBRARY_HPP
#define CLIENT_GRAPHICAL_LIBRARY_HPP

#include "Color.hpp"
#include "Sound.hpp"
#include "Text.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "shapes/Rectangle.hpp"

#include <filesystem>
#include <string>

namespace gl {
    class GraphicalLibrary
    {
    public:
        virtual ~GraphicalLibrary() = default;

        virtual auto init() -> void = 0;
        virtual auto deinit() -> void = 0;

        virtual auto get_window_size() -> Vector2ui = 0;
        virtual auto getDeltaTime() -> float = 0;

        virtual auto should_close() -> bool = 0;

        virtual auto start_new_frame(gl::Color color = gl::BLACK) -> void = 0;
        virtual auto end_frame() -> void = 0;

        virtual auto draw(gl::Rectangle rect) -> void = 0;
        virtual auto draw(gl::Text text) -> void = 0;
        virtual auto draw(gl::Texture texture) -> void = 0;

        virtual auto getTextWidth(gl::Text text) -> int = 0;
        virtual auto getTextWidth(const std::string &txt, int fontSize)
            -> int = 0;

        virtual auto registerTexture(std::filesystem::path, std::string)
            -> void = 0;
        virtual auto loadAllTextures() -> void = 0;
        virtual auto loadTexture(std::filesystem::path, std::string)
            -> Texture = 0;
        virtual auto getTexture(std::string) -> Texture = 0;

        virtual auto registerSound(std::filesystem::path, std::string)
            -> void = 0;
        virtual auto loadAllSounds() -> void = 0;
        virtual auto loadSound(std::filesystem::path, std::string)
            -> Sound = 0;
        virtual auto getSound(std::string) -> Sound = 0;
        virtual auto play(Sound) -> void = 0;

        virtual auto loadEverything() -> void = 0;
    };
}

#endif /* CLIENT_GRAPHICAL_LIBRARY_HPP */
