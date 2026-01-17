#include <SQLiteCpp/Transaction.h>
#include <network/logger/Logger.hpp>
#include "AccountDatabase.hpp"

AccountDatabase::AccountDatabase()
    : db("account_db.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{
    try {
        db.exec("PRAGMA journal_mode=WAL;");

        SQLite::Statement query(db,
            "SELECT COUNT(*) FROM pragma_table_info('accounts') "
            "WHERE name='isBanned'");

        if (query.executeStep() && query.getColumn(0).getInt() == 0)
            db.exec("DROP TABLE IF EXISTS accounts");

        db.exec("CREATE TABLE IF NOT EXISTS accounts ("
                "username TEXT UNIQUE NOT NULL, "
                "password TEXT UNIQUE NOT NULL, "
                "isBanned INTEGER DEFAULT 0, "
                "score INTEGER DEFAULT 0)");
    } catch (const std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
    }
}

std::vector<std::string> AccountDatabase::getScoreboard() const
{
    try {
        std::vector<std::string> usernames;

        SQLite::Statement query(
            db,
            "SELECT username FROM accounts "
            "ORDER BY score DESC "
            "LIMIT 10"
        );

        while (query.executeStep()) {
            usernames.push_back(query.getColumn(0).getString());
        }

        return usernames;
    }
    catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_GET_SCOREBOARD);
    }
}


bool AccountDatabase::put(const std::string &username,
                          const std::string &password) const
{
    try {
        SQLite::Transaction transaction(db);
        SQLite::Statement query(db,
            "INSERT INTO accounts (username, password) VALUES (?, ?)");
        query.bind(1, username);
        query.bind(2, password);
        query.exec();
        transaction.commit();
        return true;
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_CREATE_ACCOUNT);
    }
}

bool AccountDatabase::hasUsername(const std::string &username) const
{
    try {
        SQLite::Statement query(db,
            "SELECT 1 FROM accounts WHERE username=?");
        query.bind(1, username);
        return query.executeStep();
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_VERIFY_USERNAME);
    }
}

bool AccountDatabase::hasPassword(const std::string &password) const
{
    try {
        SQLite::Statement query(db,
            "SELECT 1 FROM accounts WHERE password=?");
        query.bind(1, password);
        return query.executeStep();
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_VERIFY_PASSWORD);
    }
}

std::string AccountDatabase::getPasswordByUsername(
    const std::string &username) const
{
    try {
        SQLite::Statement query(db,
            "SELECT password FROM accounts WHERE username=?");
        query.bind(1, username);

        if (query.executeStep()) {
            return query.getColumn(0).getString();
        }
        throw DatabaseError(COULD_NOT_VERIFY_ACCOUNT_PASSWORD);
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_VERIFY_ACCOUNT_PASSWORD);
    }
}

std::vector<std::string> AccountDatabase::getAllUsernamesWithPassword(
    const std::string &password) const
{
    try {
        SQLite::Statement query(db,
            "SELECT username FROM accounts WHERE password=?");
        query.bind(1, password);
        std::vector<std::string> accounts;

        while (query.executeStep()) {
            accounts.push_back(query.getColumn(0).getString());
        }
        return accounts;
    } catch (std::exception &e) {
        LOG_ERR("SQLITE error: " << e.what());
        throw DatabaseError(COULD_NOT_GET_ACCOUNTS_WITH_PASSWORD);
    }
}

int AccountDatabase::getScore(const std::string &username) const
{
    try {
        SQLite::Statement query(db,
            "SELECT score FROM accounts WHERE username=?");
        query.bind(1, username);

        if (query.executeStep()) {
            return query.getColumn(0).getInt();
        }
        throw DatabaseError(COULD_NOT_GET_SCORE);
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_GET_SCORE);
    }
}

void AccountDatabase::setScore(const std::string &username,
                               int score) const
{
    try {
        SQLite::Transaction transaction(db);
        SQLite::Statement query(db,
            "UPDATE accounts SET score=? WHERE username=?");
        query.bind(1, score);
        query.bind(2, username);
        query.exec();
        transaction.commit();
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_SET_SCORE);
    }
}

void AccountDatabase::setBanned(const std::string &username,
                                bool banned) const
{
    try {
        SQLite::Transaction transaction(db);
        SQLite::Statement query(db,
            "UPDATE accounts SET isBanned=? WHERE username=?");
        query.bind(1, banned ? 1 : 0);
        query.bind(2, username);
        query.exec();
        transaction.commit();
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_SET_BANNED);
    }
}

bool AccountDatabase::isBanned(const std::string &username) const
{
    try {
        SQLite::Statement query(db,
            "SELECT isBanned FROM accounts WHERE username=?");
        query.bind(1, username);

        if (query.executeStep()) {
            return query.getColumn(0).getInt() != 0;
        }
        throw DatabaseError(COULD_NOT_GET_BANNED_STATUS);
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_GET_BANNED_STATUS);
    }
} 

std::vector<std::string> AccountDatabase::getAllBans() const
{
    try {
        SQLite::Statement query(db,
            "SELECT username FROM accounts WHERE isBanned=1");
        std::vector<std::string> bannedPlayers;

        while (query.executeStep()) {
            bannedPlayers.push_back(query.getColumn(0).getString());
        }
        return bannedPlayers;
    } catch (std::exception &e) {
        LOG_ERR("SQLite error: " << e.what());
        throw DatabaseError(COULD_NOT_GET_BANNED_PLAYERS);
    }
}

