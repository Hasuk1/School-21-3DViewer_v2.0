#include "transform.h"

#include <cmath>

namespace s21 {
void MoveX::TransformModel(std::vector<double> &vertex, const double k) {
  for (size_t i = 0; i < vertex.size(); i += 3) vertex[i] += k;
}

void MoveY::TransformModel(std::vector<double> &vertex, const double k) {
  for (size_t i = 1; i < vertex.size(); i += 3) vertex[i] += k;
}

void MoveZ::TransformModel(std::vector<double> &vertex, const double k) {
  for (size_t i = 2; i < vertex.size(); i += 3) vertex[i] += k;
}

void RotateX::TransformModel(std::vector<double> &vertex, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    double y = vertex[i + 1];
    double z = vertex[i + 2];
    vertex[i + 1] = y * cos(angle) + z * sin(angle);
    vertex[i + 2] = -y * sin(angle) + z * cos(angle);
  }
}

void RotateY::TransformModel(std::vector<double> &vertex, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    double x = vertex[i];
    double z = vertex[i + 2];
    vertex[i] = x * cos(angle) + z * sin(angle);
    vertex[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void RotateZ::TransformModel(std::vector<double> &vertex, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    double x = vertex[i];
    double y = vertex[i + 1];
    vertex[i + 1] = x * cos(angle) + y * sin(angle);
    vertex[i + 2] = -x * sin(angle) + y * cos(angle);
  }
}

void Scale::TransformModel(std::vector<double> &vertex, double k) {
  for (size_t i = 0; k != 0 && i < vertex.size(); ++i) vertex[i] *= k;
}

void Client::SetStrategy(Strategy *v) { operation = v; }

void Client::Transform(std::vector<double> &vertex, double k) {
  operation->TransformModel(vertex, k);
}
}  // namespace s21
