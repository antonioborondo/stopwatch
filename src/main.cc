// clang-format off
#include <boost/program_options.hpp>
#include <sqlite3.h>
// clang-format on

#include <iostream>

namespace po = boost::program_options;

void db()
{
    sqlite3* db;
    sqlite3_open("sw.db", &db);
    sqlite3_close(db);
}

int main(int argc, char** argv)
{
    try
    {
        po::options_description options_description;
        // clang-format off
        options_description.add_options()
        ("login,i", "record login timestamp")
        ("logout,o", "record logout timestamp")
        ("summary,s", "display summary")
        ("help", "display this help and exit")
        ("version", "output version information and exit")
        ;
        // clang-format on

        po::variables_map variables_map;
        po::store(po::parse_command_line(argc, argv, options_description), variables_map);

        if(variables_map.count("login"))
        {
            std::cout << "Login" << std::endl;
        }
        else if(variables_map.count("logout"))
        {
            std::cout << "Logout" << std::endl;
        }
        else if(variables_map.count("summary"))
        {
            std::cout << "Summary" << std::endl;
        }
        else if(variables_map.count("version"))
        {
            std::cout << "1.0.0" << std::endl;
        }
        else
        {
            std::cout << "Usage: sw [OPTION]" << std::endl;
            std::cout << options_description << std::endl;
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;

        return 1;
    }

    db();

    return 0;
}
