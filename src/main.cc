// clang-format off
#include <boost/program_options.hpp>
#include <sqlite3.h>
// clang-format on

#include <iostream>
#include <string>

namespace po = boost::program_options;

class Db
{
    sqlite3* db_;

public:
    Db()
    {
        sqlite3_open("sw.db", &db_);

        std::string sql{"CREATE TABLE IF NOT EXISTS log (timestamp TEXT PRIMARY KEY NOT NULL, type INTEGER NOT NULL)"};
        sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
    }

    ~Db()
    {
        sqlite3_close(db_);
    }

    void login()
    {
        std::string sql{"INSERT INTO log (timestamp, type) VALUES(datetime(CURRENT_TIMESTAMP, 'localtime'), 1)"};
        sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
    }

    void logout()
    {
        std::string sql{"INSERT INTO log (timestamp, type) VALUES(datetime(CURRENT_TIMESTAMP, 'localtime'), 0)"};
        sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
    }
};

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
            Db db;
            db.login();
        }
        else if(variables_map.count("logout"))
        {
            std::cout << "Logout" << std::endl;
            Db db;
            db.logout();
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

    return 0;
}
