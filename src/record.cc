#include "record.h"

Record::Record(Record::Type type, const std::string& timestamp):
    type_{type},
    timestamp_{timestamp}
{
}

Record::Type Record::GetType() const
{
    return type_;
}

std::string Record::GetTimestamp() const
{
    return timestamp_;
}

bool operator==(const Record& lhs, const Record& rhs)
{
    return (lhs.GetType() == rhs.GetType()) && (lhs.GetTimestamp() == rhs.GetTimestamp());
}
