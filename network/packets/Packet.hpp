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
    #include <string>
    #include <cstring>
    #include <queue>
    #include <memory>
    #include <arpa/inet.h>
    #include <vector>
    #include <sstream>
    #include <functional>

    #define SENT_TOO_LARGE_STRING "Sent string was too large"
    #define RECEIVED_TOO_LARGE_STRING "Received too large string"
    #define NOT_ENOUGH_DATA "Did not receive enough data to unserialize"

    #define MAX_STRING_SIZE 256

    #define make_copy(TYPE) std::make_shared<TYPE>(*this)
    #define create_packet(TYPE, ...) std::make_shared<TYPE>(__VA_ARGS__)

template <typename T, std::size_t S>
union ByteWriter {
    T value;
    uint8_t bytes[S];
};

enum PacketId {
    CLIENT_INPUTS,
    NEW_PLAYER,
    NEW_ENEMY,
    PLAYER_HIT,
    GAME_OVER,
    POSITION_UPDATE,
    HITBOX_SIZE_UPDATE,
    LASER_ACTIVE_UPDATE,
    C_AUTHENTICATION_PACKET,
    S_AUTHENTICATION_PACKET,
    AUTHENTIFIED_PACKET,
    GAME_START_REQUEST,
    TEST_PACKET,
    LOGIN_PACKET,
    REGISTER_PACKET,
    LOGIN_RESPONSE_PACKET,
    SPAWN_STRAIGHT_MOVING_ENTITY_PACKET,
    TIME_NOW_PACKET,
    RCON_RESPONSE,
    RCON_REQUEST,
    DESTROY_ENTITY_PACKET,
    JOIN_LOBBY_WITH_CODE_PACKET,
    JOIN_OR_CREATE_PUBLIC_LOBBY_PACKET,
    CREATE_PRIVATE_LOBBY_PACKET,
    JOINED_LOBBY_PACKET,
    LINK_PLAYERS_PACKET,
    SCORE_PACKET,
    TEXT_CHAT_STRING_PACKET,
    SET_ADMIN
};

class PacketDisplay {
public:
    PacketDisplay() = default;

    template<typename... Args>
    PacketDisplay(Args &&...args) {
        addAll(std::forward<Args>(args)...);
    }

    template<typename T>
    void add(const std::string &key, const T &value) {
        fields.emplace_back(key, [value](std::ostream &os) {
            os << value;
        });
    }

    void display() const {
        for (std::size_t i = 0; i < fields.size(); ++i) {
            const auto &[key, printer] = fields[i];
            std::cout << key << "=";
            printer(std::cout);

            if (i < fields.size() - 1) {
                std::cout << ", ";
            }
        }
    }

private:
    template<typename T, typename... Rest>
    void addAll(const std::string &key, const T &value, Rest &&...rest) {
        add(key, value);
        if constexpr (sizeof...(rest) > 0) {
            addAll(std::forward<Rest>(rest)...);
        }
    }
    std::vector<std::pair<std::string, std::function<void(std::ostream&)>>> fields;
};

template<>
inline void PacketDisplay::add<std::vector<std::string>>(const std::string &key, const std::vector<std::string> &value) {
    fields.emplace_back(key, [value](std::ostream &os) {
        os << "[";
        for (std::size_t i = 0; i < value.size(); i++) {
            os << value[i];
            if (i < value.size() - 1)
                os << ", ";
        }
        os << "]";
    });
}

template<>
inline void PacketDisplay::add<std::vector<std::tuple<std::string, int>>>(
    const std::string &key, 
    const std::vector<std::tuple<std::string, int>> &value) {
    fields.emplace_back(key, [value](std::ostream &os) {
        os << "[";
        for (std::size_t i = 0; i < value.size(); i++) {
            const auto &[username, score] = value[i];
            os << "{" << username << ": " << score << "}";
            if (i < value.size() - 1)
                os << ", ";
        }
        os << "]";
    });
}

class Packet {
    public:
        enum PacketMode {TCP, UDP};

        class PacketException : public std::exception {
            public:
                PacketException(const std::string &exception) {
                    this->exception = exception;
                }

                const char *what() const noexcept override {
                    return exception.c_str();
                }

            private:
                std::string exception;
        };

        uint8_t getId() const {
            return (uint8_t) this->packetId;
        }

