#include "timestamp.h"

#include <ctime>
#include <regex>

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
    std::regex_match(timestamp_, regex_match_result, regex);
    return regex_match_result[1];
}

std::string Timestamp::GetTime() const
{
    const std::regex regex{R"(\d{4}-\d{2}-\d{2} (\d{2}:\d{2}:\d{2}))"};
    std::smatch regex_match_result;
    std::regex_match(timestamp_, regex_match_result, regex);
    return regex_match_result[1];
}

Timestamp Timestamp::GetCurrent()
{
    const std::time_t time{std::time(nullptr)};
    const size_t timestamp_size{32};
    char timestamp[timestamp_size];
    std::strftime(std::data(timestamp), std::size(timestamp), "%F %T", localtime(&time));

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
