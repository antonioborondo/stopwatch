#include "printer.h"

#include "record.h"
#include "timestamp.h"
#include "type.h"

#include <fmt/format.h>

Printer::Printer(std::ostream& sink):
    sink_{sink}
{
}

void Printer::PrintRecords(const std::vector<Record>& records) const
{
    sink_ << "+-------+---------------------+\n";
    sink_ << "| Type  | Timestamp           |\n";
    sink_ << "+-------+---------------------+\n";

    for(const auto& record: records)
    {
        sink_ << fmt::format("| {:<5} | {:<19} |\n", record.GetType(), record.GetTimestamp());
    }

    sink_ << "+-------+---------------------+\n";
}
