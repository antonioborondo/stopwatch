#include "timestamp.h"

#include <gtest/gtest.h>

TEST(TimestampTest, Valid)
{
    ASSERT_NO_THROW(Timestamp::GetCurrent());
    ASSERT_NO_THROW(Timestamp{"0001-01-01 01:01:01"});
}

TEST(TimestampTest, Invalid)
{
    ASSERT_THROW(Timestamp{"0001-01-01"}, std::invalid_argument);
    ASSERT_THROW(Timestamp{"01:01:01"}, std::invalid_argument);
}

TEST(TimestampTest, Get)
{
    const Timestamp timestamp{"0001-01-01 01:01:01"};
    ASSERT_EQ("0001-01-01 01:01:01", timestamp.Get());
}

TEST(TimestampTest, GetDate)
{
    const Timestamp timestamp{"0001-01-01 01:01:01"};
    ASSERT_EQ("0001-01-01", timestamp.GetDate());
}

TEST(TimestampTest, GetTime)
{
    const Timestamp timestamp{"0001-01-01 01:01:01"};
    ASSERT_EQ("01:01:01", timestamp.GetTime());
}
