#include "record.h"

#include "timestamp.h"
#include "type.h"

Record::Record(Type type, const Timestamp& timestamp)
    : type_{type}, timestamp_{timestamp} {}

Type Record::GetType() const { return type_; }

Timestamp Record::GetTimestamp() const { return timestamp_; }

bool operator==(const Record& lhs, const Record& rhs) {
  return (lhs.GetType() == rhs.GetType()) &&
         (lhs.GetTimestamp() == rhs.GetTimestamp());
}

bool operator!=(const Record& lhs, const Record& rhs) { return !(lhs == rhs); }
