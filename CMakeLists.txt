cmake_minimum_required(VERSION 3.27.7)

project(stopwatch VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS program_options REQUIRED)
find_package(SQLite3 REQUIRED)

add_executable(sw
    src/db.cc
    src/main.cc
)

target_link_libraries(sw
    PRIVATE
    Boost::program_options
    SQLite::SQLite3
)
