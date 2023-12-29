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

bool operator==(const Timestamp& lhs, const Timestamp& rhs);

bool operator!=(const Timestamp& lhs, const Timestamp& rhs);
