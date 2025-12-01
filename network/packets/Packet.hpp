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
    #define PACKET_MAX_SIZE 9

    #define DOUBLE_SIZE sizeof(double)
    #define INT_SIZE sizeof(int)
    #define CHAR_SIZE sizeof(char)
    #define LONG_SIZE sizeof(long)

template <typename T, std::size_t S>
union ByteWriter {
    T value;
    uint8_t bytes[S];
};

enum PacketId {
    UPDATE_POSITION = 1,
    REQUEST_START,
    UPDATE_SCORE,
    START_GAME,
    DEAD_PLAYER,
    BORN_PLAYER,
    MAP_COLUMN,
    PLAYER_WON,
    PLAYER_LOST,
    GHOST_PLAYER_POSITION,
    GHOST_UPDATE_SCORE
};

class Packet {
    public:

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
        }

        template<typename T>
        void write(T value) {
            ByteWriter<T, (std::size_t) sizeof(T)> bw;

            bw.value = value;
            if (writeCursor + sizeof(T) > (std::size_t) this->getSize())
                return;
            for (char c : bw.bytes) {
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
        virtual void display() = 0;
        virtual ~Packet() = default;
    private:
        int packetId;
        std::size_t writeCursor = 0;
        std::size_t readCursor = 0;
        std::queue<uint8_t> data;
};

#endif /* !PACKET_HPP_ */
