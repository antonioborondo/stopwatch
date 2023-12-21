#include "db.h"

Db::Db()
{
    sqlite3_open("sw.db", &db_);

    std::string sql{"CREATE TABLE IF NOT EXISTS log (timestamp TEXT PRIMARY KEY NOT NULL "
        "DEFAULT(strftime('%Y-%m-%d %H:%M:%f', 'now', 'localtime')), type INTEGER NOT NULL)"};
    sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
}

Db::~Db()
{
    sqlite3_close(db_);
}

void Db::Log(LogType log_type)
{
    std::string sql{
        "INSERT INTO log (type) VALUES(" + std::to_string(static_cast<int>(log_type)) + ")"};
    sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
}

std::string Db::Summary()
{
    bool tempRecord{GetLastType() == 1};

    if(tempRecord)
    {
        Log(LogType::kOut);
    }

    std::string sql{"SELECT                                                                     "
                    "    CAST (SUM(difference) * 24 AS REAL)                                    "
                    "FROM                                                                       "
                    "(                                                                          "
                    "    SELECT                                                                 "
                    "        julianday(records.logout) - julianday(records.login) AS difference "
                    "    FROM                                                                   "
                    "    (                                                                      "
                    "        SELECT                                                             "
                    "            login_records.timestamp AS login,                              "
                    "            logout_records.timestamp AS logout                             "
                    "        FROM                                                               "
                    "        (                                                                  "
                    "            SELECT                                                         "
                    "                row_number() OVER (ORDER BY timestamp) AS row_number,      "
                    "                timestamp                                                  "
                    "            FROM                                                           "
                    "                log                                                        "
                    "            WHERE                                                          "
                    "                timestamp >= date('now')                                   "
                    "                AND                                                        "
                    "                type = 1                                                   "
                    "        ) AS login_records,                                                "
                    "        (                                                                  "
                    "            SELECT                                                         "
                    "                row_number() OVER (ORDER BY timestamp) AS row_number,      "
                    "                timestamp                                                  "
                    "            FROM                                                           "
                    "                log                                                        "
                    "            WHERE                                                          "
                    "                timestamp >= date('now')                                   "
                    "                AND                                                        "
                    "                type = 0                                                   "
                    "        ) AS logout_records                                                "
                    "        WHERE                                                              "
                    "            login_records.row_number = logout_records.row_number           "
                    "    ) as records                                                           "
                    ")                                                                          "};

    sqlite3_stmt* stmt{nullptr};

    int retval = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, 0);
    double result;

    int idx = 0;

    while(1)
    {
        retval = sqlite3_step(stmt);

        if(retval == SQLITE_ROW)
        {
            result = sqlite3_column_double(stmt, 0);
        }
        else if(retval == SQLITE_DONE)
        {
            break;
        }
        else
        {
            sqlite3_finalize(stmt);
            printf("Some error encountered\n");
            break;
        }
    }

    sqlite3_finalize(stmt);

    if(tempRecord)
    {
        DeleteLast();
    }

    return std::to_string(result);
}

int Db::GetLastType()
{
    std::string sql{"SELECT type FROM log ORDER BY timestamp DESC LIMIT 1"};

    sqlite3_stmt* stmt{nullptr};

    int retval = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, 0);
    int result;

    int idx = 0;

    while(1)
    {
        retval = sqlite3_step(stmt);

        if(retval == SQLITE_ROW)
        {
            result = sqlite3_column_int(stmt, 0);
        }
        else if(retval == SQLITE_DONE)
        {
            break;
        }
        else
        {
            sqlite3_finalize(stmt);
            printf("Some error encountered\n");
            break;
        }
    }

    sqlite3_finalize(stmt);

    return result;
}

void Db::DeleteLast()
{
    char *zErrMsg = 0;
    std::string sql{"DELETE FROM log WHERE timestamp = (SELECT MAX(timestamp) FROM log)"};

    int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if( rc!=SQLITE_OK ){

      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
    }
}
