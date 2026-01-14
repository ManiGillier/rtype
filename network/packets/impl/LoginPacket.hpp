/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** LoginPacket
*/

#ifndef LOGINPACKET_HPP_
    #define LOGINPACKET_HPP_

    #include <network/packets/Packet.hpp>

class LoginPacket : public Packet {
public:
    LoginPacket(const std::string &username="", const std::string &password="") : Packet(PacketId::LOGIN_PACKET) {
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
        return make_copy(LoginPacket);
    }

    const std::string getName() {
        return "LoginPacket";
    }

    PacketDisplay display() const {
        return {"username", this->username,
                "EH MEC LE PASSWORD VITE REGARDE C CE TRUC -------> /!\\", this->password};
    }
private:
    std::string username;
    std::string password;
};

#endif /* !LOGINPACKET_HPP_ */
