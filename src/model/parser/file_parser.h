#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <set>
#include <string>
#include <vector>

namespace s21 {
enum Status { kOk, kError };

class ObjParser {
 public:
  ObjParser() = default;
  ~ObjParser() = default;

  Status ParseFile(const std::string& file_name);
  Status ParseLine(const std::string& line);
  Status ParseVertex(const std::string& data);
  Status ParseFace(const std::string& data);

 private:
  std::vector<double> verteces_;
  std::size_t verteces_count_ = 0;
  std::vector<unsigned int> faces_;
  std::size_t faces_count_ = 0;

  std::set<std::pair<unsigned int, unsigned int>> faces_set_;
};
// struct ObjData {
//   std::size_t number_of_vertices = 0;
//   std::vector<double> vertices;
//   std::size_t number_of_faces = 0;
//   std::vector<double> faces;
// };

// class FileParser {
// public:
//   FileParser(/* args */);
//   ~FileParser();

// private:
//   ObjData data_;
// };
}  // namespace s21
#endif  // FILE_PARSER_H_