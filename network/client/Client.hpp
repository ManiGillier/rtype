/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include <network/packets/PacketReader.hpp>
    #include <network/packets/PacketSender.hpp>
    #include <network/packets/listener/PacketListener.hpp>
    #include <network/poll/PollManager.hpp>
    #include <network/poll/Pollable.hpp>
    #include <string>

    #include <network/packets/impl/SAuthentificationPacket.hpp>
    #include <network/packets/impl/AuthentifiedPacket.hpp>

    #define MAX_RETRIES 10

class ClientPollable;

class Client {
    public:
        Client(const std::string &ip, int port);
        bool connect();
        bool disconnect();
        bool isConnected() const;
        bool sendPacket(std::shared_ptr<Packet> p);
        void loop();
        const std::string &getIp() const;
        int getPort() const;
        PollManager &getPollManager();
        PacketListener<Client> &getPacketListener();
        void setUUID(uint32_t uuid);
        void setAuthentified(bool auth);
        bool isAuthentified() const;
        uint32_t getUUID()  const;
    private:
        void sendUDPPackets();
        void executePackets();
        std::string ip;
        int port;
        int udpSocket;
        int fd = -1;
        PollManager pm;
        PacketListener<Client> pl;
        sockaddr_in udpServerAddress;
        bool connected = false;
        bool authentified = false;
        int retries = 0;
        uint32_t uuid = 0;
};

class ClientPollable : public Pollable {
    public:
        ClientPollable(Client &cl, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);
    private:
        bool shouldWrite() const;
        [[maybe_unused]] Client &cl;
};

class ClientPollableUDP : public Pollable {
    public:
        ClientPollableUDP(Client &cl, int fd, sockaddr_in address);
        short getFlags() const;
        bool receiveEvent(short revent);

        /* TODO: Change this system for part 2 */

        static std::vector<std::tuple<sockaddr_in, std::shared_ptr<Packet>>> &getUDPReceivedPackets()
        {
            static std::vector<std::tuple<sockaddr_in, std::shared_ptr<Packet>>> packets;
            return packets;
        }

        static void addReceivedPacket(sockaddr_in address, std::shared_ptr<Packet> p) {
            getUDPReceivedPackets().push_back(std::make_tuple(address, p));
        }

        static std::vector<std::shared_ptr<Packet>> &getUDPPacketsToSend()
        {
            static std::vector<std::shared_ptr<Packet>> packets;
            return packets;
        }

        static void addUDPPacketToSend( std::shared_ptr<Packet> p) {
            getUDPPacketsToSend().push_back(p);
        }

    private:
        sockaddr_in address;
        [[maybe_unused]] Client &cl;
};

class ClientAuthExecutor :
    public PacketExecutorImpl<SAuthentificationPacket, ClientPollable,
        Client> {
public:
    bool execute(Client &cl, std::shared_ptr<ClientPollable> con, std::shared_ptr<SAuthentificationPacket> packet) {
        (void) con;
        if (!cl.isAuthentified())
            cl.setUUID(packet->getUUID());
        return true;
    }

    int getPacketId() const {
        return PacketId::S_AUTHENTICATION_PACKET;
    }
};

class ClientSetAuthExecutor :
    public PacketExecutorImpl<AuthentifiedPacket, ClientPollable,
        Client> {
public:
    bool execute(Client &cl, std::shared_ptr<ClientPollable> con, std::shared_ptr<AuthentifiedPacket> packet) {
        (void) con;
        (void) packet;
        cl.setAuthentified(true);
        return true;
    }

    int getPacketId() const {
        return PacketId::AUTHENTIFIED_PACKET;
    }
};

#endif /* !CLIENT_HPP_ */
