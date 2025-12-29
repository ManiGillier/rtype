/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** args error class
*/

#ifndef ARGSERROR
    #define ARGSERROR

#include <string>

class ArgsError : public std::exception
{
  public:
    ArgsError(const std::string &message) : message_(message) {}
    const char *what() const throw()
    {
        return message_.c_str();
    }

  private:
    std::string message_;
};

#endif
