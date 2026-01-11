/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** raylib
*/

#include "Raylib.hpp"

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
    for (auto [name, path] = this->texturesToLoad.front();
         !this->texturesToLoad.empty();
         this->texturesToLoad.pop())
    {
        this->loadTexture(path, name);
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
