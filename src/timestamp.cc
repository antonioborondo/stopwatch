#include "timestamp.h"

#include <ctime>
#include <ostream>
#include <regex>
#include <string>

Timestamp::Timestamp(const std::string& timestamp):
    timestamp_{timestamp}
{
    if(!IsValid())
    {
        throw std::invalid_argument("Invalid timestamp");
    }
}

std::string Timestamp::Get() const
{
    return timestamp_;
}

std::string Timestamp::GetDate() const
{
    const std::regex regex{R"((\d{4}-\d{2}-\d{2}) \d{2}:\d{2}:\d{2})"};
    std::smatch regex_match_result;
    if(!std::regex_match(timestamp_, regex_match_result, regex))
    {
        throw std::runtime_error("Cannot get date");
    }
    return regex_match_result[1];
}

std::string Timestamp::GetTime() const
{
    const std::regex regex{R"(\d{4}-\d{2}-\d{2} (\d{2}:\d{2}:\d{2}))"};
    std::smatch regex_match_result;
    if(!std::regex_match(timestamp_, regex_match_result, regex))
    {
        throw std::runtime_error("Cannot get time");
    }
    return regex_match_result[1];
}

Timestamp Timestamp::GetCurrent()
{
    const std::time_t time{std::time(nullptr)};
    const size_t timestamp_size{32};
    char timestamp[timestamp_size];
    if(std::strftime(timestamp, timestamp_size, "%F %T", localtime(&time)) == 0)
    {
        throw std::runtime_error("Cannot get current");
    }
    return Timestamp(timestamp);
}

bool Timestamp::IsValid() const
{
    const std::regex regex{R"(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})"};
    std::smatch regex_match_result;
    return std::regex_match(timestamp_, regex_match_result, regex);
}

bool operator==(const Timestamp& lhs, const Timestamp& rhs)
{
    return (lhs.Get() == rhs.Get());
}

bool operator!=(const Timestamp& lhs, const Timestamp& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Timestamp& timestamp)
{
    os << timestamp.Get();
    return os;
}
