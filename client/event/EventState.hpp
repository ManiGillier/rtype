/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** event state
*/

#ifndef CLIENT_EVENT_STATE_HPP
#define CLIENT_EVENT_STATE_HPP

#include "EventId.hpp"

class EventState {
public:
    EventState(bool activated = false) : activated(activated) {}

    auto isActivated() const -> bool { return this->activated; }
    auto activate() -> void { this->activated = true; }
    auto deactivate() -> void { this->activated = false; }
    auto setActive(bool activated) -> void { this->activated = activated; }
private:
    bool activated;
};

#endif /* CLIENT_EVENT_STATE_HPP */
