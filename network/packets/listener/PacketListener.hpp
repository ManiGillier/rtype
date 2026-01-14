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
    #include <network/logger/Logger.hpp>
    #include <vector>

template<typename Entity>
class PacketListener {
    public:
        virtual ~PacketListener() = default;

        bool addExecutor(std::unique_ptr<PacketExecutor<Entity>> executor) {
            this->executors.push_back(std::move(executor));
            return true;
        }

        bool addPersistentExecutor(std::unique_ptr<PacketExecutor<Entity>> executor) {
            this->persistentExecutors.push_back(std::move(executor));
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

        void disableAllExecutors(std::shared_ptr<IPollable> p) {
            p->setDisabled(true);
        }

        void enableAllExecutors(std::shared_ptr<IPollable> p) {
            p->setDisabled(false);
        }

        void addToWhitelist(uint8_t p) {
            this->whitelist.push_back(p);
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

        bool isWhitelisted(uint8_t id) const {
            for (uint8_t i : this->whitelist) {
                if (i == id)
                    return true;
            }
            return false;
        }

        bool executePacket(Entity &e, std::shared_ptr<IPollable> con,
            std::shared_ptr<Packet> p) const {
            bool status = true;
            bool disabled = con->isDisabled();

            for (const std::unique_ptr<PacketExecutor<Entity>> &packetExecutor : this->executors) {
                if (packetExecutor->getPacketId() == p->getId() && (!disabled || isWhitelisted((uint8_t) packetExecutor->getPacketId()))) {
                    status &= packetExecutor->executePacket(e, con, p);
                }
            }
            for (const std::unique_ptr<PacketExecutor<Entity>> &packetExecutor : this->persistentExecutors) {
                if (packetExecutor->getPacketId() == p->getId()) {
                    status &= packetExecutor->executePacket(e, con, p);
                }
            }
            return status;
        }

        bool executePacket(Entity &e, sockaddr_in sock,
            std::shared_ptr<Packet> p) const {
            bool status = true;

            for (const std::unique_ptr<PacketExecutor<Entity>> &packetExecutor : this->executors) {
                if (packetExecutor->getPacketId() == p->getId())
                    status &= packetExecutor->executePacketUnlogged(e, sock, p);
            }
            for (const std::unique_ptr<PacketExecutor<Entity>> &packetExecutor : this->persistentExecutors) {
                if (packetExecutor->getPacketId() == p->getId()) {
                    status &= packetExecutor->executePacketUnlogged(e, sock, p);
                }
            }
            return status;
        }

        bool clearExecutors() {
            this->executors.clear();
            return true;
        }

        const std::vector<std::unique_ptr<PacketExecutor<Entity>>> getExecutors() const {
            return this->executors;
        }

        const std::vector<std::unique_ptr<PacketExecutor<Entity>>> getPersistentExecutors() const {
            return this->persistentExecutors;
        }

    private:
        std::vector<uint8_t> whitelist;
        std::vector<std::unique_ptr<PacketExecutor<Entity>>> executors;
        std::vector<std::unique_ptr<PacketExecutor<Entity>>> persistentExecutors;
};

#endif /* !PACKETLISTENER_HPP_ */
