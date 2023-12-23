#include "time_utils.h"

#include <ctime>

namespace
{
std::string GetCurrentTimestampWithFormat(const std::string& format)
{
    const std::time_t time{std::time(nullptr)};
    const size_t buffer_size{32};
    char buffer[buffer_size];
    std::strftime(std::data(buffer), std::size(buffer), format.c_str(), localtime(&time));

    return std::string{buffer};
}
}

namespace time_utils
{
std::string GetCurrentDate()
{
    return GetCurrentTimestampWithFormat("%F"); // yyyy-mm-dd
}

std::string GetCurrentTimestamp()
{
    return GetCurrentTimestampWithFormat("%F %T"); // yyyy-mm-dd hh:mm:ss
}
}
