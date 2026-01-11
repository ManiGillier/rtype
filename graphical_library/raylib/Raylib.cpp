/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Raylib.hpp"
#include <iostream>

auto Raylib::init() -> void
{
    raylib::InitWindow(900, 600, "TODO: Change title");
    raylib::SetTargetFPS(60);
    raylib::InitAudioDevice();
}

auto Raylib::deinit() -> void
{
    raylib::CloseWindow();
    raylib::CloseAudioDevice();
}

auto Raylib::should_close() -> bool
{
    return raylib::WindowShouldClose();
}

auto Raylib::start_new_frame(gl::Color color) -> void
{
    raylib::BeginDrawing();
    raylib::ClearBackground(raylib::Color {
        color.r,
        color.g,
        color.b,
        color.a
    });
}

auto Raylib::end_frame() -> void
{
    raylib::EndDrawing();
}

auto Raylib::draw(gl::Rectangle rect) -> void
{
    raylib::DrawRectangle((int) rect.position.x, (int) rect.position.y,
                  (int) rect.size.x, (int) rect.size.y,
                  raylib::Color {
                      rect.color.r,
                      rect.color.g,
                      rect.color.b,
                      rect.color.a
                  });
}

auto Raylib::draw(gl::Text text) -> void
{
    raylib::DrawText(text.text.c_str(), text.pos.x, text.pos.y, text.charSize,
        raylib::Color {
            text.color.r,
            text.color.g,
            text.color.b,
            text.color.a
        });
}

auto Raylib::getTextWidth(gl::Text text) -> int
{
    return raylib::MeasureText(text.text.c_str(), text.charSize);
}

auto Raylib::getTextWidth(const std::string &txt, int fontSize) -> int
{
    return raylib::MeasureText(txt.c_str(), fontSize);
}

auto Raylib::registerTexture(std::filesystem::path path, std::string name)
    -> void
{
    this->texturesToLoad.push({name, path});
}

auto Raylib::loadAllTextures() -> void
{
    while (!this->texturesToLoad.empty()) {
        auto [name, path] = this->texturesToLoad.front();

        this->loadTexture(path, name);
        this->texturesToLoad.pop();
    }
}

auto Raylib::loadTexture(std::filesystem::path path, std::string name)
    -> gl::Texture
{
    if (this->textures.contains(name))
        return this->textures.at(name).first;
    gl::Texture texture;
    raylib::Texture raylibTexture = raylib::LoadTexture(path.c_str());

    texture.path = path;
    texture.name = name;
    texture.size = {
        (std::uint32_t) raylibTexture.width,
        (std::uint32_t) raylibTexture.height
    };
    texture.scale = 1.0;
    texture.pos = { 0, 0 };
    texture.rotation = 0.0;

    this->textures[name] = { texture, raylibTexture };
    return texture;
}

auto Raylib::getTexture(std::string name) -> gl::Texture
{
    if (!this->textures.contains(name))
        return { "/dev/null", "error", { 0, 0 }, 0.0, { 0, 0 }, 0.0 };
    return this->textures.at(name).first;
}

auto Raylib::draw(gl::Texture texture) -> void
{
    if (!this->textures.contains(texture.name))
        return;
    raylib::DrawTextureEx(this->textures.at(texture.name).second,
                          { (float) texture.pos.x, (float) texture.pos.y },
                          texture.rotation, texture.scale, raylib::WHITE);
}

auto Raylib::loadEverything() -> void
{
    this->loadAllSounds();
    this->loadAllTextures();
}

auto Raylib::loadSound(std::filesystem::path path, std::string name)
    -> gl::Sound
{
    if (this->sounds.contains(name))
        return this->sounds.at(name).first;
    gl::Sound sound;
    raylib::Sound raylibSound = raylib::LoadSound(path.c_str());

    sound.path = path;
    sound.name = name;
    this->sounds[name] = { sound, raylibSound };
    return sound;
}

auto Raylib::registerSound(std::filesystem::path path, std::string name)
    -> void
{
    this->soundsToLoad.push({name, path});
}

auto Raylib::getSound(std::string name) -> gl::Sound
{
    if (!this->sounds.contains(name))
        return { "/dev/null", "error" };
    return this->sounds.at(name).first;
}

auto Raylib::play(gl::Sound sound) -> void
{
    if (!this->sounds.contains(sound.name))
        return;
    raylib::PlaySound(this->sounds.at(sound.name).second);
}

auto Raylib::loadAllSounds() -> void
{
    while (!this->soundsToLoad.empty()) {
        auto [name, path] = this->soundsToLoad.front();

        this->loadSound(path, name);
        this->soundsToLoad.pop();
    }
}

auto Raylib::get_window_size() -> gl::Vector2ui
{
    return {
        (std::uint32_t) raylib::GetRenderWidth(),
        (std::uint32_t) raylib::GetRenderHeight()
    };
}

auto Raylib::getDeltaTime() -> float
{
    return raylib::GetFrameTime();
}
