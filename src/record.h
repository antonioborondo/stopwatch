#pragma once

#include "timestamp.h"

#include <ostream>

class Record
{
public:
    enum class Type
    {
        kStop = 0,
        kStart,
    };

    Record(Type type, const Timestamp& timestamp = Timestamp::GetCurrent());

    Type GetType() const;

    Timestamp GetTimestamp() const;

private:
    Type type_;

    Timestamp timestamp_;
};

bool operator==(const Record& lhs, const Record& rhs);

bool operator!=(const Record& lhs, const Record& rhs);
