#pragma once

#include "timestamp.h"
#include "type.h"

class Record {
 public:
  Record(Type type, const Timestamp& timestamp = Timestamp::GetCurrent());

  Type GetType() const;

  Timestamp GetTimestamp() const;

 private:
  Type type_;

  Timestamp timestamp_;
};

bool operator==(const Record& lhs, const Record& rhs);

bool operator!=(const Record& lhs, const Record& rhs);
