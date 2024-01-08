# time_tracker

[![CI](https://github.com/antonioborondo/time_tracker/actions/workflows/ci.yml/badge.svg)](https://github.com/antonioborondo/time_tracker/actions/workflows/ci.yml)

## Description

Tool to track time and display the total time tracked.

### Example

```
$ time_tracker --start
2023-10-23 09:00:00

$ time_tracker --stop
2023-10-23 09:30:00

$ time_tracker --start
2023-10-23 10:00:00

$ time_tracker --stop
2023-10-23 10:30:00

$ time_tracker --summary
+-------+---------------------+
| Type  | Timestamp           |
+-------+---------------------+
| Start | 2023-10-23 09:00:00 |
| Stop  | 2023-10-23 09:30:00 |
| Start | 2023-10-23 10:00:00 |
| Stop  | 2023-10-23 10:30:00 |
+-------+---------------------+

Total time: 01:00:00

```

## Libraries

- Boost: https://boost.org
- fmt: https://github.com/fmtlib/fmt
- GoogleTest: https://github.com/google/googletest
- SQLite: https://sqlite.org

## Tools

- CMake: https://cmake.org
- Conan: https://conan.io
- GitHub Actions: https://github.com/features/actions
