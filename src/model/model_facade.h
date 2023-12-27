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

  void TransformModel(std::string str, std::vector<double>& vertex, double k) {
    if (str == "move_x") {
      MoveX strategy;
      affine_strategy_.SetStrategy(&strategy);
    } else if (str == "move_y") {
      MoveY strategy;
      affine_strategy_.SetStrategy(&strategy);
    } else if (str == "move_z") {
      MoveZ strategy;
      affine_strategy_.SetStrategy(&strategy);
    } else if (str == "rotate_x") {
      RotateX strategy;
      affine_strategy_.SetStrategy(&strategy);
    } else if (str == "rotate_y") {
      RotateY strategy;
      affine_strategy_.SetStrategy(&strategy);
    } else if (str == "rotate_z") {
      RotateZ strategy;
      affine_strategy_.SetStrategy(&strategy);
    } else if (str == "scale") {
      Scale strategy;
      affine_strategy_.SetStrategy(&strategy);
    }
    affine_strategy_.Transform(vertex, k);
  }

 private:
  ObjParser& parser_ = ObjParser::SingleParser();
  Client affine_strategy_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_MODEL_FACADE_H_
