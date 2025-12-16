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
#include <network/poll/WakeUpPollable.hpp>
#include "PollManager.hpp"

#include <sys/eventfd.h>
#include <unistd.h>

PollManager::PollManager()
{
    std::shared_ptr<IPollable> eventPollable = std::make_shared<WakeUpPollable>(*this,
        eventfd(0, EFD_NONBLOCK));

    this->addPollable(eventPollable);
    this->eventFd = eventPollable->getFileDescriptor();
}

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

std::shared_ptr<IPollable> PollManager::removePollable(int fileDescriptor)
{
    int pollableIndex = 0;
    int fdIndex = 0;
    int pollableIndexReal = -1;
    int fdIndexReal = -1;
    std::shared_ptr<IPollable> toReturn = nullptr;

    for (std::shared_ptr<IPollable> &pollable : this->pollables) {
        if (pollable->getFileDescriptor() == fileDescriptor)
            pollableIndexReal = pollableIndex;
        pollableIndex++;
    }
    for (struct pollfd m : this->pollFds) {
        if (m.fd == fileDescriptor)
            fdIndexReal = fdIndex;
        fdIndex++;
    }
    if (pollableIndexReal != -1) {
        toReturn = this->pollables[(std::size_t) pollableIndexReal];
        this->pollables.erase(this->pollables.begin() + pollableIndexReal);
    }
    if (fdIndexReal != -1) {
        this->pollFds.erase(this->pollFds.begin() + fdIndexReal);
    }
    close(fileDescriptor);
    return toReturn;
}

std::vector<std::shared_ptr<IPollable>> PollManager::removePollables(std::vector<int> fileDescriptors)
{
    std::vector<std::shared_ptr<IPollable>> pollables;

    for (int fileDescriptor : fileDescriptors)
        pollables.push_back(this->removePollable(fileDescriptor));
    return pollables;
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

std::shared_ptr<IPollable> PollManager::getPollableByAddress(sockaddr_in s)
{
    for (std::shared_ptr<IPollable> &p : this->getPool()) {
        std::optional<sockaddr_in> addr = p->getClientAddress();
        if (addr.has_value()) {
            if (addr.value().sin_addr.s_addr == s.sin_addr.s_addr &&
                addr.value().sin_port == s.sin_port) {
                return p;
            }
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<IPollable>> PollManager::pollSockets(int timeout)
{
    std::size_t socketSize = this->pollFds.size();
    LOG("Connected client size: " << this->pollFds.size());

    isPolling.store(true);
    int rc = poll(this->pollFds.data(), socketSize, timeout);
    isPolling.store(false);
    std::vector<int> toDelete;

    if (rc < 0)
        return {};
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
    auto toReturn = this->removePollables(toDelete);
    this->unlock();
    return toReturn;
}

void PollManager::wakeUp()
{
    if (isPolling.load()) {
        uint64_t value = 1;
        write(this->eventFd, &value, sizeof(value));
    }
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
