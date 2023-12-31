#pragma once

#include "record.h"

#include <iostream>
#include <ostream>
#include <vector>

class Printer
{
    std::ostream& sink_;

public:
    Printer(std::ostream& sink = std::cout);

    void PrintRecords(const std::vector<Record>& records);
};
