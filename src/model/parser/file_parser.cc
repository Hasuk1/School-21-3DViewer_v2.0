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
    return kErrorFileMissing;
  }
  std::string current_line;
  Status status = kOk;
  while (std::getline(file, current_line)) {
    status = ParseLine(current_line);
    if (status == kErrorIncorrectFile) break;
  }
  TransferUniqueVector();
  file.close();

  Print();
  return status;
}

Status ObjParser::ParseLine(const std::string& line) {
  Status status = kOk;
  if (line.length() > 7) {
    char type = line[0];
    std::string data = line.substr(2);
    if (type == 'v')
      status = ParseVertex(data);
    else if (type == 'f')
      status = ParseFace(data);
  }
  return status;
}

Status ObjParser::ParseVertex(const std::string& data) {
  std::istringstream iss(data);
  double value;
  while (iss >> value) verteces_.push_back(value);

  if (verteces_.size() % 3 == 0)
    ++verteces_count_;
  else
    return kErrorIncorrectFile;

  return kOk;
}

Status ObjParser::ParseFace(const std::string& data) {
  std::istringstream iss(data);
  long index, first_index;
  bool is_first_index = true;
  std::vector<unsigned int> faces_buff;
  while (iss >> index) {
    if (index < 0)
      index += verteces_count_;
    else
      index -= 1;

    if (is_first_index) {
      first_index = index;
      faces_buff.push_back(index);
      is_first_index = false;
    } else {
      faces_buff.push_back(index);
      faces_buff.push_back(index);
    }
  }
  faces_buff.push_back(first_index);
  InsertUniqueVector(faces_buff);
  return kOk;
}

void ObjParser::InsertUniqueVector(const std::vector<unsigned int>& data) {
  for (auto it = data.begin(); it != data.end() && data.size() % 2 == 0;
       it += 2) {
    unsigned int first = *it, second = *(it + 1);
    std::pair<unsigned int, unsigned int> vector(first, second);
    std::pair<unsigned int, unsigned int> inverse_vector(second, first);
    if (vectors_set_.find(vector) == vectors_set_.end() &&
        vectors_set_.find(inverse_vector) == vectors_set_.end()) {
      vectors_set_.insert(vector);
      edges_count_++;
    }
  }
}

void ObjParser::TransferUniqueVector() {
  for (const auto& pair : vectors_set_) {
    edges_.push_back(pair.first);
    edges_.push_back(pair.second);
  }
  vectors_set_.clear();
}

void ObjParser::Print() {
  for (const auto& coord : verteces_) {
    std::cout << "v " << coord << ", ";
  }
  std::cout << "\n";
  std::cout << "verteces_count_ = " << verteces_count_ << "\n\n";
  for (const auto& indx : edges_) {
    std::cout << "f " << indx << ", ";
  }
  std::cout << "\n";
  std::cout << "edges_count_ = " << edges_count_ << "\n";
}
}  // namespace s21