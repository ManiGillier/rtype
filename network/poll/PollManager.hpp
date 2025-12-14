/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** PollManager
*/

#ifndef POLLMANAGER_HPP_
    #define POLLMANAGER_HPP_

class Server;

    #include "IPollable.hpp"
    #include <memory>
    #include <vector>

    #include <poll.h>
    #include <unistd.h>

class PollManager {
    public:
        virtual ~PollManager() = default;
        void addPollable(std::shared_ptr<IPollable> pollable);
        void removePollable(int fileDescriptor);
        void removePollables(std::vector<int> fileDescriptors);
        void updateFlags(int fileDescriptor, short newFlags);
        std::size_t getConnectionCount() const;
        std::vector<std::shared_ptr<IPollable>> &getPool();
        void pollSockets();
        void clear();
    private:
        std::vector<struct pollfd> pollFds;
        std::vector<std::shared_ptr<IPollable>> pollables;
    };
#endif /* !POLLMANAGER_HPP_ */
