/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** RType
*/

#include "RType.hpp"
#include "./error/ArgsError.hpp"
#include "network/logger/Logger.hpp"
#include "server/network/executor/GameStartExecutor.hpp"
#include "server/network/executor/ClientInputsExecutor.hpp"
#include "server/network/server/RTypeServer.hpp"
#include <iostream>
#include <fstream>
#include "server/network/executor/RegisterExecutor.hpp"
#include "server/network/executor/LoginExecutor.hpp"
#include "server/network/executor/RCONRequestExecutor.hpp"
#include <string>
#include <ctime>
#include "utils/RandomUtils.hpp"
#include <filesystem>

RType::RType(int argc, char **argv)
{
    if (argc <= 1)
        throw ArgsError("missing arguments try: " + std::string(argv[0]) +
                        " --help");
    if (argc == 2) {
        if (std::string(argv[1]) == "--help") {
            this->displayUsage();
            return;
        }
        throw ArgsError("unexpected argument " + std::string(argv[1]));
    }
    for (int i = 1; i < argc; i++) {
        const std::string arg(argv[i]);
        if (i + 1 < argc || arg == "-d") {
            if (arg == "-t") {
                _ticks = std::atoi(argv[i + 1]);
            } else if (arg == "-p") {
                _port = std::atoi(argv[i + 1]);
            } else if (arg == "-d") {
                Logger::shouldLog = true;
            } else {
                throw ArgsError("unexpected argument " + std::string(argv[i]));
            }
            i += 1;
        } else {
            throw ArgsError("unexpected argument " + std::string(argv[i]) +
                            " wihtout value");
        }
    }
    if (_ticks < 1 || _ticks > 120)
        throw ArgsError("We’re not at the butcher’s shop; "
                        "please try a different tick value.");
}

int RType::displayUsage()
{
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t ./r-type_server {-p port} [-t tick (between 1 and "
                 "120) ] [-d]"
              << std::endl;
    std::cout << "\t : {} = mendatory" << std::endl;
    std::cout << "\t : [] = optional" << std::endl;
    exit(0);
}

void RType::initExecutor(RTypeServer &server)
{
    server.getPacketListener().addExecutor(
        std::make_unique<GameStartExecutor>(server));
    server.getPacketListener().addExecutor(
        std::make_unique<ClientInputsExecutor>(server));
    server.getPacketListener().addExecutor(
        std::make_unique<LoginExecutor>(server));
    server.getPacketListener().addExecutor(
        std::make_unique<RegisterExecutor>(server));
    server.getPacketListener().addExecutor(
        std::make_unique<RCONRequestExecutor>(server));
}

void RType::networkLoop()
{
    RTypeServer server(this->_port, this->_ticks);
    if (!server.up()) {
        LOG_ERR("RType server Can't connect");
        return;
    }
    RTypeConfig &cfg = server.getRTypeConfig();
    if (cfg.shouldCreateConfig() && !cfg.createConfig()) {
        LOG_ERR("Could not create RType Config, aborting..");
        return;
    }
    if (!cfg.readConfig()) {
        LOG_ERR("Could not read RType Config, trying to reset it..");
        if (!cfg.createConfig()) {
            LOG_ERR("Could not reset RType Confg, aborting..");
        }
        LOG("Could reset config !");
    }
    LOG("Could get RCON Key=" << cfg.getKey());
    this->initExecutor(server);
    server.getPacketListener().addToWhitelist(PacketId::LOGIN_PACKET);
    server.getPacketListener().addToWhitelist(PacketId::REGISTER_PACKET);
    server.getPacketListener().addToWhitelist(PacketId::RCON_REQUEST);
    while (server.isUp()) {
        server.loop();
        server.cleanFinishedGame();
    }
}

int RType::launch()
{
    srand((unsigned) time(NULL));
    if (_displayUsage)
        return displayUsage();

    std::thread server(&RType::networkLoop, this);
    server.join();
    return 0;
}

bool RTypeConfig::createConfig()
{
    std::ofstream config(CONFIG_FILE);

    if (!config.is_open())
        return false;
    config << "RCON_KEY=" << RandomUtils::generateRandomUUID(16);
    this->key = TO_CHANGE;
    if (!config)
        return false;
    config << std::endl;
    config.close();
    return true;
}

bool RTypeConfig::readConfig()
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
                this->key = value;
        }
    }
    if (!config.eof() && config.fail())
        return false;
    config.close();
    return true;
}

bool RTypeConfig::shouldCreateConfig() const
{
    return !std::filesystem::exists(CONFIG_FILE);
}

const std::string &RTypeConfig::getKey() const
{
    return this->key;
}
