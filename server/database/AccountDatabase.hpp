/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** AccountDatabase
*/

#ifndef ACCOUNTDATABASE_HPP_
    #define ACCOUNTDATABASE_HPP_

    #include <string>
    #include <vector>
    #include <exception>
    #include <SQLiteCpp/SQLiteCpp.h>

    #define COULD_NOT_VERIFY_USERNAME "Could not verify if username exists"
    #define COULD_NOT_VERIFY_PASSWORD "Could not verify if password already exists"
    #define COULD_NOT_CREATE_ACCOUNT "Could not create account"
    #define COULD_NOT_VERIFY_ACCOUNT_PASSWORD "Could not verify account password"
    #define COULD_NOT_GET_ACCOUNTS_WITH_PASSWORD "Could not get all accounts with similar password"

class AccountDatabase {
    public:
        class DatabaseError : public std::exception {
            public:
                DatabaseError(const std::string &error) {
                    this->exception = error + ". Please report this error to the developper";
                }

                const char *what() const noexcept override {
                    return exception.c_str();
                }
            private:
                std::string exception;
        };
        AccountDatabase();
        virtual ~AccountDatabase() = default;
        bool put(const std::string &username, const std::string &password) const;
        bool hasUsername(const std::string &username) const;
        bool hasPassword(const std::string &username) const;
        std::string getPasswordByUsername(const std::string &username) const;
        std::vector<std::string> getAllUsernamesWithPassword(const std::string &password) const;
};

#endif /* !ACCOUNTDATABASE_HPP_ */
