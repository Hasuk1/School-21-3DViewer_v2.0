void Model::RotateFunc(double rotate, int axes1, int axes2,
                       std::vector<double> &vector_to_rotate, size_t start,
                       size_t end) {
  for (size_t i = start; i < end; i += 3) {
    double v1 = vector_to_rotate[i + axes1] * cos(rotate) -
                vector_to_rotate[i + axes2] * sin(rotate);
    double v2 = vector_to_rotate[i + axes1] * sin(rotate) +
                vector_to_rotate[i + axes2] * cos(rotate);
    vector_to_rotate[i + axes1] = v1;
    vector_to_rotate[i + axes2] = v2;
  }
}

void Model::ThreadRotate(int axes1, int axes2, double rotate,
                         std::vector<double> &vector_to_rotate) {
    short int count_of_threads = std::thread::hardware_concurrency();
  int start = vector_to_rotate.size() / count_of_threads;
  while (start % 3 != 0) ++start;
  std::thread threads[count_of_threads];
  for (int i = 0; i < count_of_threads; ++i) {
    threads[i] =
        std::thread(&s21::Model::RotateFunc, this, rotate, axes1, axes2,
                    std::ref(vector_to_rotate), start * i,
                    (i == (count_of_threads - 1) ? vector_to_rotate.size() : (i + 1) * start));
  }
  for (int i = 0; i < 6; ++i) {
    threads[i].join();
  }
}

void Model::RotateVector(double rotate, Axis axes) {
  if (!rotate  rotate <= -100000  rotate >= 100000) return;
  int axes1 = (axes + 1) % 3;
  int axes2 = (axes + 2) % 3;
  rotate = rotate * M_PI / 180;
  ThreadRotate(axes1, axes2, rotate, vertexes_wire_);
  ThreadRotate(axes1, axes2, rotate, vertexes_shade_);
  ThreadRotate(axes1, axes2, rotate, normal_coords_);
}
