#include "timestamp.h"

#include <ctime>
#include <regex>

namespace
{
std::string GetCurrentTimestamp(const std::string& format)
{
    const std::time_t time{std::time(nullptr)};
    const size_t timestamp_size{32};
    char timestamp[timestamp_size];
    std::strftime(std::data(timestamp), std::size(timestamp), format.c_str(), localtime(&time));

    return std::string{timestamp};
}
}

namespace timestamp
{
std::string GetCurrentDate()
{
    return GetCurrentTimestamp("%F"); // yyyy-mm-dd
}

std::string GetCurrentDateAndTime()
{
    return GetCurrentTimestamp("%F %T"); // yyyy-mm-dd hh:mm:ss
}

std::string GetDate(const std::string& timestamp)
{
    const std::regex regex{R"((\d{4}-\d{2}-\d{2}) (\d{2}:\d{2}))"};
    std::smatch regex_match_result;
    std::regex_search(timestamp, regex_match_result, regex);
    return regex_match_result[1];
}
}
