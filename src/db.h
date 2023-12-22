#pragma once

#include "record.h"

#include <string>

struct sqlite3;

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

    bool AddRecord(const Record& record);

    Record GetLastRecord();

    std::string GetLastRecordTimestamp();
};
