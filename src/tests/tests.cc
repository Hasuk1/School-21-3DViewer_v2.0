#include <gtest/gtest.h>

#include <cmath>
#include <filesystem>

#include "../controller/3d_viewer_controller.h"

#define kEpsilon 1e-05

class ViewerModelTest : public ::testing::Test {
 protected:
  void SetUp() override {
    controller_ = &s21::ObjController::SinlgeObjController();
    current_path_ = std::filesystem::current_path().string();
  }

  void TearDown() override { controller_->ClearObjData(); }

  std::vector<double> kVertices_ = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                    0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                    0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};

  s21::ObjController* controller_;
  std::string current_path_;
  s21::Client affine_strategy_;
};

TEST_F(ViewerModelTest, parser_no_file) {
  EXPECT_EQ(controller_->ParseObjFile("xx.obj"), s21::kErrorFileMissing);
}

TEST_F(ViewerModelTest, parser_empty_file) {
  EXPECT_EQ(controller_->ParseObjFile(current_path_ + "/tests/obj/empty.obj"),
            s21::kErrorFileEmpty);
}

TEST_F(ViewerModelTest, parser_normal) {
  std::vector<double> vertices = {0.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 2.0,
                                  0.0, 0.0, 2.0, 2.0, 2.0, 0.0, 0.0, 2.0,
                                  0.0, 2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 2.0};
  std::vector<unsigned> edges = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 0, 3,
                                 3, 2, 0, 1, 1, 3, 2, 7, 7, 6, 3, 7,
                                 7, 4, 7, 5, 5, 4, 5, 0, 5, 1};
  EXPECT_EQ(controller_->ParseObjFile(current_path_ + "/tests/obj/cube.obj"),
            s21::kOk);
  EXPECT_EQ(controller_->GetObjVertex(), vertices);
  EXPECT_EQ(controller_->GetObjEdges(), edges);
  EXPECT_EQ(controller_->GetObjNormalizeCoef(), 2);
}

TEST_F(ViewerModelTest, affine_transformation_move_x) {
  s21::MoveX strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10 * 2 * 0.01);
  std::vector<double> vertices_e = {0.2, 0, 0, 0.2, 0, 2, 0.2, 2, 0, 0.2, 2, 2,
                                    2.2, 0, 0, 2.2, 0, 2, 2.2, 2, 0, 2.2, 2, 2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

TEST_F(ViewerModelTest, affine_transformation_move_y) {
  s21::MoveY strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10 * 2 * 0.01);
  std::vector<double> vertices_e = {0, 0.2, 0, 0, 0.2, 2, 0, 2.2, 0, 0, 2.2, 2,
                                    2, 0.2, 0, 2, 0.2, 2, 2, 2.2, 0, 2, 2.2, 2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

TEST_F(ViewerModelTest, affine_transformation_move_z) {
  s21::MoveZ strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10 * 2 * 0.01);
  std::vector<double> vertices_e = {0, 0, 0.2, 0, 0, 2.2, 0, 2, 0.2, 0, 2, 2.2,
                                    2, 0, 0.2, 2, 0, 2.2, 2, 2, 0.2, 2, 2, 2.2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

TEST_F(ViewerModelTest, affine_transformation_rotate_x) {
  s21::RotateX strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10);
  std::vector<double> vertices_e = {
      0, 0,       0,         0, 0.347296, 1.96962, 0, 1.96962,  -0.347296,
      0, 2.31691, 1.62232,   2, 0,        0,       2, 0.347296, 1.96962,
      2, 1.96962, -0.347296, 2, 2.31691,  1.62232};

  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

TEST_F(ViewerModelTest, affine_transformation_rotate_y) {
  s21::RotateY strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10);
  std::vector<double> vertices_e = {
      0, 0,        0,       0.347296, 0,         1.96962, 0,         2,
      0, 0.347296, 2,       1.96962,  1.96962,   0,       -0.347296, 2.31691,
      0, 1.62232,  1.96962, 2,        -0.347296, 2.31691, 2,         1.62232};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

TEST_F(ViewerModelTest, affine_transformation_rotate_z) {
  s21::RotateZ strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10);
  std::vector<double> vertices_e = {
      0,        0,       0, 0,       0,         2, 0.347296, 1.96962,   0,
      0.347296, 1.96962, 2, 1.96962, -0.347296, 0, 1.96962,  -0.347296, 2,
      2.31691,  1.62232, 0, 2.31691, 1.62232,   2};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

TEST_F(ViewerModelTest, affine_transformation_scale) {
  s21::Scale strategy;
  affine_strategy_.SetStrategy(&strategy);
  affine_strategy_.Transform(kVertices_, 10);
  std::vector<double> vertices_e = {0,  0, 0, 0,  0, 20, 0,  20, 0, 0,  20, 20,
                                    20, 0, 0, 20, 0, 20, 20, 20, 0, 20, 20, 20};
  for (size_t i = 0; i < vertices_e.size(); ++i) {
    EXPECT_NEAR(kVertices_[i], vertices_e[i], kEpsilon);
  }
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}