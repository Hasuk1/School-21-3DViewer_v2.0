#include "OpenGL_widget.h"

my_ogl_widget::my_ogl_widget(QWidget *parent) : QOpenGLWidget{parent} {}

my_ogl_widget::~my_ogl_widget() {
  verteces_.clear();
  edges_.clear();
}

void my_ogl_widget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void my_ogl_widget::paintGL() {
  glClearColor(bg_r, bg_g, bg_b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, verteces_.data());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (this->projection_type == 0) {  // Перспективная проекция
    glFrustum(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
              1 * normalize_coef, normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, 0, -2 * normalize_coef);
    glRotatef(30, 1, 0, 0);
  } else {  // Ортогональная проекция
    glOrtho(-1 * normalize_coef, 1 * normalize_coef, -1 * normalize_coef,
            1 * normalize_coef, -1 * normalize_coef, 1000 * normalize_coef);
    glTranslatef(0, -normalize_coef / 2, 0);
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  if (this->v_type != 0) build_points();
  build_lines();
  glDisableClientState(GL_VERTEX_ARRAY);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void my_ogl_widget::parse_file(char *filename) {
  //  memory_free(&this->data);
  //  data = {0, NULL, 0, NULL};
  if (filename) {
    s21::ObjParser kek;
    std::string file_name = filename;
    s21::Status status = kek.ParseFile(filename);
    if (status == s21::kOk) {
      verteces_ = kek.GetVertex();
      edges_ = kek.GetEdges();
      set_normalize_coef();
      update();
    } else if (status == s21::kErrorIncorrectFile) {
      //      closeObject();
      QMessageBox::information(this, "ERROR", "Enter a correctly obj-file");
    } else if (status == s21::kErrorFileMissing) {
      //      closeObject();
      QMessageBox::information(this, "ERROR",
                               "Enter a obj-file with coorect data");
    }
  }
}

// void my_ogl_widget::closeObject() {
//   memory_free(&this->data);
//   data = {0, NULL, 0, NULL};
//   set_normalize_coef();
//   update();
// }

void my_ogl_widget::set_normalize_coef() {
  normalize_coef = -10;
  for (auto &x : verteces_) {
    if (abs(x) > normalize_coef) {
      normalize_coef = abs(x);
    }
  }
}

void my_ogl_widget::build_lines() {
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

void my_ogl_widget::build_points() {
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

// void my_ogl_widget::mouseMoveEvent(QMouseEvent *event) {
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

// void my_ogl_widget::wheelEvent(QWheelEvent *event) {
//   QPoint numDegrees = event->angleDelta() / 120;
//   double step = normalize_coef / 10;
//   double scale_tmp = scale_val;
//   if ((int)(scale_val + numDegrees.y() * step) > 0) {
//     scale_val += numDegrees.y() * step;
//     scale(&this->data, scale_val / scale_tmp);
//     update();
//   }
// }

// void my_ogl_widget::mousePressEvent(QMouseEvent *event) {
//   current_pos = event->globalPosition().toPoint();
// }
