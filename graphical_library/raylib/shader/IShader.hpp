/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** IShader
*/

#ifndef SHADER_API_HPP
#define SHADER_API_HPP

#include <filesystem>
class IShader
{
public:
    virtual ~IShader() = default;

    virtual void load(std::filesystem::path) = 0;
    virtual void unload() = 0;
    virtual void start() = 0;
    virtual void end() = 0;
};

#endif /* SHADER_MANAGER_API_HPP */
