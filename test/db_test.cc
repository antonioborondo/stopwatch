#include "db.h"
#include "record.h"

#include <gtest/gtest.h>

#include <filesystem>

class DbTest: public testing::Test
{
protected:
    Db db_{};

    ~DbTest()
    {
        std::filesystem::remove("time_tracker.db");
    }
};

TEST_F(DbTest, AddRecord)
{
    const Record record{Record::Type::kStart, "2023-10-23 09:00:00"};

    ASSERT_TRUE(db_.AddRecord(record));

    Record record_result{db_.GetLastRecord()};
    ASSERT_EQ(record.GetType(), record_result.GetType());
    ASSERT_EQ(record.GetTimestamp(), record_result.GetTimestamp());
}
