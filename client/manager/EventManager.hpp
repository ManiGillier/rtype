/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** event manager
*/

#ifndef CLIENT_EVENT_MANAGER_HPP
#define CLIENT_EVENT_MANAGER_HPP

class EventManager
{
public:
    /* Logic thread */
    auto startListenToEvent(/*Define event enum*/) -> void;
    auto stopListenToEvent(/*Define event enum*/) -> void;
    auto resetEventListening() -> void;

    /* Both threads */
    auto getEvent(/*Define event enum*/) -> /*Define events*/ void;
    auto getEvents() -> /*Define events*/ void;

    /* Render thread */
    auto setEventState(/*Define events*/) -> void;
private:
    /* Factory for events */
    /* Vector of events to listen to */
    /* Event contains event state (and default one) */
};

#endif /* CLIENT_EVENT_MANAGER_HPP */
