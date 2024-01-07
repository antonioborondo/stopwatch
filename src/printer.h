#pragma once

#include <iostream>
#include <ostream>
#include <vector>

#include "record.h"

class Printer {
  std::ostream& sink_;

 public:
  Printer(std::ostream& sink = std::cout);

  void PrintRecords(const std::vector<Record>& records) const;
};
