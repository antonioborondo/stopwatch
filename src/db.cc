#include "db.h"

#include <fmt/format.h>

#include <iostream>
#include <sqlite3.h>

Db::Db()
{
    sqlite3_open("time_tracker.db", &db_);

    std::string sql{"CREATE TABLE IF NOT EXISTS records"
                    "("
                    "   type INTEGER NOT NULL,"
                    "   timestamp TEXT PRIMARY KEY NOT NULL"
                    ")"};

    sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
}

Db::~Db()
{
    sqlite3_close(db_);
}

std::string Db::Summary(const std::string& date)
{
    const auto last_record{GetLastRecord()};
    if(last_record.GetType() == Record::Type::kStart)
    {
        AddRecord(Record{Record::Type::kStop});
    }

    const auto sql_format_string{"SELECT                                                                       "
                                 "    CAST (SUM(difference) * 24 AS REAL)                                      "
                                 "FROM                                                                         "
                                 "(                                                                            "
                                 "    SELECT                                                                   "
                                 "        julianday(records2.logout) - julianday(records2.login) AS difference "
                                 "    FROM                                                                     "
                                 "    (                                                                        "
                                 "        SELECT                                                               "
                                 "            login_records.timestamp AS login,                                "
                                 "            logout_records.timestamp AS logout                               "
                                 "        FROM                                                                 "
                                 "        (                                                                    "
                                 "            SELECT                                                           "
                                 "                row_number() OVER (ORDER BY timestamp) AS row_number,        "
                                 "                timestamp                                                    "
                                 "            FROM                                                             "
                                 "                records                                                      "
                                 "            WHERE                                                            "
                                 "                date(timestamp) = '{0}'                                      "
                                 "                AND                                                          "
                                 "                type = 1                                                     "
                                 "        ) AS login_records,                                                  "
                                 "        (                                                                    "
                                 "            SELECT                                                           "
                                 "                row_number() OVER (ORDER BY timestamp) AS row_number,        "
                                 "                timestamp                                                    "
                                 "            FROM                                                             "
                                 "                records                                                      "
                                 "            WHERE                                                            "
                                 "                date(timestamp) = '{0}'                                      "
                                 "                AND                                                          "
                                 "                type = 0                                                     "
                                 "        ) AS logout_records                                                  "
                                 "        WHERE                                                                "
                                 "            login_records.row_number = logout_records.row_number             "
                                 "    ) as records2                                                            "
                                 ")                                                                            "};

    const auto sql{fmt::format(sql_format_string, date)};

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

    if(last_record.GetType() == Record::Type::kStart)
    {
        DeleteLast();
    }

    int hours = result;
    double minutesRemainder = (result - hours) * 60;
    int minutes = minutesRemainder;
    double secondsRemainder = (minutesRemainder - minutes) * 60;
    int seconds = secondsRemainder;

    return fmt::format("{0:02}:{1:02}:{1:02}", hours, minutes, seconds);
}

int Db::GetLastType()
{
    std::string sql{"SELECT type FROM records ORDER BY timestamp DESC LIMIT 1"};

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
    char* zErrMsg = 0;
    std::string sql{"DELETE FROM records WHERE timestamp = (SELECT MAX(timestamp) FROM records)"};

    int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

bool Db::DeleteRecords()
{
    const std::string sql{"DROP TABLE IF EXISTS records"};

    char* error_message{nullptr};
    const auto result{sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &error_message)};
    if(result != SQLITE_OK)
    {
        std::cerr << "SQL error: " << error_message << std::endl;
        sqlite3_free(error_message);

        return false;
    }

    return true;
}

bool Db::AddRecord(const Record& record)
{
    const auto sql_format_string{"INSERT INTO records (type, timestamp) VALUES({0}, '{1}')"};
    const auto sql{fmt::format(sql_format_string, std::to_string(static_cast<int>(record.GetType())), record.GetTimestamp())};

    char* error_message{nullptr};
    const auto result{sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &error_message)};
    if(result != SQLITE_OK)
    {
        std::cerr << "SQL error: " << error_message << std::endl;
        sqlite3_free(error_message);

        return false;
    }

    return true;
}

Record Db::GetLastRecord()
{
    std::string sql{"SELECT type, timestamp FROM records ORDER BY timestamp DESC LIMIT 1"};

    sqlite3_stmt* stmt{nullptr};

    int retval = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, 0);

    int type;
    std::string timestamp;

    int idx = 0;

    while(1)
    {
        retval = sqlite3_step(stmt);

        if(retval == SQLITE_ROW)
        {
            type = sqlite3_column_int(stmt, 0);
            timestamp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
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

    return Record{static_cast<Record::Type>(type), timestamp};
}
