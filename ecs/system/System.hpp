/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** system class
*/

#ifndef ECS_SYSTEM_HPP
#define ECS_SYSTEM_HPP

class System
{
  public:
    System() = default;

    // Game update (tick)
    virtual auto update() -> void = 0;
    // Render update (frame)
    virtual auto render() -> void = 0;

  private:
};

class ServerSystem : public System
{
  public:
  private:
    inline auto render() -> void {}
};

#endif /* ECS_SYSTEM_HPP */
