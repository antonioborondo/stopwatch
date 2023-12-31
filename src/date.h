#pragma once

#include <fmt/ostream.h>

#include <ostream>
#include <string>

class Date
{
public:
    Date(const std::string& date_string);

    static Date GetCurrent();

private:
    bool IsValid() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    std::string date_string_;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

template<>
struct fmt::formatter<Date>: ostream_formatter
{};
