#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <vector>

namespace s21 {
  struct ObjData {
    std::size_t number_of_vertices = 0;
    std::vector<double> vertices;
    std::size_t number_of_faces = 0;
    std::vector<double> faces;
  };

  class FileParser {
  public:
    FileParser(/* args */);
    ~FileParser();

  private:
    ObjData data_;
  };
}
#endif //FILE_PARSER_H_