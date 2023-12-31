#include "printer.h"

#include <gtest/gtest.h>

#include <sstream>

TEST(PrinterTest, PrintNoRecords)
{
    std::ostringstream sink;
    const Printer printer{sink};

    const std::vector<Record> records;

    printer.PrintRecords(records);

    const std::string expected_print{
        "+-------+---------------------+\n"
        "| Type  | Timestamp           |\n"
        "+-------+---------------------+\n"
        "+-------+---------------------+\n"};

    ASSERT_EQ(expected_print, sink.str());
}
