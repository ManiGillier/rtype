/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** ecs sync
*/

#include "Sync.hpp"
#include <optional>

auto Sync::add(std::size_t my_id, std::size_t their_id) -> void
{
    this->mine_to_theirs[my_id] = their_id;
    this->theirs_to_mine[their_id] = my_id;
}

auto Sync::get_mine_from_theirs(std::size_t their_id) const
    -> std::optional<std::size_t>
{
    if (!this->theirs_to_mine.contains(their_id))
        return std::nullopt;
    return this->theirs_to_mine.at(their_id);
}

auto Sync::get_theirs_from_mine(std::size_t my_id) const
    -> std::optional<std::size_t>
{
    if (!this->mine_to_theirs.contains(my_id))
        return std::nullopt;
    return this->mine_to_theirs.at(my_id);
}

auto Sync::del_with_mine(std::size_t my_id) -> void
{
    std::optional<std::size_t> their_value = this->get_theirs_from_mine(my_id);
    this->mine_to_theirs.erase(my_id);
    if (!their_value)
        return;
    this->theirs_to_mine.erase(*their_value);
}

auto Sync::del_with_theirs(std::size_t their_id) -> void
{
    std::optional<std::size_t> my_value = this->get_mine_from_theirs(their_id);
    this->theirs_to_mine.erase(their_id);
    if (!my_value)
    this->mine_to_theirs.erase(*my_value);
}
