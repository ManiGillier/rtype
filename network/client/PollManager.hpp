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
    #include "Client.hpp"
    #include <vector>

class PollManager {
    public:
        virtual ~PollManager() = default;
        void addPollable(std::unique_ptr<IPollable> &pollable);
        void removePollable(int fileDescriptor);
        void removePollables(std::vector<int> fileDescriptors);
        void updateFlags(int fileDescriptor, short newFlags);
        int getConnectionCount() const;
        std::vector<std::unique_ptr<IPollable>> &getClients();
        IPollable *getPollableByFileDescriptor(int fd) const;
        void pollSockets(Server *server);
    private:
        std::vector<struct pollfd> pollFds;
        std::vector<std::unique_ptr<IPollable>> pollables;
    };
#endif /* !POLLMANAGER_HPP_ */