#include "timestamp.h"

#include <ctime>

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

namespace time_utils
{
std::string GetCurrentDate()
{
    return GetCurrentTimestamp("%F"); // yyyy-mm-dd
}

std::string GetCurrentDateAndTime()
{
    return GetCurrentTimestamp("%F %T"); // yyyy-mm-dd hh:mm:ss
}
}
