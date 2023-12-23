#include "file_parser.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
Status ObjParser::ParseFile(const std::string& file_name) {
  ClearData();
  std::ifstream file(file_name);
  if (!file.is_open()) return kErrorFileMissing;
  std::string current_line;
  Status status = kOk;
  while (std::getline(file, current_line) && status == kOk) {
    status = ParseLine(current_line);
  }
  if (status == kOk)
    TransferUniqueVector();
  else
    ClearData();
  file.close();
  return verteces_.empty() || edges_.empty() ? kErrorFileEmpty : status;
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
    try {
      index = std::stoi(index_str);
    } catch (const std::out_of_range& e) {
      return kErrorFileMissing;
    }
    if (index > static_cast<long>(verteces_.size())) return kErrorFileMissing;
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

void ObjParser::ClearData() {
  verteces_.clear();
  edges_.clear();
  verteces_count_ = edges_count_ = 0;
}
}  // namespace s21
