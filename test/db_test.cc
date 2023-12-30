#include "db.h"
#include "record.h"
#include "type.h"

#include <gmock/gmock.h>
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
    const Timestamp timestamp{Timestamp::GetCurrent()};
    const Record record{Type::kStart, timestamp};
    ASSERT_TRUE(db_.AddRecord(record));

    Record last_record{db_.GetLastRecord(timestamp)};
    ASSERT_EQ(record.GetType(), last_record.GetType());
    ASSERT_EQ(record.GetTimestamp(), last_record.GetTimestamp());
}

TEST_F(DbTest, AddRecordWithTimestamp)
{
    const Record record{Type::kStart, Timestamp("0001-01-01 01:01:01")};
    ASSERT_TRUE(db_.AddRecord(record));

    const Record last_record{db_.GetLastRecord(Timestamp("0001-01-01 01:01:01"))};
    ASSERT_EQ(record.GetType(), last_record.GetType());
    ASSERT_EQ(record.GetTimestamp(), last_record.GetTimestamp());
}

TEST_F(DbTest, AddNewRecordFailsWhenLastOneIsFromSameType)
{
    const Record record_1{Type::kStart, Timestamp("0001-01-01 01:01:01")};
    ASSERT_TRUE(db_.AddRecord(record_1));
    const Record record_2{Type::kStart, Timestamp("0001-01-01 01:01:02")};
    ASSERT_FALSE(db_.AddRecord(record_2));
}

TEST_F(DbTest, AddNewRecordSucceedsWhenLastOneIsFromSameTypeButFromDifferentDay)
{
    const Record record_1{Type::kStart, Timestamp("0001-01-01 01:01:01")};
    ASSERT_TRUE(db_.AddRecord(record_1));
    const Record record_2{Type::kStart, Timestamp("0001-01-02 01:01:01")};
    ASSERT_TRUE(db_.AddRecord(record_2));
}

TEST_F(DbTest, GetSummary)
{
    const Record record_1{Type::kStart, Timestamp("2023-10-23 09:00:00")};
    ASSERT_TRUE(db_.AddRecord(record_1));

    const Record record_2{Type::kStop, Timestamp("2023-10-23 10:00:01")};
    ASSERT_TRUE(db_.AddRecord(record_2));

    ASSERT_EQ("01:00:00", db_.Summary(Timestamp("2023-10-23 09:00:00")));
}

TEST_F(DbTest, GetSummaryWithPreviousDays)
{
    ASSERT_TRUE(db_.AddRecord(Record{Type::kStart, Timestamp("2023-10-22 09:00:00")}));
    ASSERT_TRUE(db_.AddRecord(Record{Type::kStop, Timestamp("2023-10-22 10:00:00")}));
    ASSERT_TRUE(db_.AddRecord(Record{Type::kStart, Timestamp("2023-10-23 09:00:00")}));
    ASSERT_TRUE(db_.AddRecord(Record{Type::kStop, Timestamp("2023-10-23 10:00:01")}));
    ASSERT_TRUE(db_.AddRecord(Record{Type::kStart, Timestamp("2023-10-24 09:00:00")}));
    ASSERT_TRUE(db_.AddRecord(Record{Type::kStop, Timestamp("2023-10-24 10:00:00")}));

    ASSERT_EQ("01:00:00", db_.Summary(Timestamp("2023-10-23 09:00:00")));
}

TEST_F(DbTest, GetRecords)
{
    Record record_0{Type::kStart, Timestamp("2023-10-23 00:00:00")};
    ASSERT_TRUE(db_.AddRecord(record_0));
    Record record_1{Type::kStop, Timestamp("2023-10-23 00:00:01")};
    ASSERT_TRUE(db_.AddRecord(record_1));
    Record record_2{Type::kStart, Timestamp("2023-10-23 00:00:02")};
    ASSERT_TRUE(db_.AddRecord(record_2));
    Record record_3{Type::kStop, Timestamp("2023-10-23 00:00:03")};
    ASSERT_TRUE(db_.AddRecord(record_3));

    std::vector<Record> records{db_.GetRecords(Timestamp("2023-10-23 00:00:00"))};

    ASSERT_THAT(records, testing::ElementsAre(record_0, record_1, record_2, record_3));
}
