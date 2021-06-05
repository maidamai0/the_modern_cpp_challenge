#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <string_view>

#include "doctest/doctest.h"
#include "fmt/format.h"
#include "utility.hpp"

class TempLog {
 public:
  TempLog() {
    path_ = std::filesystem::temp_directory_path() / "temporary_log.txt";
    log_.open(path_);
  };
  void MoveTo(const std::string& new_path) {
    log_.close();
    std::filesystem::rename(path_, new_path);
    path_ = std::filesystem::path(new_path);
    log_.open(path_, std::ios_base::app);
  }

  template <typename T>
  friend TempLog& operator<<(TempLog& log, T&& type) {
    log.log_ << type;
    return log;
  }

  void Print() {
    log_.flush();
    std::ifstream f(path_);
    for (std::string line; std::getline(f, line);) {
      fmt::print(line + '\n');
    }
  }

 private:
  std::filesystem::path path_;
  std::ofstream log_;
};

TEST_CASE(util::problem_name().data()) {
  TempLog log;
  log << "this is temporary log" << '\n';
  log << "integer " << 1 << '\n';
  log << "std::string " << std::string("string\n");
  log << "std::string_view " << std::string_view("string_view\n");

  log.Print();
  log.MoveTo("persistent.txt");
  log << "after move\n";
  log.Print();
}