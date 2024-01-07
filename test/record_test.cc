#include "record.h"

#include <gtest/gtest.h>

#include "timestamp.h"

TEST(RecordTest, GetType) {
  const Timestamp timestamp{Timestamp::GetCurrent()};
  const Record record_1{Type::kStart, timestamp};
  ASSERT_EQ(Type::kStart, record_1.GetType());
  const Record record_2{Type::kStop, timestamp};
  ASSERT_EQ(Type::kStop, record_2.GetType());
}

TEST(RecordTest, GetTimestamp) {
  const Timestamp timestamp{Timestamp::GetCurrent()};
  const Record record{Type::kStart, timestamp};
  ASSERT_EQ(timestamp, record.GetTimestamp());
}

TEST(RecordTest, Equal) {
  const Timestamp timestamp{Timestamp::GetCurrent()};
  const Record record_1{Type::kStart, timestamp};
  const Record record_2{Type::kStart, timestamp};
  ASSERT_EQ(record_1, record_2);
  const Record record_3{Type::kStop, timestamp};
  const Record record_4{Type::kStop, timestamp};
  ASSERT_EQ(record_3, record_4);
}

TEST(RecordTest, NotEqual) {
  const Record record_1{Type::kStart, Timestamp{"0001-01-01 01:01:01"}};
  const Record record_2{Type::kStart, Timestamp{"0001-01-01 01:01:02"}};
  ASSERT_NE(record_1, record_2);
  const Timestamp timestamp{Timestamp::GetCurrent()};
  const Record record_3{Type::kStart, timestamp};
  const Record record_4{Type::kStop, timestamp};
  ASSERT_NE(record_3, record_4);
  const Record record_5{Type::kStart, Timestamp{"0001-01-01 01:01:01"}};
  const Record record_6{Type::kStop, Timestamp{"0001-01-01 01:01:02"}};
  ASSERT_NE(record_5, record_6);
}
