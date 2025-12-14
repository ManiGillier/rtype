/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ecs sync
*/

#include "Sync.hpp"

auto Sync::add(std::size_t my_id, std::size_t their_id) -> void
{
    this->mine_to_theirs[my_id] = their_id;
    this->theirs_to_mine[their_id] = my_id;
}

auto Sync::get_mine_from_theirs(std::size_t their_id) const -> std::size_t
{
    return this->theirs_to_mine.at(their_id);
}

auto Sync::get_theirs_from_mine(std::size_t my_id) const -> std::size_t
{
    return this->mine_to_theirs.at(my_id);
}

auto Sync::del_with_mine(std::size_t my_id) -> void
{
    this->theirs_to_mine.erase(this->get_theirs_from_mine(my_id));
    this->mine_to_theirs.erase(my_id);
}

auto Sync::del_with_theirs(std::size_t their_id) -> void
{
    this->mine_to_theirs.erase(this->get_mine_from_theirs(their_id));
    this->theirs_to_mine.erase(their_id);
}
