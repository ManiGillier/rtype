/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RegisterPacket
*/

#ifndef REGISTERPACKET_HPP_
#define REGISTERPACKET_HPP_

    #include <network/packets/Packet.hpp>
    #define PASSWORD_IS_ALREADY_OWNED_BY(USERNAME) "Sorry, this password is already owned by " USERNAME

class RegisterPacket : public Packet {
public:
    RegisterPacket(const std::string &username="", const std::string &password="") : Packet(PacketId::REGISTER_PACKET) {
        this->username = username;
        this->password = password;
    }

    void serialize() {
        this->write(username);
        this->write(password);
    }

    void unserialize() {
        this->read(username);
        this->read(password);
    }

    enum PacketMode getMode() const {
        return PacketMode::TCP;
    }

    std::shared_ptr<Packet> clone() const {
        return make_copy(RegisterPacket);
    }

    const std::string getName() {
        return "RegisterResponse";
    }

    PacketDisplay display() const {
        return {"username", username,
            "password -----> (very important, must note):", password};
    }
private:
    std::string username;
    std::string password;
};
#endif /* !REGISTERPACKET_HPP_ */
