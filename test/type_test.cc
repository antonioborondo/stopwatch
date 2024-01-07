#include "type.h"

#include <sstream>

#include <gtest/gtest.h>

TEST(TypeTest, Sink) {
  std::ostringstream sink;
  sink << Type::kStop;
  ASSERT_EQ("Stop", sink.str());
  sink.str("");
  sink.clear();
  sink << Type::kStart;
  ASSERT_EQ("Start", sink.str());
}
