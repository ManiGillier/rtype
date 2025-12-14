/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** NetworkTester
*/

#include <network/server/Server.hpp>
#include <network/client/Client.hpp>
#include <network/packets/listener/PacketExecutor.hpp>
#include <network/packets/impl/NewPlayerPacket.hpp>
#include <iostream>
#include <cstring>

class ScoreUpdateExecutor : public PacketExecutorImpl<NewPlayerPacket, ClientPollable, Client> {

    bool execute(Client &cl, std::shared_ptr<ClientPollable> &con, std::shared_ptr<NewPlayerPacket> packet) {
        (void) con;
        (void) packet;
        LOG("YAYYYYYY !!!!! port=" << cl.getPort());
        cl.sendPacket(create_packet(NewPlayerPacket, 67));
        return true;
    }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }

};

class ScoreUpdateExecutorServ : public PacketExecutorImpl<NewPlayerPacket, ServerClient, Server> {

    bool execute(Server &s, std::shared_ptr<ServerClient> &con, std::shared_ptr<NewPlayerPacket> packet) {
        (void) con;
        (void) packet;
        (void) s;
        LOG("WOOOHOOOO !!!!");
        packet->display();
        return false;
    }

    int getPacketId() const {
        return PacketId::NEW_PLAYER;
    }

};

static int client(const std::string &ip, int port)
{
    Client cl(ip, port);

    cl.getPacketListener().addExecutor(std::make_unique<ScoreUpdateExecutor>());
    cl.connect();
    if (!cl.isConnected()) {
        LOG_ERR("Could not connect to " << ip << ":" << port << ", aborting..");
        return 1;
    }
    while (cl.isConnected()) {
        cl.loop();
        cl.executePackets();
    }
    return 0;
}

static int server(int port)
{
    CustomServer serv(port);

    serv.getPacketListener().addExecutor(std::make_unique<ScoreUpdateExecutorServ>());
    serv.up();
    if (!serv.isUp()) {
        LOG_ERR("Could not start server at port " << port << ", aborting..");
        return 1;
    }
    while (serv.isUp())
        serv.loop();
    return 0;
}

// ./reseauType {client | server} {port}

int main(int argc, char **argv)
{
    int port = 0;
    std::string ip;

    if (argc == 1)
        return 1;
    if (!strcmp(argv[1], "client")) {
        if ((argc != 5 && argc != 4) || (argc == 5 && strcmp(argv[4], "-d")))
            return 1;
        Logger::shouldLog = argc == 5;
        port = atoi(argv[3]);
        ip = argv[2];
        return client(ip, port);
    }
    if (!strcmp(argv[1], "server")) {
        if ((argc != 3 && argc != 4) || (argc == 4 && strcmp(argv[3], "-d")))
            return 1;
        Logger::shouldLog = argc == 4;
        port = atoi(argv[2]);
        return server(port);
    }
    return 1;
}
