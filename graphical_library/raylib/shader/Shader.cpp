/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** shader
*/

#include "Shader.hpp"

void Shader::load(std::filesystem::path path)
{
    this->shader = raylib::LoadShader(0, path.c_str());
}

void Shader::unload()
{
    raylib::UnloadShader(this->shader);
}

void Shader::start()
{
    if (raylib::IsShaderValid(this->shader))
        raylib::BeginShaderMode(this->shader);
}

void Shader::end()
{
    raylib::EndShaderMode();
}
