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
    #include <SQLiteCpp/SQLiteCpp.h>

class AccountDatabase {
    public:
        AccountDatabase();
        virtual ~AccountDatabase() = default;
        void put(const std::string &username, const std::string &password) const;
        bool hasUsername(const std::string &username) const;
        bool hasPassword(const std::string &username) const;
        std::string getPasswordByUsername(const std::string &username) const;
        std::vector<std::string> getAllUsernamesWithPassword(const std::string &password) const;
        bool isConnected() const;
    private:
        bool connected = false;
        SQLite::Database db;
};

#endif /* !ACCOUNTDATABASE_HPP_ */
