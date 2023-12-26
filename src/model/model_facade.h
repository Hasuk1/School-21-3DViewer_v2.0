#ifndef CPP4_3DVIEWER_V2_SRC_MODEL_FACADE_H_
#define CPP4_3DVIEWER_V2_SRC_MODEL_FACADE_H_

#include <string>
#include <vector>

#include "./parser/file_parser.h"
#include "./transform/transform.h"

namespace s21 {
class ObjFacade {
 public:
  ObjFacade() = default;
  ~ObjFacade() = default;

  Status ParseFile(const std::string& file_name) {
    return parser_.ParseFile(file_name);
  }

  void ClearData() { parser_.ClearData(); }

  std::vector<double> GetVertex() { return parser_.GetVertex(); }

  std::vector<unsigned> GetEdges() { return parser_.GetEdges(); }

  float GetNormalizeCoef() { return parser_.GetNormalizeCoef(); }

 private:
  ObjParser& parser_ = ObjParser::SingleParser();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_FACADE_H_
