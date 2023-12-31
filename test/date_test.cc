#include "date.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(DateTest, Valid)
{
    ASSERT_NO_THROW(Date::GetCurrent());
    ASSERT_NO_THROW(Date{"0001-01-01"});
}

TEST(DateTest, Invalid)
{
    ASSERT_THROW(Date{"0001-01-01 01:01:01"}, std::invalid_argument);
    ASSERT_THROW(Date{"01:01:01"}, std::invalid_argument);
}

TEST(DateTest, Sink)
{
    const std::string date_string{"0001-01-01"};
    const Date date{date_string};
    std::ostringstream sink;
    sink << date;
    ASSERT_EQ(date_string, sink.str());
}
