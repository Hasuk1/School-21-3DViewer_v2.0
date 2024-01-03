#include "OpenGL_widget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

MyOpenGLWidget::~MyOpenGLWidget() {
  verteces_.clear();
  edges_.clear();
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::paintGL() {
  glClearColor(settings_.background_rgb.red, settings_.background_rgb.green,
               settings_.background_rgb.blue, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, verteces_.data());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (settings_.projection_type == 0) {
    glOrtho(-1 * normalize_coef_, 1 * normalize_coef_, -1 * normalize_coef_,
            1 * normalize_coef_, -1 * normalize_coef_, 1000 * normalize_coef_);
    glTranslatef(0, -normalize_coef_ / 2, 0);
  } else {
    glFrustum(-1 * normalize_coef_, 1 * normalize_coef_, -1 * normalize_coef_,
              1 * normalize_coef_, normalize_coef_, 1000 * normalize_coef_);
    glTranslatef(0, 0, -2 * normalize_coef_);
    glRotatef(30, 1, 0, 0);
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  if (settings_.vertices_type != 0) BuildPoints();
  BuildLines();
  glDisableClientState(GL_VERTEX_ARRAY);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
  current_pos_ = event->globalPosition().toPoint();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  new_pos_ = QPoint(event->globalPosition().toPoint() - current_pos_);

  if (event->buttons() & Qt::RightButton) {
    TransformOBJ(s21::kMoveX, new_pos_.x() * normalize_coef_ / 5120, true);
    TransformOBJ(s21::kMoveY, -new_pos_.y() * normalize_coef_ / 5120, true);
    update();
  } else if (event->buttons() & Qt::LeftButton) {
    TransformOBJ(s21::kRotateX, -new_pos_.y() * 0.01, true);
    TransformOBJ(s21::kRotateY, new_pos_.x() * 0.01, true);
    update();
  }
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 120;
  TransformOBJ(s21::kScale, numDegrees.y() * normalize_coef_ / 5, true);
  update();
}

void MyOpenGLWidget::ParseFile(QString path_to_file) {
  verteces_.clear();
  edges_.clear();
  s21::Status status = controller_.ParseObjFile(path_to_file.toStdString());
  QString error_str;
  if (status == s21::kOk) {
    verteces_ = controller_.GetObjVertex();
    edges_ = controller_.GetObjEdges();
    normalize_coef_ = controller_.GetObjNormalizeCoef();
    controller_.ClearObjData();
    update();
    verteces_copy_ = verteces_;
  } else if (status == s21::kErrorIncorrectFile) {
    error_str = "Enter a correctly obj-file";
  } else if (status == s21::kErrorFileMissing) {
    error_str = "Enter a obj-file with coorect data";
  } else if (status == s21::kErrorFileEmpty) {
    error_str = "Enter a obj-file with some data";
  }
  if (status != s21::kOk) {
    CloseObject();
    QMessageBox::information(this, "ERROR", error_str);
  }
}

void MyOpenGLWidget::ReRender() {
  verteces_.clear();
  verteces_ = verteces_copy_;
  update();
}

void MyOpenGLWidget::CloseObject() {
  verteces_.clear();
  edges_.clear();
  normalize_coef_ = -10;
  update();
}

void MyOpenGLWidget::SetProjectionType(int value) {
  settings_.projection_type = value;
}

void MyOpenGLWidget::SetEdgesColor(s21::ColorRGB edges_rgb) {
  settings_.line_rgb.red = edges_rgb.red;
  settings_.line_rgb.blue = edges_rgb.blue;
  settings_.line_rgb.green = edges_rgb.green;
}

s21::Settings MyOpenGLWidget::GetSettings() { return settings_; }

QString MyOpenGLWidget::GetVertexAmount() {
  return QString::number(verteces_.size() / 3);
}

QString MyOpenGLWidget::GetEdgeAmount() {
  return QString::number(edges_.size() / 2);
}

void MyOpenGLWidget::MoveOBJ(s21::Mode mode, double value, bool is_click) {
  double translate_coef;
  if (mode == s21::kMoveX) {
    translate_coef = translate_x_;
    if (!is_click) translate_x_ = value;
  } else if (mode == s21::kMoveY) {
    translate_coef = translate_y_;
    if (!is_click) translate_y_ = value;
  } else if (mode == s21::kMoveZ) {
    translate_coef = translate_z_;
    if (!is_click) translate_z_ = value;
  }
  if (!is_click) value = (value - translate_coef) * normalize_coef_ * 0.01;
  controller_.TransformModel(mode, verteces_, value);
}

void MyOpenGLWidget::RotateOBJ(s21::Mode mode, double value, bool is_click) {
  double rotate_coef;
  if (mode == s21::kRotateX) {
    rotate_coef = rotate_x_;
    if (!is_click) rotate_x_ = value;
  } else if (mode == s21::kRotateY) {
    rotate_coef = rotate_y_;
    if (!is_click) rotate_y_ = value;
  } else if (mode == s21::kRotateZ) {
    rotate_coef = rotate_z_;
    if (!is_click) rotate_z_ = value;
  }
  if (!is_click) value -= rotate_coef;
  controller_.TransformModel(mode, verteces_, value);
}

void MyOpenGLWidget::ScaleOBJ(double value, bool is_click) {
  double scale_coef = scale_val_;
  if (is_click && (int)(scale_val_ + value) > 0) {
    scale_val_ += value;
    controller_.TransformModel(s21::kScale, verteces_, scale_val_ / scale_coef);
  } else if (!is_click) {
    scale_val_ = value;
    controller_.TransformModel(s21::kScale, verteces_, value / scale_coef);
  }
}

void MyOpenGLWidget::TransformOBJ(s21::Mode mode, double value, bool is_click) {
  if (mode == s21::kMoveX || mode == s21::kMoveY || mode == s21::kMoveZ) {
    MoveOBJ(mode, value, is_click);
  } else if (mode == s21::kRotateX || mode == s21::kRotateY ||
             mode == s21::kRotateZ) {
    RotateOBJ(mode, value, is_click);
  } else if (mode == s21::kScale) {
    ScaleOBJ(value, is_click);
  }
}

void MyOpenGLWidget::BuildLines() {
  if (settings_.line_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(settings_.line_thickness);
  glColor3f(settings_.line_rgb.red, settings_.line_rgb.green,
            settings_.line_rgb.blue);
  glDrawElements(GL_LINES, edges_.size(), GL_UNSIGNED_INT, edges_.data());
  if (settings_.line_type == 1) glDisable(GL_LINE_STIPPLE);
}

void MyOpenGLWidget::BuildPoints() {
  if (settings_.vertices_type == 1) glEnable(GL_POINT_SMOOTH);
  glPointSize(settings_.vertices_size);
  glColor3f(settings_.vertices_rgb.red, settings_.vertices_rgb.green,
            settings_.vertices_rgb.blue);
  glDrawArrays(GL_POINTS, 0, verteces_.size());
  if (settings_.vertices_type == 1) glDisable(GL_POINT_SMOOTH);
}
