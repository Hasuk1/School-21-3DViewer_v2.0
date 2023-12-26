#ifndef CPP4_3DVIEWER_V2_SRC_FILE_PARSER_H_
#define CPP4_3DVIEWER_V2_SRC_FILE_PARSER_H_

#include <set>
#include <string>
#include <vector>

namespace s21 {
enum Status { kOk, kErrorFileMissing, kErrorIncorrectFile, kErrorFileEmpty };

class ObjParser {
 public:
  static ObjParser& SingleParser();
  Status ParseFile(const std::string& file_name);
  void ClearData();
  std::vector<double> GetVertex();
  std::vector<unsigned> GetEdges();

 private:
  ObjParser() = default;
  ~ObjParser() = default;
  Status ParseLine(const std::string& line);
  Status ParseVertex(const std::string& data);
  Status ParseFace(const std::string& data);
  void InsertUniqueVector(const std::vector<unsigned>& data);
  void TransferUniqueVector();

  std::vector<double> verteces_;
  std::vector<unsigned> edges_;
  std::size_t verteces_count_ = 0;
  std::set<std::pair<unsigned, unsigned>> vectors_set_;
};

}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_SRC_FILE_PARSER_H_