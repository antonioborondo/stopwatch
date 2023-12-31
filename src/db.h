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

    void DeleteLast();

    std::string Summary(const Timestamp& timestamp = Timestamp::GetCurrent());

    bool DeleteRecords();

    bool AddRecord(const Record& record);

    Record GetLastRecord(const Timestamp& timestamp);

    std::vector<Record> GetRecords(const Timestamp& timestamp = Timestamp::GetCurrent()) const;

private:
    std::string GetTime(double time_in_days);

    std::filesystem::path GetDataDirectory();

    void CreateDataDirectory(const std::filesystem::path& data_directory);
};
