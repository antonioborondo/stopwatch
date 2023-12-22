#pragma once

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


    enum class Type
    {
        kStop = 0,
        kStart,
    };

    bool AddRecord(Type type, const std::string& timestamp = "");

    std::string GetLastRecordTimestamp();
};
