/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** syncronization class
*/

#ifndef ECS_SYNC_HPP
#define ECS_SYNC_HPP

#include <map>

class Sync
{
public:
    auto add(std::size_t my_id, std::size_t their_id) -> void;
    auto get_mine_from_theirs(std::size_t their_id) const -> std::size_t;
    auto get_theirs_from_mine(std::size_t my_id) const -> std::size_t;
    auto del_with_mine(std::size_t my_id) -> void;
    auto del_with_theirs(std::size_t their_id) -> void;
private:
    std::map<std::size_t, std::size_t> mine_to_theirs;
    std::map<std::size_t, std::size_t> theirs_to_mine;
};

#endif /* ECS_SYNC_HPP */
