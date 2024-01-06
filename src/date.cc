#include "date.h"

#include <ctime>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>

Date::Date(const std::string& date_string):
    date_string_{date_string}
{
    if(!IsValid())
    {
        throw std::invalid_argument("Invalid date");
    }
}

Date Date::GetCurrent()
{
    const std::time_t time{std::time(nullptr)};
    const size_t date_size{16};
    char date_string[date_size];
    if(std::strftime(date_string, date_size, "%F", localtime(&time)) == 0)
    {
        throw std::runtime_error("Cannot get current");
    }
    return Date(date_string);
}

bool Date::IsValid() const
{
    const std::regex regex{R"(\d{4}-\d{2}-\d{2})"};
    std::smatch regex_match_result;
    return std::regex_match(date_string_, regex_match_result, regex);
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << date.date_string_;
    return os;
}
