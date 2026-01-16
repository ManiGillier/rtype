/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RCONResponse
*/

#ifndef RCONRESPONSE_HPP_
    #define RCONRESPONSE_HPP_

    #include <network/packets/Packet.hpp>
    #define RCON_DEFAULT_RESPONSE "The specified password is incorrect"

class RCONResponse : public Packet {
    public:
        RCONResponse(std::string response=RCON_DEFAULT_RESPONSE) :
            Packet(PacketId::RCON_RESPONSE) {
                this->responses.push_back(response);
            }

        enum PacketMode getMode() const {
            return PacketMode::TCP;
        }

        void serialize() {
            this->write((uint16_t) this->responses.size());
            for (const std::string &response : this->responses)
                this->write(response);
        }

        void unserialize() {
            uint16_t size;

            this->read(size);
            this->responses.clear();
            for (uint16_t i = 0; i < size; i++) {
                std::string response;
                this->read(response);
                this->responses.push_back(response);
            }
        }

        const std::string getName() {
            return "RCONResponsePacket";
        }

        PacketDisplay display() const {
            return {"response", this->responses};
        }

        std::shared_ptr<Packet> clone() const {
            return make_copy(RCONResponse);
        }

        const std::vector<std::string> &getResponses() const {
            return this->responses;
        }

        void addResponse(const std::string &response) {
            this->responses.push_back(response);
        }

        void clearResponses() {
            this->responses.clear();
        }
     
    private:
        std::vector<std::string> responses;
};

#endif /* !RCONRESPONSE_HPP_ */
