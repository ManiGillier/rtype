/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** event manager
*/

#ifndef CLIENT_EVENT_MANAGER_HPP
#define CLIENT_EVENT_MANAGER_HPP

#include "client/event/Event.hpp"
#include <map>
#include <mutex>

class EventManager
{
public:
    /* Logic thread */
    auto startListenToEvent(EventId) -> void;
    auto stopListenToEvent(EventId) -> void;
    auto resetEventListening() -> void;

    /* Both threads */
    auto getEvent(EventId) const -> Event const &;
    auto getEvents() const -> std::map<EventId, Event> const &;
    auto lockAccess() -> void;
    auto unlockAccess() -> void;

    /* Render thread */
    auto setEventState(EventId, EventState) -> void;
private:
    std::mutex mutex;
    std::map<EventId, Event> listenEventList;
};

#endif /* CLIENT_EVENT_MANAGER_HPP */
