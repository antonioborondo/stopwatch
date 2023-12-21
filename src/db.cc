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
    std::string sql{"SELECT round(CAST (SUM(difference) * 24 AS REAL), 2) FROM (SELECT records.login AS login, records.logout AS logout, julianday(records.logout) - julianday(records.login) AS difference FROM (SELECT login.timestamp AS login, logout.timestamp AS logout FROM (SELECT timestamp, row_number() OVER (ORDER BY timestamp) AS row_number FROM log WHERE timestamp >= date('now') AND type = 1) AS login, (SELECT timestamp, row_number() OVER (ORDER BY timestamp) AS row_number FROM log WHERE timestamp >= date('now') AND type = 0) AS logout WHERE login.row_number = logout.row_number) as records)"};
    sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);

    return std::string{};
}
