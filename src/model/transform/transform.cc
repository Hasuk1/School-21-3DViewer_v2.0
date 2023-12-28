#include "transform.h"

#include <cmath>
#include <thread>

namespace s21 {
void MoveX::TransformModel(std::vector<double> &vertex, unsigned start,
                           unsigned end, const double k) {
  for (unsigned i = start; i < end; i += 3) vertex[i] += k;
}

void MoveY::TransformModel(std::vector<double> &vertex, unsigned start,
                           unsigned end, const double k) {
  for (unsigned i = start + 1; i < end; i += 3) vertex[i] += k;
}

void MoveZ::TransformModel(std::vector<double> &vertex, unsigned start,
                           unsigned end, const double k) {
  for (unsigned i = start + 2; i < end; i += 3) vertex[i] += k;
}

void RotateX::TransformModel(std::vector<double> &vertex, unsigned start,
                             unsigned end, double angle) {
  angle = angle * M_PI / 180;
  for (unsigned i = start; i < end; i += 3) {
    double y = vertex[i + 1];
    double z = vertex[i + 2];
    vertex[i + 1] = y * cos(angle) + z * sin(angle);
    vertex[i + 2] = -y * sin(angle) + z * cos(angle);
  }
}

void RotateY::TransformModel(std::vector<double> &vertex, unsigned start,
                             unsigned end, double angle) {
  angle = angle * M_PI / 180;
  for (unsigned i = start; i < end; i += 3) {
    double x = vertex[i];
    double z = vertex[i + 2];
    vertex[i] = x * cos(angle) + z * sin(angle);
    vertex[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void RotateZ::TransformModel(std::vector<double> &vertex, unsigned start,
                             unsigned end, double angle) {
  angle = angle * M_PI / 180;
  for (unsigned i = start; i < end; i += 3) {
    double x = vertex[i];
    double y = vertex[i + 1];
    vertex[i + 1] = x * cos(angle) + y * sin(angle);
    vertex[i + 2] = -x * sin(angle) + y * cos(angle);
  }
}

void Scale::TransformModel(std::vector<double> &vertex, unsigned start,
                           unsigned end, double k) {
  for (unsigned i = start; k != 0 && i < end; ++i) vertex[i] *= k;
}

void Client::SetStrategy(Strategy *v) { operation = v; }

void Client::Transform(std::vector<double> &vertex, double k) {
  unsigned numbers_of_threads = std::thread::hardware_concurrency();
  unsigned start = vertex.size() / numbers_of_threads;
  while (start % 3 != 0) ++start;
  std::thread threads[numbers_of_threads];
  for (unsigned i = 0; i < numbers_of_threads; ++i) {
    unsigned start_index = i * start;
    unsigned end_index =
        i == (numbers_of_threads - 1) ? vertex.size() : (i + 1) * start;
    threads[i] = std::thread([this, &vertex, start_index, end_index, k]() {
      operation->TransformModel(vertex, start_index, end_index, k);
    });
  }
  for (unsigned i = 0; i < numbers_of_threads; ++i) {
    threads[i].join();
  }
}
}  // namespace s21
