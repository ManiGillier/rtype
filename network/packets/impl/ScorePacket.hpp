/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** ScorePacket
*/

#ifndef SCOREPACKET_HPP_
    #define SCOREPACKET_HPP_

    #include <string>
    #include "network/packets/Packet.hpp"

class ScorePacket : public Packet {
    public:
        enum ScorePacketType {REQUEST, LIST};
        ScorePacket(enum ScorePacketType request=LIST,
            std::vector<std::string> usernames={}) : Packet(PacketId::SCORE_PACKET),
            request(request), usernames(usernames) {};

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write((uint8_t) request);
        if (request == LIST) {
            this->write((uint8_t) usernames.size());
            for (std::size_t i = 0; i < usernames.size(); i++)
                this->write(usernames[i]);
        }
    }

    void unserialize() {
        uint8_t requestType;
        uint8_t size;

        this->read(requestType);
        this->request = static_cast<ScorePacketType>(requestType);
        if (this->request == LIST) {
            this->read(size);
            for ([[maybe_unused]] uint8_t i = 0; i < size; i++) {
                std::string username;

                this->read(username);
                this->usernames.push_back(username);
            }
        }
    }

    void addUsername(const std::string &username) {
        if (username.size() >= 10)
            return;
        this->usernames.push_back(username);
    }

    const std::string getName() {
        return "ScorePacket";
    }

    PacketDisplay display() const {
        if (this->request == REQUEST)
            return {"Request", "REQUEST"};
        return {"Request", "LIST", "Scoreboard", this->usernames};
    }

    enum ScorePacketType getRequest() {
        return this->request;
    }

    const std::vector<std::string> &getUsernames() const {
        return this->usernames;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(ScorePacket);
    }

    private:
        enum ScorePacketType request;
        std::vector<std::string> usernames;
};

#endif /* !SCOREPACKET_HPP_ */
