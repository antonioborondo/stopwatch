#include "db.h"
#include "record.h"

#include <gtest/gtest.h>

class DbTest: public testing::Test
{
protected:
    Db db_{};

    void TearDown() override
    {
        db_.DeleteRecords();
    }
};

TEST_F(DbTest, AddRecord)
{
    const Record record{Record::Type::kStart};

    ASSERT_TRUE(db_.AddRecord(record));

    Record record_result{db_.GetLastRecord()};
    ASSERT_EQ(record.GetType(), record_result.GetType());
    ASSERT_EQ(record.GetTimestamp(), record_result.GetTimestamp());
}

TEST_F(DbTest, AddRecordWithTimestamp)
{
    const Record record{Record::Type::kStart, "2023-10-23 09:00:00"};

    ASSERT_TRUE(db_.AddRecord(record));

    Record record_result{db_.GetLastRecord()};
    ASSERT_EQ(record.GetType(), record_result.GetType());
    ASSERT_EQ(record.GetTimestamp(), record_result.GetTimestamp());
}

TEST_F(DbTest, GetSummary)
{
    const Record record_1{Record::Type::kStart, "2023-10-23 09:00:00"};
    ASSERT_TRUE(db_.AddRecord(record_1));

    const Record record_2{Record::Type::kStop, "2023-10-23 10:00:01"};
    ASSERT_TRUE(db_.AddRecord(record_2));

    ASSERT_EQ("01:00:00", db_.Summary("2023-10-23"));
}

TEST_F(DbTest, GetSummaryWithPreviousDays)
{
    ASSERT_TRUE(db_.AddRecord(Record{Record::Type::kStart, "2023-10-22 09:00:00"}));
    ASSERT_TRUE(db_.AddRecord(Record{Record::Type::kStop, "2023-10-22 10:00:00"}));
    ASSERT_TRUE(db_.AddRecord(Record{Record::Type::kStart, "2023-10-23 09:00:00"}));
    ASSERT_TRUE(db_.AddRecord(Record{Record::Type::kStop, "2023-10-23 10:00:01"}));
    ASSERT_TRUE(db_.AddRecord(Record{Record::Type::kStart, "2023-10-24 09:00:00"}));
    ASSERT_TRUE(db_.AddRecord(Record{Record::Type::kStop, "2023-10-24 10:00:00"}));

    ASSERT_EQ("01:00:00", db_.Summary("2023-10-23"));
}
