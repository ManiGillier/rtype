/*
** EPITECH PROJECT, 2025
** jetpack [WSL: Ubuntu-24.04]
** File description:
** MapColumnPacket
*/

#ifndef MAPCOLUMNPACKET_HPP_
    #define MAPCOLUMNPACKET_HPP_

    #include <array>
    #include "Object.hpp"
    #include "Packet.hpp"

    #define COLUMN_HEIGHT 5

class MapColumnPacket : public Packet {
public:
    MapColumnPacket() : Packet(PacketId::MAP_COLUMN) {
        return;
    }

    MapColumnPacket(uint8_t objects[COLUMN_HEIGHT])
        : Packet(PacketId::MAP_COLUMN) {
        for (int i = 0; i < COLUMN_HEIGHT; i++)
            this->_obj[i] = objects[i];
    }

    MapColumnPacket(std::vector<uint8_t> objects)
        : Packet(PacketId::MAP_COLUMN) {
        for (int i = 0; i < COLUMN_HEIGHT; i++)
            this->_obj[i] = objects[i];
    }

    void serialize() {
        for (int i = 0; i < COLUMN_HEIGHT; i++)
            this->writeChar(_obj[i]);
    }

    void unserialize() {
        for (int i = 0; i < COLUMN_HEIGHT; i++)
            _obj[i] = this->readChar(_obj[i]);
    }

    int getSize() const {
        return sizeof(char) * 5;
    }

    std::array<uint8_t, 5> getColumn() {
        return this->_obj;
    }

    const std::string getName() {
        return "MapColumnPacket";
    }

    void display() {
        std::string objects = "";

        for (int i = 0; i < COLUMN_HEIGHT; i++) {
            if (i != 0)
                objects += " ";
            if (_obj[i] == (uint8_t) Object::COIN)
                objects += "Coin";
            if (_obj[i] == (uint8_t) Object::EMPTY)  
                objects += "Empty";
            if (_obj[i] == (uint8_t) Object::ZAP)
                objects += "Zap";
            if (_obj[i] == (uint8_t) Object::FINISH)
                objects += "Finish";
            if (i + 1 != COLUMN_HEIGHT)
                objects += ",";
        }
        std::cout << "Objects = [" << objects << "]";
    }

private:
    std::array<uint8_t, 5> _obj;
};

#endif /* !MAPCOLUMNPACKET_HPP_ */
