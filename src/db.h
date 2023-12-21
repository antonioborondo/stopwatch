#pragma once

#include <sqlite3.h>
#include <string>

class Db
{
    sqlite3* db_;

public:
    Db();

    ~Db();

    enum class LogType
    {
        kOut = 0,
        kIn,
    };

    void Log(LogType log_type);

    int GetLastType();

    void DeleteLast();

    std::string Summary();
};
