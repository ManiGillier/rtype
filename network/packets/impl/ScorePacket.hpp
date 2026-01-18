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
            std::vector<std::tuple<std::string, int>> scores={}) :
            Packet(PacketId::SCORE_PACKET), request(request),
            scores(scores) {};

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    void serialize() {
        this->write((uint8_t) request);
        if (request == LIST) {
            this->write((uint16_t) scores.size());
            for (std::size_t i = 0; i < scores.size(); i++) {
                auto [username, score] = scores[i];
                this->write(username);
                this->write(score);
            }
        }
    }

    void unserialize() {
        uint8_t requestType;
        uint16_t size;

        this->read(requestType);
        this->request = static_cast<ScorePacketType>(requestType);
        if (this->request == LIST) {
            this->read(size);
            for ([[maybe_unused]] uint16_t i = 0; i < size; i++) {
                std::string username;
                int score;

                this->read(username);
                this->read(score);
                this->scores.emplace_back(username, score);
            }
        }
    }

    void addScore(const std::string &username, int score) {
        if (this->scores.size() >= 10)
            return;
        this->scores.emplace_back(username, score);
    }

    const std::string getName() {
        return "ScorePacket";
    }

    PacketDisplay display() const {
        if (this->request == REQUEST)
            return {"Request", "REQUEST"};
        return {"Request", "LIST", "Scoreboard", this->scores};
    }

    enum ScorePacketType getRequest() {
        return this->request;
    }

    const std::vector<std::tuple<std::string, int>> &getScores() const {
        return this->scores;
    }

    std::vector<std::string> getUsernames() const {
        std::vector<std::string> toReturn;

        for (auto [username, score] : scores)
            toReturn.push_back(username);
        return toReturn;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(ScorePacket);
    }

    private:
        enum ScorePacketType request;
        std::vector<std::tuple<std::string, int>> scores;
};

#endif /* !SCOREPACKET_HPP_ */
