#include "printer.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(PrinterTest, PrintNoRecords)
{
    std::ostringstream sink;
    Printer printer{sink};

    std::vector<Record> records;

    printer.PrintRecords(records);

    ASSERT_EQ("+-------+---------------------+\n| Type  | Timestamp           |\n+-------+---------------------+\n+-------+---------------------+\n", sink.str());
}
