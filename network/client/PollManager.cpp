/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PollManager
*/

#include "PollManager.hpp"
#include "Server.hpp"
#include "IPollable.hpp"
#include "Logger.hpp"
#include "Client.hpp"
#include <poll.h>
#include <unistd.h>
#include <iostream>

void PollManager::addPollable(std::unique_ptr<IPollable> &pollable)
{
    struct pollfd pollDescriptor = {
        .fd = pollable->getFileDescriptor(),
        .events = pollable->getFlags(),
        .revents = 0
    };

    pollables.push_back(std::move(pollable));
    pollFds.push_back(pollDescriptor);
}

void PollManager::removePollable(int fileDescriptor)
{
    int pollableIndex = 0;
    int fdIndex = 0;

    for (std::unique_ptr<IPollable> &pollable : this->pollables) {
        if (pollable->getFileDescriptor() == fileDescriptor)
            break;
        pollableIndex++;
    }
    for (struct pollfd m : this->pollFds) {
        if (m.fd == fileDescriptor)
            break;
        fdIndex++;
    }
    this->pollFds.erase(this->pollFds.begin() + fdIndex);
    this->pollables.erase(this->pollables.begin() + pollableIndex);
    close(fileDescriptor);
}

void PollManager::removePollables(std::vector<int> fileDescriptors)
{
    for (int fileDescriptor : fileDescriptors) {
        LOG_ERR("Client " << fileDescriptor << " disconnected." << std::endl);
        this->removePollable(fileDescriptor);
    }
}

void PollManager::updateFlags(int fileDescriptor, short newFlags)
{
    struct pollfd pollDescriptor = {
        .fd = fileDescriptor,
        .events = newFlags,
        .revents = 0
    };

    for (std::size_t i = 0; i < this->pollFds.size(); i++) {
        if (this->pollFds[i].fd == fileDescriptor)
            this->pollFds[i] = pollDescriptor;
    }
}

int PollManager::getConnectionCount() const
{
    return this->pollables.size();
}

std::vector<std::unique_ptr<IPollable>> &PollManager::getPollables()
{
    return this->pollables;
}

void PollManager::pollSockets(Server *server)
{
    std::size_t socketSize = this->pollFds.size();
    int rc = poll(this->pollFds.data(), socketSize, -1);
    std::vector<int> toDelete;

    if (rc < 0)
        return;
    for (std::size_t i = 0; i < socketSize; i++) {
        if (this->pollFds[i].revents == 0)
            continue;
        if ((this->pollFds[i].revents & POLLHUP) != 0) {
            toDelete.push_back(this->pollFds[i].fd);
            continue;
        }
        if(!this->pollables[i]->receiveEvent(this, this->pollFds[i].revents))
            toDelete.push_back(this->pollFds[i].fd);
        this->pollFds[i].events = this->pollables[i]->getFlags();
        this->pollFds[i].revents = 0;
    }
    this->removePollables(toDelete);
}
