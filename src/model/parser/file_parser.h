#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <vector>

namespace s21 {
class ObjComponents {
public:
  virtual void Parse(const std::string& data) = 0;
  virtual ~ObjComponents() = default;
};

class ObjVertex : public ObjComponents{
  public:
    void Parse(const std::string& data) override;
  private:
    std::vector<double> vertex_;
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