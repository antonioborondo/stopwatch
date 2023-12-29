#pragma once

#include "record.h"
#include "timestamp.h"

#include <filesystem>
#include <string>
#include <vector>

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

    Record GetLastRecord(const std::string& date = timestamp::GetCurrentDate());

    std::vector<Record> GetRecords(const std::string& date = timestamp::GetCurrentDate()) const;

private:
    std::string GetTime(double time_in_days);

    std::filesystem::path GetDataDirectory();

    void CreateDataDirectory(const std::filesystem::path& data_directory);
};
