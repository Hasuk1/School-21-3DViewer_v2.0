#ifndef CPP4_3DVIEWER_V2_SRC_3D_VIEWER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_SRC_3D_VIEWER_CONTROLLER_H_

#include <string>
#include <vector>

#include "./../model/model_facade.h"

namespace s21 {
class ObjController {
 public:
  static ObjController& SinlgeObjController() {
    static ObjController TheObjController;
    return TheObjController;
  }

  Status ParseObjFile(const std::string& file_name) {
    return facade_.ParseFile(file_name);
  }

  void ClearObjData() { facade_.ClearData(); }

  std::vector<double> GetObjVertex() { return facade_.GetVertex(); }

  std::vector<unsigned> GetObjEdges() { return facade_.GetEdges(); }

  float GetObjNormalizeCoef() { return facade_.GetNormalizeCoef(); }

  void TransformModel(Mode mode, std::vector<double>& vertex, double k) {
    facade_.TransformModel(mode, vertex, k);
  }

 private:
  ObjController() = default;
  ~ObjController() = default;
  ObjFacade facade_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_3D_VIEWER_CONTROLLER_H_
