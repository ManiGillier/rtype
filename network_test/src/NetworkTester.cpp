/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** NetworkTester
*/

#include <iostream>
#include <cstring>

static int client(int port)
{
    return 0;
}

static int server(int port)
{
    

    return 0;
}

// ./reseauType {client | server} {port}

int main(int argc, char **argv)
{
    if (argc != 3 || !(!strcmp(argv[1], "client") || !strcmp(argv[1], "server")))
        return 1;
    return !strcmp(argv[1], "client") ? client(atoi(argv[2])) : server(atoi(argv[2]));
}
