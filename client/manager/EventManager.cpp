/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** event manager
*/

#include "EventManager.hpp"

auto EventManager::startListenToEvent(EventId id) -> void
{
    this->listenEventList.insert(std::make_pair(id, Event(id)));
}

auto EventManager::stopListenToEvent(EventId id) -> void
{
    this->listenEventList.erase(id);
}

auto EventManager::getEvent(EventId id) const -> Event
{
    return this->listenEventList.at(id);
}

auto EventManager::getEvents() const -> std::map<EventId, Event> const &
{
    return this->listenEventList;
}

auto EventManager::setEventState(EventId id, EventState state) -> void
{
    if (!this->listenEventList.contains(id))
        this->listenEventList.insert(std::make_pair(id, Event(id)));
    this->listenEventList.at(id).setState(state);
}

auto EventManager::lockAccess() -> void
{
    this->mutex.lock();
}

auto EventManager::unlockAccess() -> void
{
    this->mutex.unlock();
}

auto EventManager::resetEventListening() -> void
{
    this->listenEventList.clear();
}
