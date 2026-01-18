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
        #define COULD_NOT_GET_SCORE "Could not get account score"
        #define COULD_NOT_SET_SCORE "Could not set account score"
        #define COULD_NOT_SET_BANNED "Could not set account banned status"
        #define COULD_NOT_GET_BANNED_STATUS "Could not get account banned status"
        #define COULD_NOT_GET_BANNED_PLAYERS "Could not get list of banned players"
        #define COULD_NOT_GET_SCOREBOARD "Could not get scoreboard"

class AccountDatabase {
private:
    mutable SQLite::Database db;

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
    bool put(const std::string &username,
             const std::string &password) const;
    bool hasUsername(const std::string &username) const;
    bool hasPassword(const std::string &password) const;
    std::string getPasswordByUsername(
        const std::string &username) const;
    std::vector<std::string> getAllUsernamesWithPassword(
        const std::string &password) const;
    int getScore(const std::string &username) const;
    void setScore(const std::string &username, int score) const;
    void setBanned(const std::string &username, bool banned) const;
    bool isBanned(const std::string &username) const;
    std::vector<std::tuple<std::string, int>> getScoreboard() const;
    std::vector<std::string> getAllBans() const;
};

#endif /* !ACCOUNTDATABASE_HPP_ */
