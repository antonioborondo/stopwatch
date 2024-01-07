#include "timestamp.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>

TEST(TimestampTest, Valid) {
  ASSERT_NO_THROW(Timestamp::GetCurrent());
  ASSERT_NO_THROW(Timestamp{"0001-01-01 01:01:01"});
}

TEST(TimestampTest, Invalid) {
  ASSERT_THROW(Timestamp{"0001-01-01"}, std::invalid_argument);
  ASSERT_THROW(Timestamp{"01:01:01"}, std::invalid_argument);
}

TEST(TimestampTest, Get) {
  const Timestamp timestamp{"0001-01-01 01:01:01"};
  ASSERT_EQ("0001-01-01 01:01:01", timestamp.Get());
}

TEST(TimestampTest, GetDate) {
  const Timestamp timestamp{"0001-01-01 01:01:01"};
  ASSERT_EQ("0001-01-01", timestamp.GetDate());
}

TEST(TimestampTest, GetTime) {
  const Timestamp timestamp{"0001-01-01 01:01:01"};
  ASSERT_EQ("01:01:01", timestamp.GetTime());
}

TEST(TimestampTest, Equal) {
  const Timestamp timestamp_1{"0001-01-01 01:01:01"};
  const Timestamp timestamp_2{"0001-01-01 01:01:01"};
  ASSERT_EQ(timestamp_1, timestamp_2);
}

TEST(TimestampTest, NotEqual) {
  const Timestamp timestamp_1{"0001-01-01 01:01:01"};
  const Timestamp timestamp_2{"0001-01-01 01:01:02"};
  ASSERT_NE(timestamp_1, timestamp_2);
}

TEST(TimestampTest, Sink) {
  const std::string timestamp_string{"0001-01-01 01:01:01"};
  const Timestamp timestamp{timestamp_string};
  std::ostringstream sink;
  sink << timestamp;
  ASSERT_EQ(timestamp_string, sink.str());
}
