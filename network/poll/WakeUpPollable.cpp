/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** WakeUpPollable
*/

#include "WakeUpPollable.hpp"

WakeUpPollable::WakeUpPollable(PollManager &pm, int fd) : Pollable(fd, pm)
{
    return;
}

short WakeUpPollable::getFlags() const
{
    return POLLIN;
}

bool WakeUpPollable::receiveEvent(short revent)
{
    uint64_t value;

    read(this->getFileDescriptor(), &value, sizeof(value));
    (void) value;
    (void) revent;
    return true;
}
