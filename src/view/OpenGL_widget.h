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

  QString GetVertexAmount();
  QString GetEdgeAmount();

  void MoveByX(int value);
  void MoveByY(int value);
  ////////////////
  double scale_val = 50;
  double rotate_x, rotate_y, rotate_z;
  double translate_x, translate_y, translate_z;
  double v_size = 1;
  double l_thickness = 1;
  int projection_type = 1;  // 0-параллельная 1-центральная
  int v_type = 0;
  int l_type = 0;
  double v_r = 1, v_g = 1, v_b = 1;
  double l_r = 1, l_g = 100, l_b = 1;
  double bg_r = 0, bg_g = 0, bg_b = 0;

 private:
  ~MyOpenGLWidget() override;

  void BuildLines();
  void BuildPoints();

  s21::ObjController &controller_ = s21::ObjController::SinlgeObjController();

  std::vector<double> verteces_;
  std::vector<double> verteces_copy_;
  std::vector<unsigned> edges_;
  GLfloat normalize_coef_;
  QPoint current_pos_, new_pos_;
};

#endif  // CPP4_3DVIEWER_V2_SRC_OPENGL_WIDGET_H
