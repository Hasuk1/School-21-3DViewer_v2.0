#include "file_parser.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
Status ObjParser::ParseFile(const std::string& file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Unable to open file: " << file_name << "\n";
    return kError;
  }

  std::string current_line;
  Status status = kOk;
  while (std::getline(file, current_line) && status == kOk) {
    status = ParseLine(current_line);
  }

  file.close();
  return status;
}

Status ObjParser::ParseLine(const std::string& line) {
  if (line.empty()) return kOk;
  Status status = kOk;
  char type = line[0];
  std::string data = line.substr(2);
  if (type == 'v') {
    status = ParseVertex(data);
  } else if (type == 'f') {
    status = ParseFace(data);
  }
  return status;
}

Status ObjParser::ParseVertex(const std::string& data) {
  std::istringstream iss(data);
  double xyz[3];
  if (iss >> xyz[0] >> xyz[1] >> xyz[2]) {
    for (int i = 0; i < 3; ++i) verteces_.push_back(xyz[i]);
    verteces_count_++;
  } else {
    std::cerr << "Error parsing vertex data\n";
    return kError;
  }
  return kOk;
}

Status ObjParser::ParseFace(const std::string& data) {
  if (data == "1") return kError;
  return kOk;
}

}  // namespace s21