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
            Packet(PacketId::RCON_RESPONSE), response(response) {}

        enum PacketMode getMode() const {
            return PacketMode::TCP;
        }

        void serialize() {
            this->write(response);
        }
        void unserialize() {
            this->read(response);
        }

        const std::string getName() {
            return "RCONResponsePacket";
        }

        PacketDisplay display() const {
            return {"response", this->response};
        }

        std::shared_ptr<Packet> clone() const {
            return make_copy(RCONResponse);
        }

        const std::string &getResponse() const {
            return this->response;
        }
    private:
        std::string response;
};

#endif /* !RCONRESPONSE_HPP_ */
