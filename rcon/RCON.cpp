/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** main
*/

#include <iostream>
#include <chrono>
#include <iostream>
#include <ostream>
#include <fstream>
#include <format>
#include <thread>

#include <network/client/Client.hpp>
#include <network/packets/impl/RCONResponse.hpp>
#include <rcon/Logger.hpp>

#include <rcon/commands/CommandManager.hpp>

#define CONFIG_FILE "rtype.cfg"

static bool readConfig(std::string &rconKey)
{
    std::ifstream config(CONFIG_FILE);
    std::string key;
    std::string value;

    if (!config.is_open())
        return false;
    std::string line;
    while (std::getline(config, line)) {
        std::size_t pos = line.find('=');
        if (pos != std::string::npos) {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            if (key == "RCON_KEY")
                rconKey = value;
        }
    }
    if (!config.eof() && config.fail())
        return false;
    config.close();
    return true;
}

class RCONExecutor : public PacketExecutorImplClient<RCONResponse, ClientPollable> {
    bool execute(Client &cl, std::shared_ptr<ClientPollable> con, std::shared_ptr<RCONResponse> packet) {
        const std::vector<std::string> &responses = packet->getResponses();
        for (std::size_t i = 0; i < responses.size(); i++) {
            if (i == 0)
                RCON_LOG(responses[i]);
            else
                std::cout << responses[i] << std::endl;
        }
        (void) cl;
        (void) con;
        return true;
    }

    int getPacketId() const {
        return PacketId::RCON_RESPONSE;
    }

};

static void rcon_network(Client &cl)
{
    while (cl.isConnected()) {
        cl.loop();
        cl.executePackets();
    }
}

static int rcon_shell(const std::string &key, const std::string &ip, int port)
{
    Client cl(ip, port);
    cl.getPacketListener().addExecutor(std::make_unique<RCONExecutor>());
    cl.connect();
    if (!cl.isConnected()) {
        RCON_LOG("Could not connect to " << ip << ":" << port << ", aborting..");
        return 1;
    }
    std::thread networkTest(rcon_network, std::ref(cl));
    CommandManager cmdManager;

    std::string command;
    while (cl.isConnected()) {
        std::cout << "❯ ";
        std::getline(std::cin, command);

        try {
            cmdManager.execute(cl, command, key);
        } catch (const CommandManager::CommandException &e) {
            RCON_LOG(e.what());
        }
    }
    return 0; 
}


int main(int argc, char **argv)
{
    std::string key = "";

    if (argc != 3) {
        RCON_LOG("Usage: ./r-type_rcon <ip> <port>");
        return 84;
    }
    RCON_LOG("Retrieving RCON Key..");
    if (!readConfig(key)) {
        RCON_LOG("Could not retrieve RCON Key, aborting...");
        return 84;
    }
    RCON_LOG("Could retrieve RCON Key: " << key);
    return rcon_shell(key, argv[1], atoi(argv[2]));
}
