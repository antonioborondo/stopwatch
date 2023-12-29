#include "db.h"
#include "record.h"

#include <boost/program_options.hpp>

#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    try
    {
        po::options_description options_description;
        // clang-format off
        options_description.add_options()
        ("start", "start time tracker")
        ("stop", "stop time tracker")
        ("summary", "display time tracker summary")
        ("help", "display this help and exit")
        ("version", "output version information and exit")
        ;
        // clang-format on

        po::variables_map variables_map;
        po::store(po::parse_command_line(argc, argv, options_description), variables_map);

        Db db;
        if(variables_map.count("start"))
        {
            const Record record{Record::Type::kStart, Timestamp::GetCurrent()};
            db.AddRecord(record);
            std::cout << record.GetTimestamp().Get() << std::endl;
        }
        else if(variables_map.count("stop"))
        {
            const Record record{Record::Type::kStop, Timestamp::GetCurrent()};
            db.AddRecord(record);
            std::cout << record.GetTimestamp().Get() << std::endl;
        }
        else if(variables_map.count("summary"))
        {
            std::cout << "+-------+---------------------+\n";
            std::cout << "| Type  | Timestamp           |\n";
            std::cout << "+-------+---------------------+\n";
            auto records{db.GetRecords()};
            for(const auto& record: records)
            {
                std::cout << "| " << record.GetType() << " | " << record.GetTimestamp().Get() << " |\n";
            }
            std::cout << "+-------+---------------------+\n";

            std::cout << "\nTotal time: " << db.Summary(Timestamp::GetCurrent()) << "\n";
        }
        else if(variables_map.count("version"))
        {
            std::cout << "time_tracker 1.0.0" << std::endl;
        }
        else
        {
            std::cout << "Usage: time_tracker [OPTION]" << std::endl;
            std::cout << options_description << std::endl;
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;

        return 1;
    }

    return 0;
}
