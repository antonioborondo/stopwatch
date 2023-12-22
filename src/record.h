#pragma once

#include <string>

class Record
{
public:
    enum class Type
    {
        kStop = 0,
        kStart,
    };

    Record(Type type, const std::string& timestamp = "");

    Type GetType() const;

    std::string GetTimestamp() const;

private:
    std::string GetCurrentTimestamp();

    Type type_;

    std::string timestamp_;
};
