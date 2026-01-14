/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** LoginResponse
*/

#ifndef LOGINRESPONSE_HPP_
    #define LOGINRESPONSE_HPP_

    #include <network/packets/Packet.hpp>
    #define PASSWORD_IS_ALREADY_OWNED_BY(USERNAME) "Sorry, this password is already owned by " USERNAME

class LoginResponse : public Packet {
public:
    LoginResponse(uint8_t succesful=0, const std::string &reason="") : Packet(PacketId::LOGIN_RESPONSE_PACKET) {
        this->succesful = succesful;
        this->reason = reason;
    }

    void serialize() {
        this->write(succesful);
        if (!succesful)
            this->write(reason);
    }

    void unserialize() {
        this->read(succesful);
        if (!succesful)
            this->read(reason);
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(LoginResponse);
    }

    const std::string getName() {
        return "LoginResponse";
    }

    PacketDisplay display() const {
        if (reason.empty())
            return {"succesful", (int) this->succesful};
        return {"succesful", (int) this->succesful, "reason", this->reason};
    }
private:
    std::string reason;
    uint8_t succesful;
};
#endif /* !LOGINRESPONSE_HPP_ */
