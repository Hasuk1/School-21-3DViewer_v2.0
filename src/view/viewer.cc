#include "viewer.h"

Viewer::Viewer(QWidget* parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
  ui_->setupUi(this);
  setWindowTitle("3DViewer_v2.0");
  setFixedSize(width(), height());
  InitializeConnect();
  settings_ = new QSettings("setting3DViewer.conf", "settings", this);
  LoadSettings();
}

Viewer::~Viewer() {
  ui_->OGLWindow->CloseObject();
  SaveSettings();
  delete settings_;
  delete ui_;
}

void Viewer::on_open_obj_file_clicked() {
  QString path_to_file = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), QDir::rootPath(), tr("Obj Files (*.obj)"));
  ui_->path_to_obj_file->setText(path_to_file);
}

void Viewer::on_render_obj_file_clicked() {
  /*Set standart settings*/
  ui_->slider_move_x->setValue(0);
  ui_->slider_move_y->setValue(0);
  ui_->slider_move_z->setValue(0);
  ui_->slider_rotate_x->setValue(0);
  ui_->slider_rotate_y->setValue(0);
  ui_->slider_rotate_z->setValue(0);
  ui_->slider_scale->setValue(50);
  /***********************/

  if (QFile::exists(ui_->path_to_obj_file->text())) {
    QString current_open_file_name = ui_->current_obj_file_name->text();
    QFileInfo file_info(ui_->path_to_obj_file->text());
    QString file_name_to_render = file_info.fileName();

    if (current_open_file_name != file_name_to_render) {
      ui_->OGLWindow->ParseFile(ui_->path_to_obj_file->text());
      ui_->current_obj_file_name->setText(file_name_to_render);
      ui_->current_obj_edges->setText(ui_->OGLWindow->GetEdgeAmount());
      ui_->current_obj_vertices->setText(ui_->OGLWindow->GetVertexAmount());
    } else
      ui_->OGLWindow->ReRender();

  } else {
    QMessageBox::information(this, "ERROR", "Enter a path to file correctly");
    ui_->current_obj_vertices->setText("");
    ui_->current_obj_edges->setText("");
    ui_->current_obj_file_name->setText("");
  }
}

void Viewer::on_close_object_clicked() {
  ui_->OGLWindow->CloseObject();
  ui_->OGLWindow->update();
  ui_->current_obj_vertices->setText("");
  ui_->current_obj_edges->setText("");
  ui_->current_obj_file_name->setText("");
  ui_->path_to_obj_file->setText("");
}

void Viewer::Transform(int value) {
  QObject* sender_object = sender();
  s21::Mode mode = s21::kDefault;
  if (sender_object == ui_->slider_move_x) {
    mode = s21::kMoveX;
  } else if (sender_object == ui_->slider_move_y) {
    mode = s21::kMoveY;
  } else if (sender_object == ui_->slider_move_z) {
    mode = s21::kMoveZ;
  } else if (sender_object == ui_->slider_rotate_x) {
    mode = s21::kRotateX;
  } else if (sender_object == ui_->slider_rotate_y) {
    mode = s21::kRotateY;
  } else if (sender_object == ui_->slider_rotate_z) {
    mode = s21::kRotateZ;
  } else if (sender_object == ui_->slider_scale) {
    mode = s21::kScale;
  }
  if (mode != s21::kDefault) ui_->OGLWindow->TransformOBJ(mode, value, false);
  ui_->OGLWindow->update();
}

void Viewer::ChangeColorEdges() {
  QPushButton* button = qobject_cast<QPushButton*>(sender());
  QString current_style = button->styleSheet();
  if (button->text() == "R") {
    ui_->OGLWindow->SetEdgesColor({211, 54, 48});
  }
  button->setStyleSheet(current_style +
                        "border: 2px solid rgb(200, 249, 100);");
}

void Viewer::ChangeProjectionType() {
  ui_->OGLWindow->SetProjectionType(
      ui_->combo_box_projection_type->currentIndex());
  ui_->OGLWindow->update();
}

void Viewer::SaveSettings() {
  s21::Settings current_settings = ui_->OGLWindow->GetSettings();
  settings_->setValue("settings", 1);
  settings_->setValue("projection_type", current_settings.projection_type);
}

void Viewer::LoadSettings() {
  if (settings_->value("settings").toInt()) {
    s21::Settings saved_settings;
    saved_settings.projection_type =
        settings_->value("projection_type").toInt();

    SetLoadedSettings(saved_settings);
  }
}

void Viewer::SetLoadedSettings(s21::Settings settings) {
  ui_->OGLWindow->SetProjectionType(settings.projection_type);
  ui_->combo_box_projection_type->setCurrentIndex(settings.projection_type);
}

void Viewer::InitializeConnect() {
  /*Initialize affine*/
  connect(ui_->slider_move_x, &QSlider::valueChanged, this, &Viewer::Transform);
  connect(ui_->spin_box_move_x, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_move_x, &QSlider::setValue);
  connect(ui_->slider_move_x, &QSlider::valueChanged, ui_->spin_box_move_x,
          QOverload<int>::of(&QSpinBox::setValue));

  connect(ui_->slider_move_y, &QSlider::valueChanged, this, &Viewer::Transform);
  connect(ui_->spin_box_move_y, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_move_y, &QSlider::setValue);
  connect(ui_->slider_move_y, &QSlider::valueChanged, ui_->spin_box_move_y,
          QOverload<int>::of(&QSpinBox::setValue));

  connect(ui_->slider_move_z, &QSlider::valueChanged, this, &Viewer::Transform);
  connect(ui_->spin_box_move_z, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_move_z, &QSlider::setValue);
  connect(ui_->slider_move_z, &QSlider::valueChanged, ui_->spin_box_move_z,
          QOverload<int>::of(&QSpinBox::setValue));

  connect(ui_->slider_scale, &QSlider::valueChanged, this, &Viewer::Transform);
  connect(ui_->spin_box_scale, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_scale, &QSlider::setValue);
  connect(ui_->slider_scale, &QSlider::valueChanged, ui_->spin_box_scale,
          QOverload<int>::of(&QSpinBox::setValue));

  connect(ui_->slider_rotate_x, &QSlider::valueChanged, this,
          &Viewer::Transform);
  connect(ui_->spin_box_rotate_x, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_rotate_x, &QSlider::setValue);
  connect(ui_->slider_rotate_x, &QSlider::valueChanged, ui_->spin_box_rotate_x,
          QOverload<int>::of(&QSpinBox::setValue));

  connect(ui_->slider_rotate_y, &QSlider::valueChanged, this,
          &Viewer::Transform);
  connect(ui_->spin_box_rotate_y, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_rotate_y, &QSlider::setValue);
  connect(ui_->slider_rotate_y, &QSlider::valueChanged, ui_->spin_box_rotate_y,
          QOverload<int>::of(&QSpinBox::setValue));

  connect(ui_->slider_rotate_z, &QSlider::valueChanged, this,
          &Viewer::Transform);
  connect(ui_->spin_box_rotate_z, QOverload<int>::of(&QSpinBox::valueChanged),
          ui_->slider_rotate_z, &QSlider::setValue);
  connect(ui_->slider_rotate_z, &QSlider::valueChanged, ui_->spin_box_rotate_z,
          QOverload<int>::of(&QSpinBox::setValue));

  /*Initialize edges color*/
  connect(ui_->edges_red, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);

  /*Initialize projection type*/
  connect(ui_->combo_box_projection_type,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &Viewer::ChangeProjectionType);
  /************/
}
