#include "db.h"

#include <gtest/gtest.h>

class DbTest: public testing::Test
{
protected:
    Db db_{};
};

TEST_F(DbTest, AddRecord)
{
    const std::string timestamp{"2023-10-23 09:00:00.000"};
    ASSERT_TRUE(db_.AddRecord(Db::Type::kStart, timestamp));
    ASSERT_EQ(timestamp, db_.GetLastRecordTimestamp());
}
