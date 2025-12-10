/*
** EPITECH PROJECT, 2025
** jetpack
** File description:
** IPollable
*/

#ifndef IPOLLABLE_HPP_
    #define IPOLLABLE_HPP_

class IPollable {
    public:
        virtual ~IPollable() = default;
        virtual int getFileDescriptor() = 0;
        virtual short getFlags() const = 0;
        virtual bool receiveEvent(short revent) = 0;
};

#endif /* !IPOLLABLE_HPP_ */
