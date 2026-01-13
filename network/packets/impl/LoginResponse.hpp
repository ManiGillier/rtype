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
    LoginResponse(const std::string &reason="", const std::string &token="") : Packet(PacketId::LOGIN_RESPONSE_PACKET) {
        this->reason = reason;
        this->token = token;
    }

    void serialize() {
        this->write(reason);
        if (reason.empty())
            this->write(token);
    }

    void unserialize() {
        this->read(reason);
        if (reason.empty())
            this->read(token);
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
        return reason.empty() ? (PacketDisplay) {"token", this->token} :
            (PacketDisplay) {"reason", this->reason};
    }
private:
    std::string reason;
    std::string token;
};
#endif /* !LOGINRESPONSE_HPP_ */
