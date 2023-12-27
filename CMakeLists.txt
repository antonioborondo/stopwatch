cmake_minimum_required(VERSION 3.28.1)

project(time_tracker VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

add_library(time_tracker_common STATIC
    src/db.cc
    src/record.cc
    src/timestamp.cc
)

target_include_directories(time_tracker_common
    PUBLIC
    src
)

find_package(fmt REQUIRED)
find_package(SQLite3 REQUIRED)

target_link_libraries(time_tracker_common
    PRIVATE
    fmt::fmt
    SQLite::SQLite3
)

add_executable(time_tracker
    src/main.cc
)

find_package(Boost COMPONENTS program_options REQUIRED)

target_link_libraries(time_tracker
    PRIVATE
    Boost::program_options
    time_tracker_common
)

add_executable(time_tracker_test
    test/db_test.cc
)

find_package(GTest REQUIRED)

target_link_libraries(time_tracker_test
    PRIVATE
    GTest::gtest_main
    time_tracker_common
)

enable_testing()

add_test(NAME time_tracker_test COMMAND time_tracker_test)

install(TARGETS time_tracker DESTINATION bin)

include(CPack)
