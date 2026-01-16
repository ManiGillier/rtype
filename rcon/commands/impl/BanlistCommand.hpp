/*
** EPITECH PROJECT, 2026
** rtype [WSL: Ubuntu-24.04]
** File description:
** BanlistCommand
*/

#ifndef BANLISTCOMMAND_HPP_
    #define BANLISTCOMMAND_HPP_

    #include <rcon/commands/ICommand.hpp>
    #include <network/packets/impl/RCONRequest.hpp>

class BanlistCommand : public ICommand {
    public:
        std::string getCommandName() const {
            return "banlist";
        }

        std::string getHelp() const {
            return "Get the list of all banned players";
        }

        std::string getUsage() const {
            return "banlist";
        }

        std::size_t getArgumentCount() const {
            return 0;
        }

        void executeCommand(Client &cl,
            std::vector<std::string> args, const std::string &key,
            CommandManager &cm) const {
                (void) args;
                (void) cm;

                cl.sendPacket(create_packet(RCONRequest, RCONRequest::BANLIST, key));
            }
};

#endif /* !BANLISTCOMMAND_HPP_ */
