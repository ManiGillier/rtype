/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** event
*/

#ifndef CLIENT_EVENT_HPP
#define CLIENT_EVENT_HPP

#include "EventId.hpp"
#include "EventState.hpp"

class Event
{
public:
    Event(EventId id) : id(id) {}
    Event(const Event &evt) : id(evt.getId()), state(evt.getState()) {}

    auto getId() const -> EventId { return this->id; }

    auto setState(EventState state) -> void { this->state = state; }
    auto getState() const -> EventState { return this->state; }
private:
    const EventId id;
    EventState state = EventState(false);
};

#endif /* CLIENT_EVENT_HPP */
