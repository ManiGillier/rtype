/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PollManager
*/

#include <network/poll/PollManager.hpp>
#include <network/server/Server.hpp>
#include <network/poll/IPollable.hpp>
#include <network/logger/Logger.hpp>
#include <iostream>
#include "PollManager.hpp"

void PollManager::addPollable(std::shared_ptr<IPollable> pollable)
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

    for (std::shared_ptr<IPollable> &pollable : this->pollables) {
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
        LOG_ERR("Client " << fileDescriptor << " disconnected.");
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

std::size_t PollManager::getConnectionCount() const
{
    return this->pollables.size();
}

std::vector<std::shared_ptr<IPollable>> &PollManager::getPool()
{
    return this->pollables;
}

void PollManager::pollSockets()
{
    std::size_t socketSize = this->pollFds.size();
    LOG("Connected client size: " << this->pollFds.size());
    int rc = poll(this->pollFds.data(), socketSize, -1);
    std::vector<int> toDelete;

    if (rc < 0)
        return;
    this->lock();
    for (std::size_t i = 0; i < socketSize; i++) {
        if (this->pollFds[i].revents == 0)
            continue;
        if ((this->pollFds[i].revents & POLLHUP) != 0) {
            toDelete.push_back(this->pollFds[i].fd);
            continue;
        }
        if(!this->pollables[i]->receiveEvent(this->pollFds[i].revents))
            toDelete.push_back(this->pollFds[i].fd);
        this->pollFds[i].events = this->pollables[i]->getFlags();
        this->pollFds[i].revents = 0;
    }
    this->removePollables(toDelete);
    this->unlock();
}

void PollManager::clear()
{
    for (struct pollfd &fd : this->pollFds)
        close(fd.fd);
    this->pollFds.clear();
    this->pollables.clear();
}

void PollManager::lock() { this->mutex.lock(); }
void PollManager::unlock() { this->mutex.unlock(); }
