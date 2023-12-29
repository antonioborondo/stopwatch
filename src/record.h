#pragma once

#include "timestamp.h"

#include <string>

class Record
{
public:
    enum class Type
    {
        kStop = 0,
        kStart,
    };

    Record(Type type, const std::string& timestamp = timestamp::GetCurrentDateAndTime());

    Type GetType() const;

    std::string GetTimestamp() const;

private:
    Type type_;

    std::string timestamp_;
};

bool operator==(const Record& lhs, const Record& rhs);