        Packet(int packetId) {
            this->packetId = packetId;
        }

        std::vector<uint8_t> &getData() {
            return this->data;
        }

        void setData(std::vector<uint8_t> &data) {
            this->data = data;
        }

        std::size_t getReadCursor() const {
            return this->readCursor;
        }

        void clearData() {
            data.clear();
            this->writeCursor = 0;
        }

        template<typename T>
        void write(T value) {
            ByteWriter<T, sizeof(T)> bw;

            bw.value = toNetwork(value);
            for (uint8_t c : bw.bytes) {
                this->data.push_back(c);
                writeCursor++;
            }
        }

        // TODO: Disable send of large strings
        void write(const std::string &value) {
            if (value.size() > MAX_STRING_SIZE)
                throw PacketException(SENT_TOO_LARGE_STRING);
            this->write(static_cast<uint32_t>(value.size()));
            for (const char c : value) {
                this->data.push_back((uint8_t) c);
                writeCursor++;
            }
        }

        template<typename T>
        T read(T &value) {
            ByteWriter<T, (std::size_t) sizeof(T)> bw;
            std::size_t index = 0;

            if (readCursor + sizeof(T) > (std::size_t) this->getData().size())
                throw PacketException(NOT_ENOUGH_DATA);
            for (index = 0; index != sizeof(T); index++)
                bw.bytes[index] = data[readCursor + index];
            readCursor += sizeof(T);
            value = fromNetwork(bw.value);
            return value;
        }

        template<typename T>
        static std::vector<uint8_t> toBinary(T &value) {
            std::vector<uint8_t> binary;
            ByteWriter<T, sizeof(T)> bw;

            bw.value = toNetwork(value);
            for (uint8_t c : bw.bytes)
                binary.push_back(c);
            return binary;
        }

        template<typename T>
        static T fromBinary(std::vector<uint8_t> &data, T &value) {
            if (sizeof(T) > (std::size_t) data.size())
                throw PacketException(NOT_ENOUGH_DATA);
            std::memcpy(&value, data.data(), sizeof(T));
            value = fromNetwork(value);
            data.erase(data.begin(), std::next(data.begin(), static_cast<std::ptrdiff_t>(sizeof(T))));
            return value;
        }

        std::string read(std::string &value) {
            uint32_t stringLength = 0;
            uint8_t stringCharacter;

            this->read(stringLength);
            if (stringLength > MAX_STRING_SIZE)
                throw PacketException(RECEIVED_TOO_LARGE_STRING);
            value.clear();
            for (std::size_t i = 0; i < stringLength; i++) {
                this->read(stringCharacter);
                value.push_back((char) stringCharacter);
            }
            return value;
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

        virtual bool isEqual(const Packet &other) const
        {
            if (this->packetId != other.packetId) {
                return false;
            }
            return this->data == other.data;
        }

        virtual void serialize() = 0;
        virtual void unserialize() = 0;
        virtual const std::string getName() = 0;
        virtual std::shared_ptr<Packet> clone() const = 0;
        virtual enum PacketMode getMode() const = 0;
        virtual PacketDisplay display() const = 0;
        virtual ~Packet() = default;
    private:
        int packetId;
        std::size_t writeCursor = 0;
        std::size_t readCursor = 0;
        std::vector<uint8_t> data;

        template<typename T>
        static inline T toNetwork(T value) {
            if constexpr (sizeof(T) == 1) {
                return value;
            } else if constexpr (sizeof(T) == 2) {
                uint16_t temp;
                std::memcpy(&temp, &value, sizeof(T));
                temp = htons(temp);
                std::memcpy(&value, &temp, sizeof(T));
                return value;
            } else if constexpr (sizeof(T) == 4) {
                uint32_t temp;
                std::memcpy(&temp, &value, sizeof(T));
                temp = htonl(temp);
                std::memcpy(&value, &temp, sizeof(T));
                return value;
            } else if constexpr (sizeof(T) == 8) {
                uint64_t temp;
                std::memcpy(&temp, &value, sizeof(T));
                temp = __builtin_bswap64(temp);
                std::memcpy(&value, &temp, sizeof(T));
                return value;
            }
            return value;
        }

        template<typename T>
        static inline T fromNetwork(T value) {
            return toNetwork(value);
        }
};

#endif /* !PACKET_HPP_ */
