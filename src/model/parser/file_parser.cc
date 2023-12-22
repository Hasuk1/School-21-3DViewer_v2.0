#include "file_parser.h"

#include <clocale>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
Status ObjParser::ParseFile(const std::string& file_name) {
  std::setlocale(LC_ALL, "en_US.UTF-8");
  ClearData();
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
  if (status == kOk) TransferUniqueVector();
    else ClearData();
  file.close();
  Print();
  return status;
}

Status ObjParser::ParseLine(const std::string& line) {
  Status status = kOk;
  if (line.length() > 2) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if (type == "v") {
      std::string data = line.substr(2);
      status = ParseVertex(data);
    } else if (type == "f") {
      std::string data = line.substr(2);
      status = ParseFace(data);
    }
  }
  return status;
}

Status ObjParser::ParseVertex(const std::string& data) {
  std::istringstream iss(data);
  double x, y, z;
  if (iss >> x >> y >> z) {
    verteces_.push_back(x);
    verteces_.push_back(y);
    verteces_.push_back(z);
    ++verteces_count_;
  } else {
    ClearData();
    return kErrorIncorrectFile;
  }
  return kOk;
}

Status ObjParser::ParseFace(const std::string& data) {
  std::istringstream iss(data);
  std::string index_str;
  long index, first_index;
  bool is_first_index = true;
  std::vector<unsigned int> faces_buff;
  while (iss >> index_str) {
    index = std::stoi(index_str);
    if (index>verteces_.size()) return kErrorFileMissing;
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
  // edges_count_++;
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

void ObjParser::ClearData() {
  verteces_.clear();
  edges_.clear();
  verteces_count_ = edges_count_ = 0;
}

void ObjParser::Print() {
  // for (const auto& coord : verteces_) {
  //   std::cout << coord << "-> ";
  // }
  std::cout << "verteces_count_ = " << verteces_count_ << "\n";
  // for (const auto& indx : edges_) {
  //   std::cout << "f " << indx << ", ";
  // }
  // std::cout << "\n";
  std::cout << "edges_count_ = " << edges_count_ << "\n";

  /*verteces_count_ = 1000000
edges_count_ = 1669317*/
}
}  // namespace s21