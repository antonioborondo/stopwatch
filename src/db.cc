#include "db.h"

Db::Db()
{
    sqlite3_open("sw.db", &db_);

    std::string sql{"CREATE TABLE IF NOT EXISTS log (timestamp TEXT PRIMARY KEY NOT NULL DEFAULT(strftime('%Y-%m-%d %H:%M:%f', 'now', 'localtime')), type INTEGER NOT NULL)"};
    sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
}

Db::~Db()
{
    sqlite3_close(db_);
}

void Db::Log(LogType log_type)
{
    std::string sql{"INSERT INTO log (type) VALUES(" + std::to_string(static_cast<int>(log_type)) + ")"};
    sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
}

std::string Db::Summary()
{
    return std::string{};
}
