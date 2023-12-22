#include "record.h"

#include <ctime>

Record::Record(Record::Type type, const std::string& timestamp):
    type_{type},
    timestamp_{timestamp.empty() ? GetCurrentTimestamp() : timestamp}
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

std::string Record::GetCurrentTimestamp()
{
    const std::time_t current_time{std::time(nullptr)};
    char current_timestamp[std::size("yyyy-mm-dd hh:mm:ss")];
    std::strftime(std::data(current_timestamp), std::size(current_timestamp), "%F %T", localtime(&current_time));

    return std::string{current_timestamp};
}
