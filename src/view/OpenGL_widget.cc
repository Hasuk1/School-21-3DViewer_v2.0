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
  glClearColor(bg_r, bg_g, bg_b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, verteces_.data());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->projection_type == 0) {
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
  if (this->v_type != 0) BuildPoints();
  BuildLines();
  glDisableClientState(GL_VERTEX_ARRAY);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void MyOpenGLWidget::ParseFile(QString path_to_file) {
  verteces_.clear();
  edges_.clear();
  s21::ObjParser &parser = s21::ObjParser::SingleParser();
  s21::Status status = parser.ParseFile(path_to_file.toStdString());
  QString error_str;
  if (status == s21::kOk) {
    verteces_ = parser.GetVertex();
    edges_ = parser.GetEdges();
    parser.ClearData();
    SetNormalizeCoef();
    update();
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

void MyOpenGLWidget::CloseObject() {
  verteces_.clear();
  edges_.clear();
  SetNormalizeCoef();
  update();
}

QString MyOpenGLWidget::GetVertexAmount() {
  return QString::number(verteces_.size() / 3);
}
QString MyOpenGLWidget::GetEdgeAmount() {
  return QString::number(edges_.size() / 2);
}

void MyOpenGLWidget::SetNormalizeCoef() {
  GLfloat x_max = -10, y_max = -10, z_max = -10;
  for (size_t i = 0; i < verteces_.size(); i += 3) {
    for (size_t j = 0; j < 3; ++j) {
      if (j == 0 && abs(verteces_[i + j]) > x_max)
        x_max = abs(verteces_[i + j]);
      if (j == 1 && abs(verteces_[i + j]) > y_max)
        y_max = abs(verteces_[i + j]);
      if (j == 2 && abs(verteces_[i + j]) > z_max)
        z_max = abs(verteces_[i + j]);
    }
  }
  normalize_coef_ = (x_max + y_max + z_max) / 3;
}

void MyOpenGLWidget::BuildLines() {
  if (this->l_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(this->l_thickness);
  glColor3f(this->l_r, this->l_g, this->l_b);
  glDrawElements(GL_LINES, edges_.size(), GL_UNSIGNED_INT, edges_.data());
  if (this->l_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyOpenGLWidget::BuildPoints() {
  if (this->v_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(this->v_size);
  glColor3f(this->v_r, this->v_g, this->v_b);
  glDrawArrays(GL_POINTS, 0, verteces_.size());
  if (this->v_type == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

// void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
//   new_pos = QPoint(event->globalPosition().toPoint() - current_pos);

//  if (event->buttons() & Qt::RightButton) {
//    move_X(&this->data, new_pos.x() * this->normalize_coef / 5120);
//    move_Y(&this->data, -new_pos.y() * this->normalize_coef / 5120);
//    update();
//  } else if (event->buttons() & Qt::LeftButton) {
//    rotate_X(&this->data, -new_pos.y() * 0.01);
//    rotate_Y(&this->data, new_pos.x() * 0.01);
//    update();
//  }
//}

// void MyOpenGLWidget::wheelEvent(QWheelEvent *event) {
//   QPoint numDegrees = event->angleDelta() / 120;
//   double step = normalize_coef / 10;
//   double scale_tmp = scale_val;
//   if ((int)(scale_val + numDegrees.y() * step) > 0) {
//     scale_val += numDegrees.y() * step;
//     scale(&this->data, scale_val / scale_tmp);
//     update();
//   }
// }

// void MyOpenGLWidget::mousePressEvent(QMouseEvent *event) {
//   current_pos = event->globalPosition().toPoint();
// }
