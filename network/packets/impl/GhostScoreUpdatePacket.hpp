/*
** EPITECH PROJECT, 2025
** jetpack [WSL: Ubuntu-24.04]
** File description:
** GhostScoreUpdatePacket
*/

    #ifndef GHOSTSCOREUPDATEPACKET_HPP_
    #define GHOSTSCOREUPDATEPACKET_HPP_

    #include "network/packets/Packet.hpp"

class GhostScoreUpdatePacket : public Packet {
public:
    GhostScoreUpdatePacket(uint32_t score=0, int whichGhost=0) :
        Packet(PacketId::GHOST_UPDATE_SCORE)
        {
            this->score = score;
            this->whichGhost = whichGhost;
        }

    void serialize() {
        this->write(score);
        this->write(whichGhost);
    }

    void unserialize() {
        this->score = this->read(this->score);
        this->whichGhost = this->read(this->whichGhost);
    }

    uint32_t getScore() const {
        return this->score;
    }

    int getWhichGhost() const {
        return this->whichGhost;
    }

    void setGhost(int whichGhost) {
        this->whichGhost = whichGhost;
    }

    void setScore(uint32_t score) {
        this->score = score;
    }

    int getSize() const {
        return (int) sizeof(uint32_t) + (int) sizeof(int);
    }

    const std::string getName() {
        return "GhostScoreUpdatePacket";
    }

    void display() {
        std::cout << "Score=" << this->score << ", Player=" << this->whichGhost;
    }

private:
    uint32_t score;
    int whichGhost;
};

#endif /* !GHOSTSCOREUPDATEPACKET_HPP_ */
