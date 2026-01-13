/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** AccountDatabase
*/

#include "AccountDatabase.hpp"

AccountDatabase::AccountDatabase() try : db(SQLite::Database("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)) {
    db.exec("CREATE TABLE IF NOT EXISTS accounts (username TEXT UNIQUE NOT NULL, password TEXT UNIQUE NOT NULL)");
    this->connected = true;
} catch (const std::exception &e) {}

void AccountDatabase::put(const std::string &username,
                          const std::string &password) const
{
    (void) username;
    (void) password;
    return;
}

bool AccountDatabase::hasUsername(const std::string &username) const
{
    (void) username;
    return false;
}

bool AccountDatabase::hasPassword(const std::string &username) const
{
    (void) username;
    return false;
}

std::string AccountDatabase::getPasswordByUsername(const std::string &username) const
{
    (void) username;
    return std::string();
}

std::vector<std::string> AccountDatabase::getAllUsernamesWithPassword(const std::string &password) const
{
    (void) password;
    return std::vector<std::string>();
}

bool AccountDatabase::isConnected() const
{
    return this->connected;
}
