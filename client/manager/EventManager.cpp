/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** event manager
*/

#include "EventManager.hpp"

auto EventManager::startListenToEvent(EventId id) -> void
{
    this->listenEventList.insert_or_assign(id, Event(id));
}

auto EventManager::stopListenToEvent(EventId id) -> void
{
    this->listenEventList.erase(id);
}

auto EventManager::getEvent(EventId id) const -> Event const &
{
    return this->listenEventList.at(id);
}

auto EventManager::getEvents() const -> std::map<EventId, Event> const &
{
    return this->listenEventList;
}

auto EventManager::setEventState(EventId id, EventState state) -> void
{
    this->listenEventList[id].setState(state);
}

auto EventManager::lockAccess() -> void
{
    this->mutex.lock();
}

auto EventManager::unlockAccess() -> void
{
    this->mutex.unlock();
}
