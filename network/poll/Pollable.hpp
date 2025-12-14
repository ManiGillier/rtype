/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Pollable
*/

#ifndef POLLABLE_HPP_
    #define POLLABLE_HPP_

    #include <network/poll/IPollable.hpp>
    #include <network/packets/PacketReader.hpp>
    #include <network/packets/PacketSender.hpp>
    #include <network/poll/PollManager.hpp>

    #include <atomic>
    #include <optional>

class Pollable : public IPollable {
    public:

        /* TODO : Make IDs more random lol */
        Pollable(int fd, PollManager &pm,
            Packet::PacketMode mode=Packet::PacketMode::TCP) :
            _fd(fd), sender(fd), pm(pm), reader(fd, mode) {
            static std::atomic<uint32_t> counter{1};
            this->uuid = counter.fetch_add(1, std::memory_order_relaxed);
        }

        int getFileDescriptor() {
            return this->_fd;
        }

        PacketSender &getPacketSender() {
            return this->sender;
        }

        const PacketSender &getPacketSender() const {
            return this->sender;
        }

        PacketReader &getPacketReader() {
            return this->reader;
        }

        const PacketReader &getPacketReader() const {
            return this->reader;
        }

        uint32_t getUUID() const {
            return this->uuid;
        }

        std::optional<sockaddr_in> getClientAddress() const {
            return this->address;
        }

        void setClientAddress(std::optional<sockaddr_in> address) {
            this->address = address;
        }

        void sendPacket(std::shared_ptr<Packet> p) {
            this->getPacketSender().sendPacket(p);
            this->pm.updateFlags(this->getFileDescriptor(), this->getFlags());
        }

        std::queue<std::shared_ptr<Packet>> &getReceivedPackets() {
            return this->toProcess;
        }
    protected:
        std::queue<std::shared_ptr<Packet>> toProcess;
    private:
        std::optional<sockaddr_in> address = std::nullopt;
        uint32_t uuid;
        int _fd;
        PacketSender sender;
        PollManager &pm;
        PacketReader reader;
};

#endif /* !POLLABLE_HPP_ */
