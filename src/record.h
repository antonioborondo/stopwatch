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

    Record(Type type, const Timestamp& timestamp);

    Type GetType() const;

    Timestamp GetTimestamp() const;

private:
    Type type_;

    Timestamp timestamp_;
};

bool operator==(const Record& lhs, const Record& rhs);

std::ostream& operator<<(std::ostream& os, const Record::Type& type);
