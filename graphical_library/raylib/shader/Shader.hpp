/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** shader
*/

#ifndef SHADER_HPP
#define SHADER_HPP

#include "IShader.hpp"
#include <filesystem>

namespace raylib {
    #include <raylib.h>
}

class Shader : public IShader
{
public:
    void load(std::filesystem::path path);
    void unload();
    void start();
    void end();
private:
    raylib::Shader shader;
};

#endif /* SHADER_HPP */
