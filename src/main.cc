#include "db.h"

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

        if(variables_map.count("start"))
        {
            std::cout << "Start time tracker" << std::endl;
            Db db;
            db.Log(Db::LogType::kIn);
        }
        else if(variables_map.count("stop"))
        {
            std::cout << "Stop time tracker" << std::endl;
            Db db;
            db.Log(Db::LogType::kOut);
        }
        else if(variables_map.count("summary"))
        {
            std::cout << "Time tracker summary:" << std::endl;
            Db db;
            std::cout << db.Summary() << " hours" << std::endl;
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
