#ifndef CPP4_3DVIEWER_V2_SRC_OPENGL_WIDGET_H_
#define CPP4_3DVIEWER_V2_SRC_OPENGL_WIDGET_H_
#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl.h>

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QSettings>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <iostream>

#include "./../controller/3d_viewer_controller.h"

namespace s21 {
struct ColorRGB {
  float red;
  float green;
  float blue;
};

struct Settings {
  ColorRGB edges_rgb = {1, 1, 1};
  int edges_type = 0;
  int edges_thickness = 1;
  ColorRGB vertices_rgb = {1, 1, 1};
  int vertices_type = 0;
  double vertices_size = 1;
  ColorRGB background_rgb = {0, 0, 0};
  int projection_type = 0;
};
}  // namespace s21

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit MyOpenGLWidget(QWidget *parent = nullptr);
  void initializeGL() override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void ParseFile(QString path_to_file);
  void ReRender();
  void CloseObject();
  void SetEdgesColor(s21::ColorRGB edges_rgb);
  void SetEdgesType(int value);
  void SetEdgesThickness(int value);
  void SetVerticesColor(s21::ColorRGB vertices_rgb);
  void SetVerticesType(int value);
  void SetVerticesSize(int value);
  void SetBackgroundColor(s21::ColorRGB background_rgb);
  void SetProjectionType(int value);
  s21::Settings GetSettings();
  QString GetVertexAmount();
  QString GetEdgeAmount();
  void TransformOBJ(s21::Mode mode, double value, bool is_click);

 private:
  ~MyOpenGLWidget() override;
  void BuildLines();
  void BuildPoints();
  void MoveOBJ(s21::Mode mode, double value, bool is_click);
  void RotateOBJ(s21::Mode mode, double value, bool is_click);
  void ScaleOBJ(double value, bool is_click);

  s21::ObjController &controller_ = s21::ObjController::SinlgeObjController();
  std::vector<double> verteces_;
  std::vector<double> verteces_copy_;
  std::vector<unsigned> edges_;
  QPoint current_pos_, new_pos_;
  GLfloat normalize_coef_;
  double translate_x_, translate_y_, translate_z_;
  double rotate_x_, rotate_y_, rotate_z_;
  double scale_val_ = 50;
  s21::Settings settings_;
};

#endif  // CPP4_3DVIEWER_V2_SRC_OPENGL_WIDGET_H
