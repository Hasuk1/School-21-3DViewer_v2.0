#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include <string>

#include "file_parser.h"

namespace s21 {
  void ObjVertex::Parse(const std::string& data){
    std::istringstream iss(data);
    char type;
    double xyz[3];
    iss >> type >> xyz[0] >> xyz[1] >> xyz[2];
    for (int i = 0; i < 3; ++i)
      vertex_.push_back(xyz[i]);
    
  }
}  // namespace s21