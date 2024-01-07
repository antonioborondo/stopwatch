#include "printer.h"

#include <ostream>
#include <vector>

// clang-format off
#include "fmt/format.h"
// clang-format on

#include "record.h"

Printer::Printer(std::ostream& sink) : sink_{sink} {}

void Printer::PrintRecords(const std::vector<Record>& records) const {
  sink_ << "+-------+---------------------+\n";
  sink_ << "| Type  | Timestamp           |\n";
  sink_ << "+-------+---------------------+\n";

  for (const auto& record : records) {
    sink_ << fmt::format("| {:<5} | {:<19} |\n", record.GetType(),
                         record.GetTimestamp());
  }

  sink_ << "+-------+---------------------+\n";
}
