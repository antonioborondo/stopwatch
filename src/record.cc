#include "record.h"

#include <ostream>

Record::Record(Record::Type type, const Timestamp& timestamp):
    type_{type},
    timestamp_{timestamp}
{
}

Record::Type Record::GetType() const
{
    return type_;
}

Timestamp Record::GetTimestamp() const
{
    return timestamp_;
}

bool operator==(const Record& lhs, const Record& rhs)
{
    return (lhs.GetType() == rhs.GetType()) && (lhs.GetTimestamp() == rhs.GetTimestamp());
}

std::ostream& operator<<(std::ostream& os, const Record::Type& type)
{
    switch(type)
    {
        case Record::Type::kStop:
        {
            os << "Stop ";
            break;
        }
        default:
        {
            os << "Start";
            break;
        }
    }
    return os;
}
