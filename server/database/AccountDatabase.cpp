/*
** EPITECH PROJECT, 2026
** rtype
** File description:
** AccountDatabase
*/

#include <SQLiteCpp/Transaction.h>
#include <network/logger/Logger.hpp>
#include "AccountDatabase.hpp"

AccountDatabase::AccountDatabase()
{
    try {
        SQLite::Database db(SQLite::Database("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE));
        db.exec("CREATE TABLE IF NOT EXISTS accounts (username TEXT UNIQUE NOT NULL, password TEXT UNIQUE NOT NULL)");
    } catch (const std::exception &e) {}
}

bool AccountDatabase::put(const std::string &username,
                          const std::string &password) const
{
    try {
        SQLite::Database db("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Transaction transaction(db);

        db.exec("INSERT INTO accounts VALUES (\"" + username + "\", \"" + password + "\")");

        transaction.commit();
        return true;
    } catch (std::exception &e) {
        LOG_ERR(e.what());
        throw DatabaseError(COULD_NOT_CREATE_ACCOUNT);
        return false;
    }
}

bool AccountDatabase::hasUsername(const std::string &username) const
{
   try {
        SQLite::Database db("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT * FROM accounts WHERE username=\"" + username + "\"");

        return query.executeStep();
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_VERIFY_USERNAME);
    }
}

bool AccountDatabase::hasPassword(const std::string &password) const
{
   try {
        SQLite::Database db("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT * FROM accounts WHERE password=\"" + password + "\"");

        return query.executeStep();
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_VERIFY_PASSWORD);
        return false;
    }
}

std::string AccountDatabase::getPasswordByUsername(const std::string &username) const
{
   try {
        SQLite::Database db("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT `password` FROM accounts WHERE username=\"" + username + "\"");

        if (query.executeStep()) {
            return (std::string) query.getColumn(0);
        }
        throw DatabaseError(COULD_NOT_VERIFY_ACCOUNT_PASSWORD);
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_VERIFY_ACCOUNT_PASSWORD);
        return "";
    }
}

std::vector<std::string> AccountDatabase::getAllUsernamesWithPassword(const std::string &password) const
{
   try {
        SQLite::Database db("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        SQLite::Statement query(db, "SELECT `username` FROM accounts WHERE `password`=\"" + password + "\"");
        std::vector<std::string> accounts;

        while (query.executeStep()) {
            accounts.push_back(query.getColumn(0));
        }
        return accounts;
    } catch (std::exception &e) {
        LOG_ERR("SQLITE error: " << e.what());
        throw DatabaseError(COULD_NOT_GET_ACCOUNTS_WITH_PASSWORD);
    }
}
