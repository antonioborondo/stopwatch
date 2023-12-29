#pragma once

#include <string>

class Timestamp
{
public:
    Timestamp(const std::string& timestamp);

    std::string Get() const;

    std::string GetDate() const;

    std::string GetTime() const;

    static Timestamp GetCurrent();

private:
    bool IsValid() const;

    std::string timestamp_;
};

namespace timestamp
{
std::string GetCurrentDate();
std::string GetCurrentDateAndTime();
std::string GetDate(const std::string& timestamp);
}
