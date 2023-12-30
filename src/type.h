#pragma once

#include <ostream>

enum class Type
{
    kStop = 0,
    kStart,
};

std::ostream& operator<<(std::ostream& os, const Type& type);
