#ifndef OPENGL_WIDGET_H
#define OPENGL_WIDGET_H
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

#include "../model/parser/file_parser.h"

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit MyOpenGLWidget(QWidget *parent = nullptr);

  void initializeGL() override;
  void paintGL() override;

  void ParseFile(QString path_to_file);

  QString GetVertexAmount();
  QString GetEdgeAmount();
  //  void mousePressEvent(QMouseEvent *event) override;
  //  void mouseMoveEvent(QMouseEvent *event) override;
  //  void wheelEvent(QWheelEvent *event) override;
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
  void SetNormalizeCoef();
  void CloseObject();

  void BuildLines();
  void BuildPoints();

  std::vector<double> verteces_;
  std::vector<unsigned int> edges_;
  GLfloat normalize_coef_;

  // QPoint current_pos_;
  // QPoint new_pos_;
};

#endif  // OPENGL_WIDGET_H
