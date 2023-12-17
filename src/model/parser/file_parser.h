#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include "obj_data.h"

namespace s21 {
  struct ObjData {
    unsigned long number_of_vertices = 0;
    std::vector<double> vertices;
    unsigned long number_of_faces = 0;
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