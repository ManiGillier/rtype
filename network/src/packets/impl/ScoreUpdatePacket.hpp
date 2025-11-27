/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** UpdateScorePacket
*/

#ifndef UPDATESCOREPACKET_HPP_
    #define UPDATESCOREPACKET_HPP_

    #include "Packet.hpp"

class ScoreUpdatePacket : public Packet {
public:
    ScoreUpdatePacket(uint32_t score=0, int xPosition = 0, int yPosition = 0) :
        Packet(PacketId::UPDATE_SCORE)
        {
            this->score = score;
            this->xPosition = xPosition;
            this->yPosition = yPosition;
        }

    void serialize() {
        this->write(score);
        this->write(xPosition);
        this->write(yPosition);
    }

    void unserialize() {
        this->score = this->read(this->score);
        this->xPosition = this->read(this->xPosition);
        this->yPosition = this->read(this->yPosition);
    }

    uint32_t getScore() const {
        return this->score;
    }

    int getX() const {
        return this->xPosition;
    }

    int getY() const {
        return this->yPosition;
    }

    void setScore(uint32_t score) {
        this->score = score;
    }

    int getSize() const {
        return (int) sizeof(uint32_t) + 2 * (int) sizeof(int);
    }

    const std::string getName() {
        return "ScoreUpdatePacket";
    }

    void display() {
        std::cout << "Score=" << this->score << ", X=" << this->xPosition <<
            ", Y=" << this->yPosition;
    }

private:
    uint32_t score;
    int xPosition;
    int yPosition;
};

#endif /* !UPDATESCOREPACKET_HPP_ */
