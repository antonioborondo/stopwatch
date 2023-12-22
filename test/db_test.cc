#include "db.h"
#include "record.h"

#include <gtest/gtest.h>

class DbTest: public testing::Test
{
protected:
    Db db_{};
};

TEST_F(DbTest, AddRecord)
{
    const Record record{Record::Type::kStart, "2023-10-23 09:00:00.000"};

    ASSERT_TRUE(db_.AddRecord(record));
    ASSERT_EQ(record.GetTimestamp(), db_.GetLastRecordTimestamp());
}
