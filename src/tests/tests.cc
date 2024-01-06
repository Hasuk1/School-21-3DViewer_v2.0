#include <gtest/gtest.h>

#include <cmath>

#include "../controller/3d_viewer_controller.h"

#define kEpsilon 1e-05
// const std::string kPath =
//     "/Users/perlabru/my-project/School-21-3DViewer_v2.0/src/tests/obj/";

const std::string kPath = "/home/3d_viewer/tests/obj/";

TEST(ViewerModelTest, parser_no_file) {
  s21::ObjController &controller = s21::ObjController::SinlgeObjController();
  EXPECT_EQ(controller.ParseObjFile("xx.obj"), s21::kErrorFileMissing);
  controller.ClearObjData();
}

TEST(ViewerModelTest, parser_empty_file) {
  s21::ObjController &controller = s21::ObjController::SinlgeObjController();
  EXPECT_EQ(controller.ParseObjFile(kPath + "empty.obj"), s21::kErrorFileEmpty);
  controller.ClearObjData();
}

TEST(ViewerModelTest, parser_normal) {
  s21::ObjController &controller = s21::ObjController::SinlgeObjController();
  std::vector<double> vertices = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                  0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                  0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<unsigned> edges = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 0, 3,
                                 3, 2, 0, 1, 1, 3, 2, 7, 7, 6, 3, 7,
                                 7, 4, 7, 5, 5, 4, 5, 0, 5, 1};
  EXPECT_EQ(controller.ParseObjFile(kPath + "cube.obj"), s21::kOk);
  EXPECT_EQ(controller.GetObjVertex(), vertices);
  EXPECT_EQ(controller.GetObjEdges(), edges);
  EXPECT_EQ(controller.GetObjNormalizeCoef(), 2);
}

TEST(ViewerModelTest, affine_transformation_move_x) {
  s21::Client affine_strategy;
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::MoveX strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10 * 2 * 0.01);
  std::vector<double> vertices_e = {0.2, 0, 0, 0.2, 0, 2, 0.2, 2, 0, 0.2, 2, 2,
                                    2.2, 0, 0, 2.2, 0, 2, 2.2, 2, 0, 2.2, 2, 2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

TEST(ViewerModelTest, affine_transformation_move_y) {
  s21::Client affine_strategy;
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::MoveY strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10 * 2 * 0.01);
  std::vector<double> vertices_e = {0, 0.2, 0, 0, 0.2, 2, 0, 2.2, 0, 0, 2.2, 2,
                                    2, 0.2, 0, 2, 0.2, 2, 2, 2.2, 0, 2, 2.2, 2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

TEST(ViewerModelTest, affine_transformation_move_z) {
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::MoveZ strategy;
  s21::Client affine_strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10 * 2 * 0.01);
  std::vector<double> vertices_e = {0, 0, 0.2, 0, 0, 2.2, 0, 2, 0.2, 0, 2, 2.2,
                                    2, 0, 0.2, 2, 0, 2.2, 2, 2, 0.2, 2, 2, 2.2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

TEST(ViewerModelTest, affine_transformation_rotate_x) {
  s21::Client affine_strategy;
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::RotateX strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10);
  std::vector<double> vertices_e = {
      0, 0,       0,         0, 0.347296, 1.96962, 0, 1.96962,  -0.347296,
      0, 2.31691, 1.62232,   2, 0,        0,       2, 0.347296, 1.96962,
      2, 1.96962, -0.347296, 2, 2.31691,  1.62232};

  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

TEST(ViewerModelTest, affine_transformation_rotate_y) {
  s21::Client affine_strategy;
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::RotateY strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10);
  std::vector<double> vertices_e = {
      0, 0,        0,       0.347296, 0,         1.96962, 0,         2,
      0, 0.347296, 2,       1.96962,  1.96962,   0,       -0.347296, 2.31691,
      0, 1.62232,  1.96962, 2,        -0.347296, 2.31691, 2,         1.62232};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

TEST(ViewerModelTest, affine_transformation_rotate_z) {
  s21::Client affine_strategy;
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::RotateZ strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10);
  std::vector<double> vertices_e = {
      0,        0,       0, 0,       0,         2, 0.347296, 1.96962,   0,
      0.347296, 1.96962, 2, 1.96962, -0.347296, 0, 1.96962,  -0.347296, 2,
      2.31691,  1.62232, 0, 2.31691, 1.62232,   2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

TEST(ViewerModelTest, affine_transformation_scale) {
  s21::Client affine_strategy;
  std::vector<double> vertices_a = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  s21::Scale strategy;
  affine_strategy.SetStrategy(&strategy);
  affine_strategy.Transform(vertices_a, 10);
  std::vector<double> vertices_e = {0,  0, 0, 0,  0, 20, 0,  20, 0, 0,  20, 20,
                                    20, 0, 0, 20, 0, 20, 20, 20, 0, 20, 20, 20};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(vertices_a[i], vertices_e[i], kEpsilon);
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}