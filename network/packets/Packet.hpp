/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** Packet
*/

#ifndef PACKET_HPP_
    #define PACKET_HPP_

    #include <iostream>
    #include <cstdint>
    #include <queue>
    #include <memory>

    #define DOUBLE_SIZE sizeof(double)
    #define INT_SIZE sizeof(int)
    #define CHAR_SIZE sizeof(char)
    #define LONG_SIZE sizeof(long)

    #define make_copy(TYPE) std::make_shared<TYPE>(*this)
    #define create_packet(TYPE, ...) std::make_shared<TYPE>(__VA_ARGS__)

template <typename T, std::size_t S>
union ByteWriter {
    T value;
    uint8_t bytes[S];
};

enum PacketId {
    PLAYER_ID = 1,
    CLIENT_INPUTS,
    NEW_PLAYER,
    NEW_BULLET,
    NEW_ENEMY,
    PLAYER_HIT,
    PLAYER_DIED,
    DESPAWN_PLAYER,
    DESPAWN_BULLET,
    ENEMY_DIED,
    GAME_OVER,
    POSITION_UPDATE,
    HEALTH_UPDATE,
    HITBOX_SIZE_UPDATE,
    LASER_ACTIVE_UPDATE,
    C_AUTHENTICATION_PACKET,
    S_AUTHENTICATION_PACKET,
    AUTHENTIFIED_PACKET,
    GAME_START_REQUEST
};

class Packet {
    public:
        enum PacketMode {TCP, UDP};

        uint8_t getId() const {
            return (uint8_t) this->packetId;
        }

        Packet(int packetId) {
            this->packetId = packetId;
        }

        std::queue<uint8_t> &getData() {
            return this->data;
        }

        void setData(std::queue<uint8_t> &data) {
            this->data = data;
        }

        void clearData() {
            while (!this->data.empty())
                data.pop();
            this->writeCursor = 0;
        }

        template<typename T>
        void write(T value) {
            ByteWriter<T, (std::size_t) sizeof(T)> bw;

            bw.value = value;
            if (writeCursor + sizeof(T) > (std::size_t) this->getSize())
                return;
            for (uint8_t c : bw.bytes) {
                this->data.push(c);
                writeCursor++;
            }
        }

        // TODO : Verify
        template<typename T>
        T read(T &value) {
            ByteWriter<T, (std::size_t) sizeof(T)> bw;
            std::queue<uint8_t> data = this->getData();
            std::size_t index = 0;

            if (readCursor + sizeof(T) > (std::size_t) this->getSize())
                throw std::exception();
            while (index != readCursor) {
                data.pop();
                index++;
            }
            for (index = 0; index != sizeof(T); index++) {
                bw.bytes[index] = data.front();
                data.pop();
            }
            readCursor += sizeof(T);
            value = bw.value;
            return bw.value;
        }

        int readInt(int i) {
            return this->read(i);
        }

        long readLong(long l) {
            return this->read(l);
        }

        char readChar(char c) {
            return this->read(c);
        }

        double readDouble(double d) {
            return this->read(d);
        }

        void writeInt(int i) {
            write(i);
        }

        void writeLong(long l) {
            write(l);
        }

        void writeChar(char c) {
            write(c);
        }

        void writeDouble(double d) {
            write(d);
        }

        virtual int getSize() const = 0;
        virtual void serialize() = 0;
        virtual void unserialize() = 0;
        virtual const std::string getName() = 0;
        virtual std::shared_ptr<Packet> clone() const = 0;
        virtual enum PacketMode getMode() const = 0;
        virtual void display() = 0;
        virtual ~Packet() = default;
    private:
        int packetId;
        std::size_t writeCursor = 0;
        std::size_t readCursor = 0;
        std::queue<uint8_t> data;
};

#endif /* !PACKET_HPP_ */
