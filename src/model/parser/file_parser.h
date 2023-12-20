#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <set>
#include <string>
#include <vector>

namespace s21 {
enum Status { kOk, kErrorFileMissing, kErrorIncorrectFile };

class ObjParser {
 public:
  ObjParser() = default;
  ~ObjParser() = default;

  Status ParseFile(const std::string& file_name);

  std::vector<double> GetVertex() { return verteces_; }
  std::vector<unsigned int> GetEdges() { return edges_; }

 private:
  void Print();

  Status ParseLine(const std::string& line);
  Status ParseVertex(const std::string& data);
  Status ParseFace(const std::string& data);
  void InsertUniqueVector(const std::vector<unsigned int>& data);
  void TransferUniqueVector();

  std::vector<double> verteces_;
  std::size_t verteces_count_ = 0;
  std::vector<unsigned int> edges_;
  std::size_t edges_count_ = 0;

  std::set<std::pair<unsigned int, unsigned int>> vectors_set_;
};

}  // namespace s21
#endif  // FILE_PARSER_H_