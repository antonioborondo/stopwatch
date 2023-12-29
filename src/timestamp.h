#pragma once

#include <string>

namespace timestamp
{
std::string GetCurrentDate();
std::string GetCurrentDateAndTime();
std::string GetDate(const std::string& timestamp);
}
