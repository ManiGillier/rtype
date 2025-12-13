/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** PacketListener
*/

#ifndef PACKETLISTENER_HPP_
    #define PACKETLISTENER_HPP_

    #include "PacketExecutor.hpp"
    #include <network/poll/IPollable.hpp>
    #include <vector>

template<typename Entity>
class PacketListener {
    public:
        virtual ~PacketListener() = default;

        bool addExecutor(std::unique_ptr<PacketExecutor<Entity>> executor) {
            this->executors.push_back(std::move(executor));
            return true;
        }

        bool removeExecutor(std::unique_ptr<PacketExecutor<Entity>> &executor) {
            for (auto it = this->executors.begin(); it != this->executors.end(); it++) {
                if (*it == executor) {
                    this->executors.erase(it);
                    return true;
                }
            }
            return false;
        }

        bool removeExecutor(int packetId) {
            for (auto it = this->executors.begin(); it != this->executors.end(); it++) {
                if ((*it)->getPacketId() == packetId) {
                    this->executors.erase(it);
                    return true;
                }
            }
            return false;
        }

        bool executePacket(Entity &e, std::shared_ptr<IPollable> &con,
            std::shared_ptr<Packet> p) const {
            bool status = true;

            for (const std::unique_ptr<PacketExecutor<Entity>> &packetExecutor : this->executors) {
                if (packetExecutor->getPacketId() == p->getId())
                    status &= packetExecutor->executePacket(e, con, p);
            }
            return status;
        }

        bool clearExecutors() {
            this->executors.clear();
            return true;
        }

        const std::vector<std::unique_ptr<PacketExecutor<Entity>>> &getExecutors() const {
            return this->executors;
        }

    private:
        std::vector<std::unique_ptr<PacketExecutor<Entity>>> executors;
};

#endif /* !PACKETLISTENER_HPP_ */
