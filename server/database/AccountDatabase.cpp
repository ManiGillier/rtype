/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** AccountDatabase
*/

#include "AccountDatabase.hpp"

AccountDatabase::AccountDatabase() : db(SQLite::Database("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE))
{
    db.exec("CREATE TABLE test (username TEXT UNIQUE, password TEXT UNIQUE)");
}

void AccountDatabase::put(const std::string &username,
                          const std::string &password) const
{
    return;
}

bool AccountDatabase::hasUsername(const std::string &username) const
{
    return false;
}

bool AccountDatabase::hasPassword(const std::string &username) const
{
    return false;
}

std::string AccountDatabase::getPasswordByUsername(const std::string &username) const
{
    return std::string();
}

std::vector<std::string> AccountDatabase::getAllUsernamesWithPassword(const std::string &password) const
{
    return std::vector<std::string>();
}

AccountDatabase::~AccountDatabase()
{
    return;
}
