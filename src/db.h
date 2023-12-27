#pragma once

#include "record.h"
#include "timestamp.h"

#include <string>

struct sqlite3;

class Db
{
    sqlite3* db_;

public:
    Db();

    ~Db();

    int GetLastType();

    void DeleteLast();

    std::string Summary(const std::string& date = timestamp::GetCurrentDate());

    bool DeleteRecords();

    bool AddRecord(const Record& record);

    Record GetLastRecord();
};
