/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** NetworkTester
*/

#include <network/server/Server.hpp>
#include <iostream>
#include <cstring>

static int client(int port)
{
    (void) port;
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

    if ((argc != 3 && argc != 4) || !(!strcmp(argv[1], "client") || !strcmp(argv[1], "server")))
        return 1;
    port = atoi(argv[2]);
    for (; *argv; argv++) {
        if (!strcmp(*argv, "-d"))
            Logger::shouldLog = true;
    }
    return !strcmp(argv[1], "client") ? client(port) : server(port);
}
