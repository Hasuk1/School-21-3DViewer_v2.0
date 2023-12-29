#ifndef CPP4_3DVIEWER_V2_SRC_TRANSFORM_H_
#define CPP4_3DVIEWER_V2_SRC_TRANSFORM_H_

#include <vector>

namespace s21 {
enum Mode {
  kMoveX,
  kMoveY,
  kMoveZ,
  kRotateX,
  kRotateY,
  kRotateZ,
  kScale,
  kDefault
};

class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual void TransformModel(std::vector<double> &vertex, const unsigned start,
                              const unsigned end, const double k) = 0;
};

class MoveX : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class MoveY : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class MoveZ : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class RotateX : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class RotateY : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class RotateZ : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class Scale : public Strategy {
 public:
  void TransformModel(std::vector<double> &vertex, const unsigned start,
                      const unsigned end, const double k);
};

class Context {
 protected:
  Strategy *operation;

 public:
  virtual ~Context() = default;
  virtual void Transform(std::vector<double> &vertex, const double k) = 0;
  virtual void SetStrategy(Strategy *o) = 0;
};

class Client : public Context {
 public:
  void SetStrategy(Strategy *v);
  void Transform(std::vector<double> &vertex, const double k);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_SRC_TRANSFORM_H_
