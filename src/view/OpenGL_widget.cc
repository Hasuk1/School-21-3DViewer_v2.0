#include "OpenGL_widget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

MyOpenGLWidget::~MyOpenGLWidget() {
  verteces_.clear();
  verteces_copy_.clear();
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
  } else if (event->buttons() & Qt::LeftButton) {
    TransformOBJ(s21::kRotateX, -new_pos_.y() * 0.01, true);
    TransformOBJ(s21::kRotateY, new_pos_.x() * 0.01, true);
  }
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
  QPoint numDegrees = event->angleDelta() / 120;
  TransformOBJ(s21::kScale, numDegrees.y() * normalize_coef_ / 5, true);
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
  scale_val_ = 50;
  translate_x_ = translate_y_ = translate_z_ = 0;
  rotate_x_ = rotate_y_ = rotate_z_ = 0;
  update();
}

void MyOpenGLWidget::CloseObject() {
  verteces_.clear();
  edges_.clear();
  verteces_copy_.clear();
  normalize_coef_ = -10;
  scale_val_ = 50;
  translate_x_ = translate_y_ = translate_z_ = 0;
  rotate_x_ = rotate_y_ = rotate_z_ = 0;
}

void MyOpenGLWidget::SetEdgesColor(s21::ColorRGB edges_rgb) {
  settings_.edges_rgb.red = edges_rgb.red / 255;
  settings_.edges_rgb.blue = edges_rgb.blue / 255;
  settings_.edges_rgb.green = edges_rgb.green / 255;
}

void MyOpenGLWidget::SetEdgesType(int value) { settings_.edges_type = value; }

void MyOpenGLWidget::SetEdgesThickness(int value) {
  settings_.edges_thickness = value;
}

void MyOpenGLWidget::SetVerticesColor(s21::ColorRGB vertices_rgb) {
  settings_.vertices_rgb.red = vertices_rgb.red / 255;
  settings_.vertices_rgb.blue = vertices_rgb.blue / 255;
  settings_.vertices_rgb.green = vertices_rgb.green / 255;
}

void MyOpenGLWidget::SetVerticesType(int value) {
  settings_.vertices_type = value;
}

void MyOpenGLWidget::SetVerticesSize(int value) {
  settings_.vertices_size = value;
}

void MyOpenGLWidget::SetBackgroundColor(s21::ColorRGB background_rgb) {
  settings_.background_rgb.red = background_rgb.red / 255;
  settings_.background_rgb.blue = background_rgb.blue / 255;
  settings_.background_rgb.green = background_rgb.green / 255;
}

void MyOpenGLWidget::SetProjectionType(int value) {
  settings_.projection_type = value;
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
  update();
}

void MyOpenGLWidget::BuildLines() {
  if (settings_.edges_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else
    glDisable(GL_LINE_STIPPLE);
  glLineWidth(settings_.edges_thickness);
  glColor3f(settings_.edges_rgb.red, settings_.edges_rgb.green,
            settings_.edges_rgb.blue);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_LINES, static_cast<GLsizei>(edges_.size()), GL_UNSIGNED_INT,
                 edges_.data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyOpenGLWidget::BuildPoints() {
  if (settings_.vertices_type == 1) glEnable(GL_POINT_SMOOTH);
  glPointSize(settings_.vertices_size);
  glColor3f(settings_.vertices_rgb.red, settings_.vertices_rgb.green,
            settings_.vertices_rgb.blue);
  glVertexPointer(3, GL_DOUBLE, 0, verteces_.data());
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(verteces_.size() / 3));
  glDisableClientState(GL_VERTEX_ARRAY);
  if (settings_.vertices_type == 1) glDisable(GL_POINT_SMOOTH);
}
