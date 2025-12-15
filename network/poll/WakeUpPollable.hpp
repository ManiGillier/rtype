/*
** EPITECH PROJECT, 2025
** rtype [WSL: Ubuntu-24.04]
** File description:
** WakeUpPollable
*/

#ifndef WAKEUPPOLLABLE_HPP_
    #define WAKEUPPOLLABLE_HPP_

    #include <network/poll/Pollable.hpp>

class WakeUpPollable : public Pollable {
    public:
        WakeUpPollable(PollManager &pm, int fd);
        short getFlags() const;
        bool receiveEvent(short revent);
        void sendPacket(std::shared_ptr<Packet> p, bool wakeUpPoll=true) { (void) p; (void) wakeUpPoll; };
};

#endif /* !WAKEUPPOLLABLE_HPP_ */
