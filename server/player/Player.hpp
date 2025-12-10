/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** player
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

// TODO: inherit of client network
class Player
{
  public:
    Player(int id);
    ~Player() = default;
    int getId() const; 

  private:
    int _id;
};

#endif /* PLAYER_HPP */
