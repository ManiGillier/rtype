/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RCONRequest
*/

#ifndef RCONREQUEST_HPP_
    #define RCONREQUEST_HPP_

    #include <network/packets/Packet.hpp>

class RCONRequest : public Packet {
    public:
        enum RequestType {LIST, KICK, BAN};
        RCONRequest(RequestType requestType=LIST, const std::string &rconKey="",
            const std::string &target="") :
            Packet(PacketId::RCON_REQUEST), requestType(requestType),
            rconKey(rconKey), target(target) {}

        enum PacketMode getMode() const {
            return PacketMode::TCP;
        }

        void serialize() {
            this->write(rconKey);
            this->write((uint8_t) requestType);
            if (requestType == KICK || requestType == BAN)
                this->write(target);
        }

        void unserialize() {
            uint8_t requestType;

            this->read(rconKey);
            this->read(requestType);
            this->requestType = static_cast<RequestType>(requestType);
            if (requestType == KICK || requestType == BAN)
                this->read(target);
        }

        const std::string getName() {
            return "RCONRequest";
        }

        PacketDisplay display() const {
            return {"requestType", getRequestTypeAsString(requestType)};
        }

        std::shared_ptr<Packet> clone() const {
            return make_copy(RCONRequest);
        }

        RequestType getRequestType() const {
            return this->requestType;
        }
    private:
        std::string getRequestTypeAsString(RequestType requestType) const {
            switch (requestType) {
                case LIST:
                    return "LIST";
                case KICK:
                    return "KICK";
                case BAN:
                    return "BAN";
            }
            return "Unknown";
        }
        RequestType requestType;
        std::string rconKey;
        std::string target;
};

#endif /* !RCONREQUEST_HPP_ */
