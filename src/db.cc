#include "db.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// clang-format off
#include "fmt/format.h"
#include "sqlite3.h"
// clang-format on

#include "record.h"
#include "timestamp.h"
#include "type.h"

Db::Db() {
#ifdef NDEBUG
  std::filesystem::path data_directory{GetDataDirectory()};
  CreateDataDirectory(data_directory);
  std::filesystem::path database_file_path{GetDataDirectory() /=
                                           "time_tracker.db"};
#else
  std::filesystem::path database_file_path{"time_tracker.db"};
#endif
  sqlite3_open(database_file_path.c_str(), &db_);

  std::string sql{
      "CREATE TABLE IF NOT EXISTS records"
      "("
      "   type INTEGER NOT NULL,"
      "   timestamp TEXT PRIMARY KEY NOT NULL"
      ")"};

  sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, nullptr);
}

Db::~Db() { sqlite3_close(db_); }

std::string Db::Summary(const Timestamp& timestamp) {
  const auto last_record{GetLastRecord(timestamp)};
  if (last_record.GetType() == Type::kStart) {
    AddRecord(Record{Type::kStop, Timestamp::GetCurrent()});
  }

  const auto sql_format_string{R"(
        SELECT
            SUM(difference)
        FROM
        (
            SELECT
                julianday(stop_records.timestamp) -julianday(start_records.timestamp) AS difference
            FROM
            (
                SELECT
                    row_number() OVER(ORDER BY timestamp) AS row_number,
                    timestamp
                FROM
                    records
                WHERE
                    date(timestamp) = '{0}'
                    AND
                    type=1
            ) AS start_records,
            (
                SELECT
                    row_number() OVER(ORDER BY timestamp) AS row_number,
                    timestamp
                FROM
                    records
                WHERE
                    date(timestamp) = '{0}'
                    AND
                    type=0
            ) AS stop_records
            WHERE
                start_records.row_number=stop_records.row_number
        )
    )"};

  const auto sql{fmt::format(sql_format_string, timestamp.GetDate())};

  sqlite3_stmt* stmt{nullptr};

  int retval = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, 0);
  double result;

  int idx = 0;

  while (1) {
    retval = sqlite3_step(stmt);

    if (retval == SQLITE_ROW) {
      result = sqlite3_column_double(stmt, 0);
    } else if (retval == SQLITE_DONE) {
      break;
    } else {
      sqlite3_finalize(stmt);
      printf("Some error encountered\n");
      break;
    }
  }

  sqlite3_finalize(stmt);

  if (last_record.GetType() == Type::kStart) {
    DeleteLast();
  }

  return GetTime(result);
}

void Db::DeleteLast() {
  char* zErrMsg = 0;
  std::string sql{
      "DELETE FROM records WHERE timestamp = (SELECT MAX(timestamp) FROM "
      "records)"};

  int rc = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
}

bool Db::DeleteRecords() {
  const std::string sql{"DROP TABLE IF EXISTS records"};

  char* error_message{nullptr};
  const auto result{
      sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &error_message)};
  if (result != SQLITE_OK) {
    std::cerr << "SQL error: " << error_message << std::endl;
    sqlite3_free(error_message);

    return false;
  }

  return true;
}

bool Db::AddRecord(const Record& record) {
  const auto records{GetRecords(record.GetTimestamp())};
  if (!records.empty()) {
    if (records.back().GetType() == record.GetType()) {
      return false;
    }
  }

  const auto sql_format_string{
      "INSERT INTO records (type, timestamp) VALUES({0}, '{1}')"};
  const auto sql{fmt::format(sql_format_string,
                             std::to_string(static_cast<int>(record.GetType())),
                             record.GetTimestamp().Get())};

  char* error_message{nullptr};
  const auto result{
      sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &error_message)};
  if (result != SQLITE_OK) {
    std::cerr << "SQL error: " << error_message << std::endl;
    sqlite3_free(error_message);

    return false;
  }

  return true;
}

Record Db::GetLastRecord(const Timestamp& timestamp) {
  const std::string sql_format_string{R"(
        SELECT
            type,
            timestamp
        FROM
            records
        WHERE
            date(timestamp) = '{}'
        ORDER BY
            timestamp
            DESC
        LIMIT 1
    )"};

  const auto sql{fmt::format(sql_format_string, timestamp.GetDate())};

  sqlite3_stmt* stmt{nullptr};

  int retval = sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, 0);

  int type;
  std::string timestamp2;

  int idx = 0;

  while (1) {
    retval = sqlite3_step(stmt);

    if (retval == SQLITE_ROW) {
      type = sqlite3_column_int(stmt, 0);
      timestamp2 = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    } else if (retval == SQLITE_DONE) {
      break;
    } else {
      sqlite3_finalize(stmt);
      printf("Some error encountered\n");
      break;
    }
  }

  sqlite3_finalize(stmt);

  return Record{static_cast<Type>(type), Timestamp{timestamp2}};
}

std::vector<Record> Db::GetRecords(const Timestamp& timestamp) const {
  std::vector<Record> records;

  const std::string sql_format_string{R"(
        SELECT
            type,
            timestamp
        FROM
            records
        WHERE
            date(timestamp) = '{0}'
    )"};
  const auto sql{fmt::format(sql_format_string, timestamp.GetDate())};

  sqlite3_stmt* statement{nullptr};
  int result_code{
      sqlite3_prepare_v2(db_, sql.c_str(), -1, &statement, nullptr)};

  while (true) {
    result_code = sqlite3_step(statement);
    if (result_code == SQLITE_ROW) {
      const auto result_type{
          static_cast<Type>(sqlite3_column_int(statement, 0))};
      const auto result_timestamp{
          reinterpret_cast<const char*>(sqlite3_column_text(statement, 1))};
      records.emplace_back(result_type, Timestamp{result_timestamp});
    } else if (result_code == SQLITE_DONE) {
      break;
    } else {
      sqlite3_finalize(statement);
      printf("Some error encountered\n");
      break;
    }
  }

  sqlite3_finalize(statement);

  return records;
}

std::string Db::GetTime(double time_in_days) {
  double hours{time_in_days * 24};

  double minutes_in_hours{hours - static_cast<int>(hours)};
  double minutes{minutes_in_hours * 60};

  double seconds_in_minutes{minutes - static_cast<int>(minutes)};
  double seconds{seconds_in_minutes * 60};

  return fmt::format("{0:02}:{1:02}:{2:02}", static_cast<int>(hours),
                     static_cast<int>(minutes), static_cast<int>(seconds));
}

std::filesystem::path Db::GetDataDirectory() {
  std::filesystem::path data_directory;

  const auto xdg_data_home_directory{std::getenv("XDG_DATA_HOME")};
  if (xdg_data_home_directory && strlen(xdg_data_home_directory) != 0) {
    data_directory = xdg_data_home_directory;
  } else {
    data_directory = std::getenv("HOME");
    data_directory /= ".local/share";
  }

  data_directory /= "time_tracker";

  return data_directory;
}

void Db::CreateDataDirectory(const std::filesystem::path& data_directory) {
  std::filesystem::create_directories(data_directory);
}
