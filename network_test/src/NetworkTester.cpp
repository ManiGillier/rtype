/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** NetworkTester
*/

#include <network/server/Server.hpp>
#include <network/client/Client.hpp>
#include <iostream>
#include <cstring>

static int client(const std::string &ip, int port)
{
    Client cl(ip, port);

    cl.connect();

    while (true)
        cl.loop();
    return 0;
}

static int server(int port)
{
    CustomServer serv(port);

    serv.up();

    while (true)
        serv.loop();
    return 0;
}

// ./reseauType {client | server} {port}

int main(int argc, char **argv)
{
    int port = 0;
    std::string ip;

    if (!strcmp(argv[1], "client")) {
        if ((argc != 5 && argc != 4) || (argc == 5 && strcmp(argv[4], "-d")))
            return 1;
        Logger::shouldLog = !strcmp(argv[4], "-d");
        port = atoi(argv[3]);
        ip = argv[2];
        return client(ip, port);
    }
    if (!strcmp(argv[1], "server")) {
        if ((argc != 3 && argc != 4) || (argc == 4 && strcmp(argv[3], "-d")))
            return 1;
        Logger::shouldLog = !strcmp(argv[3], "-d");
        port = atoi(argv[2]);
        return server(port);
    }
    return 1;
}
