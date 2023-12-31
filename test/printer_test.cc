#include "printer.h"
#include "record.h"

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

class PrinterTest: public testing::Test
{
protected:
    std::ostringstream sink_;

    Printer printer_;

    PrinterTest():
        printer_{sink_}
    {
    }

    void SetUp() override
    {
        sink_.str("");
        sink_.clear();
    }
};

TEST_F(PrinterTest, PrintNoRecords)
{
    const std::vector<Record> records;

    printer_.PrintRecords(records);

    const std::string expected_print{
        "+-------+---------------------+\n"
        "| Type  | Timestamp           |\n"
        "+-------+---------------------+\n"
        "+-------+---------------------+\n"};
    ASSERT_EQ(expected_print, sink_.str());
}

TEST_F(PrinterTest, PrintMultipleRecords)
{
    std::vector<Record> records;
    records.emplace_back(Type::kStart, Timestamp{"0001-01-01 01:01:01"});
    records.emplace_back(Type::kStop, Timestamp{"0001-01-01 01:01:02"});

    printer_.PrintRecords(records);

    const std::string expected_print{
        "+-------+---------------------+\n"
        "| Type  | Timestamp           |\n"
        "+-------+---------------------+\n"
        "| Start | 0001-01-01 01:01:01 |\n"
        "| Stop  | 0001-01-01 01:01:02 |\n"
        "+-------+---------------------+\n"};
    ASSERT_EQ(expected_print, sink_.str());
}
