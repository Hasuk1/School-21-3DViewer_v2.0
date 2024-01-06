#include "viewer.h"

extern "C" {
#include "include/gif.h"
}

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
  SetStandartAffine();
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

void Viewer::on_button_close_object_clicked() {
  SetStandartAffine();
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
}

void Viewer::ChangeColorEdges() {
  SetStandartEdgesButtonStyle();
  QObject* sender_button = sender();
  QString current_style = qobject_cast<QPushButton*>(sender())->styleSheet();
  QString border = "border:2px solid rgb(200, 249, 100);";
  if (sender_button == ui_->edges_red) {
    ui_->OGLWindow->SetEdgesColor({211, 54, 48});
  } else if (sender_button == ui_->edges_orange) {
    ui_->OGLWindow->SetEdgesColor({226, 148, 61});
  } else if (sender_button == ui_->edges_yellow) {
    ui_->OGLWindow->SetEdgesColor({242, 216, 77});
  } else if (sender_button == ui_->edges_green) {
    ui_->OGLWindow->SetEdgesColor({102, 195, 89});
  } else if (sender_button == ui_->edges_blue) {
    ui_->OGLWindow->SetEdgesColor({34, 83, 237});
  } else if (sender_button == ui_->edges_purple) {
    ui_->OGLWindow->SetEdgesColor({95, 15, 162});
  } else if (sender_button == ui_->edges_white) {
    ui_->OGLWindow->SetEdgesColor({255, 255, 255});
  }
  qobject_cast<QPushButton*>(sender())->setStyleSheet(current_style + border);
  ui_->OGLWindow->update();
}

void Viewer::SetStandartEdgesButtonStyle() {
  QString start = "background-color:rgb(";
  QString end = ");border-radius:5px;";
  ui_->edges_red->setStyleSheet(start + "211,54,48" + end);
  ui_->edges_orange->setStyleSheet(start + "226,148,61" + end);
  ui_->edges_yellow->setStyleSheet(start + "242,216,77" + end);
  ui_->edges_green->setStyleSheet(start + "102,195,89" + end);
  ui_->edges_blue->setStyleSheet(start + "34,83,237" + end);
  ui_->edges_purple->setStyleSheet(start + "95,15,162" + end);
  ui_->edges_white->setStyleSheet(start + "255,255,255" + end);
}

void Viewer::ChangeTypeEdges() {
  ui_->OGLWindow->SetEdgesType(ui_->edges_type->currentIndex());
  ui_->OGLWindow->update();
}

void Viewer::ChangeThicknessEdges() {
  ui_->OGLWindow->SetEdgesThickness(ui_->edges_thickness->value());
  ui_->OGLWindow->update();
}

void Viewer::on_edges_reset_clicked() {
  QString s =
      "background-color:rgb(255,255,255);border-radius:5px;border:2px solid "
      "rgb(200, 249, 100);";
  SetStandartEdgesButtonStyle();
  ui_->edges_white->setStyleSheet(s);
  ui_->OGLWindow->SetEdgesColor({255, 255, 255});
  ui_->edges_type->setCurrentIndex(0);
  ui_->OGLWindow->SetEdgesType(0);
  ui_->edges_thickness->setValue(1);
  ui_->OGLWindow->SetEdgesThickness(1);
  ui_->OGLWindow->update();
}

void Viewer::ChangeColorVertices() {
  SetStandarVerticesButtonStyle();
  QObject* sender_button = sender();
  QString current_style = qobject_cast<QPushButton*>(sender())->styleSheet();
  QString border = "border:2px solid rgb(200, 249, 100);";
  if (sender_button == ui_->vertices_red) {
    ui_->OGLWindow->SetVerticesColor({211, 54, 48});
  } else if (sender_button == ui_->vertices_orange) {
    ui_->OGLWindow->SetVerticesColor({226, 148, 61});
  } else if (sender_button == ui_->vertices_yellow) {
    ui_->OGLWindow->SetVerticesColor({242, 216, 77});
  } else if (sender_button == ui_->vertices_green) {
    ui_->OGLWindow->SetVerticesColor({102, 195, 89});
  } else if (sender_button == ui_->vertices_blue) {
    ui_->OGLWindow->SetVerticesColor({34, 83, 237});
  } else if (sender_button == ui_->vertices_purple) {
    ui_->OGLWindow->SetVerticesColor({95, 15, 162});
  } else if (sender_button == ui_->vertices_white) {
    ui_->OGLWindow->SetVerticesColor({255, 255, 255});
  }
  qobject_cast<QPushButton*>(sender())->setStyleSheet(current_style + border);
  ui_->OGLWindow->update();
}

void Viewer::SetStandarVerticesButtonStyle() {
  QString start = "background-color:rgb(";
  QString end = ");border-radius:5px;";
  ui_->vertices_red->setStyleSheet(start + "211,54,48" + end);
  ui_->vertices_orange->setStyleSheet(start + "226,148,61" + end);
  ui_->vertices_yellow->setStyleSheet(start + "242,216,77" + end);
  ui_->vertices_green->setStyleSheet(start + "102,195,89" + end);
  ui_->vertices_blue->setStyleSheet(start + "34,83,237" + end);
  ui_->vertices_purple->setStyleSheet(start + "95,15,162" + end);
  ui_->vertices_white->setStyleSheet(start + "255,255,255" + end);
}

void Viewer::ChangeTypeVertices() {
  ui_->OGLWindow->SetVerticesType(ui_->vertices_type->currentIndex());
  ui_->OGLWindow->update();
}

void Viewer::ChangeThicknessVertices() {
  ui_->OGLWindow->SetVerticesSize(ui_->vertices_thickness->value());
  ui_->OGLWindow->update();
}

void Viewer::on_vertices_reset_clicked() {
  QString s =
      "background-color:rgb(255,255,255);border-radius:5px;border:2px solid "
      "rgb(200, 249, 100);";
  SetStandarVerticesButtonStyle();
  ui_->vertices_white->setStyleSheet(s);
  ui_->OGLWindow->SetVerticesColor({255, 255, 255});
  ui_->vertices_type->setCurrentIndex(0);
  ui_->OGLWindow->SetVerticesType(0);
  ui_->vertices_thickness->setValue(1);
  ui_->OGLWindow->SetVerticesSize(1);
  ui_->OGLWindow->update();
}

void Viewer::ChangeColorBackground() {
  SetStandarBackgroundButtonStyle();
  QObject* sender_button = sender();
  QString current_style = qobject_cast<QPushButton*>(sender())->styleSheet();
  QString border = "border:2px solid rgb(200, 249, 100);";
  QString green_border = "border:2px solid rgb(255, 255, 255);";
  if (sender_button == ui_->background_black) {
    ui_->OGLWindow->SetBackgroundColor({0, 0, 0});
  } else if (sender_button == ui_->background_blue) {
    ui_->OGLWindow->SetBackgroundColor({66, 66, 169});
  } else if (sender_button == ui_->background_dark_gray) {
    ui_->OGLWindow->SetBackgroundColor({27, 27, 27});
  } else if (sender_button == ui_->background_light_gray) {
    ui_->OGLWindow->SetBackgroundColor({102, 102, 102});
  } else if (sender_button == ui_->background_green) {
    ui_->OGLWindow->SetBackgroundColor({190, 249, 81});
  } else if (sender_button == ui_->background_pink) {
    ui_->OGLWindow->SetBackgroundColor({245, 215, 255});
  } else if (sender_button == ui_->background_white) {
    ui_->OGLWindow->SetBackgroundColor({255, 255, 255});
  }
  if (sender_button == ui_->background_green)
    qobject_cast<QPushButton*>(sender())->setStyleSheet(current_style +
                                                        green_border);
  else
    qobject_cast<QPushButton*>(sender())->setStyleSheet(current_style + border);
  ui_->OGLWindow->update();
}

void Viewer::SetStandarBackgroundButtonStyle() {
  QString start = "background-color:rgb(";
  QString end = ");border-radius:5px;";
  ui_->background_black->setStyleSheet(start + "0,0,0" + end);
  ui_->background_blue->setStyleSheet(start + "66,66,169" + end);
  ui_->background_dark_gray->setStyleSheet(start + "27,27,27" + end);
  ui_->background_light_gray->setStyleSheet(start + "102,102,102" + end);
  ui_->background_green->setStyleSheet(start + "190,249,81" + end);
  ui_->background_pink->setStyleSheet(start + "245,215,255" + end);
  ui_->background_white->setStyleSheet(start + "255,255,255" + end);
}

void Viewer::on_background_reset_clicked() {
  QString s =
      "background-color:rgb(27,27,27);border-radius:5px;border:2px solid "
      "rgb(200, 249, 100);";
  SetStandarBackgroundButtonStyle();
  ui_->background_dark_gray->setStyleSheet(s);
  ui_->OGLWindow->SetBackgroundColor({27, 27, 27});
  ui_->OGLWindow->update();
}

void Viewer::ChangeProjectionType() {
  ui_->OGLWindow->SetProjectionType(
      ui_->combo_box_projection_type->currentIndex());
  ui_->OGLWindow->update();
}

void Viewer::on_button_get_screenshot_clicked() {
  QPixmap screenshot = ui_->OGLWindow->grab();
  QString file_path = QFileDialog::getSaveFileName(
      this, "Save Screenshot", "screenshot", "JPEG (*.jpeg);;BMP (*.bmp)");
  if (!file_path.isEmpty()) {
    if (file_path.endsWith(".bmp"))
      screenshot.save(file_path, "BMP");
    else
      screenshot.save(file_path, "JPEG");
  }
}

void Viewer::on_button_get_gif_clicked() {
  QString file_path = QFileDialog::getSaveFileName(this, "Save Gif",
                                                   "animation", "GIF (*.gif)");
  if (!file_path.isEmpty()) {
    QImage img(ui_->OGLWindow->size(), QImage::Format_RGB32), img640_480;
    QPainter painter(&img);
    QTime timer;
    GifWriter gif;
    GifBegin(&gif, file_path.toLatin1(), 640, 480, 10);
    for (int i = 1, sec = 5; i <= 50; ++i) {
      if (i % 10 == 0)
        ui_->button_get_gif->setText(QString::number(sec--) + "s");
      ui_->OGLWindow->render(&painter);
      img640_480 = img.scaled(QSize(640, 480));
      GifWriteFrame(&gif, img640_480.bits(), 640, 480, 10);
      timer = QTime::currentTime().addMSecs(100);
      while (QTime::currentTime() < timer)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 10);
    }
    ui_->button_get_gif->setText("GIF");
    GifEnd(&gif);
    QMessageBox::information(this, "Gif ready", "Gif saved successfully.");
  }
}

void Viewer::SaveSettings() {
  s21::Settings current_settings = ui_->OGLWindow->GetSettings();
  settings_->setValue("settings", 1);
  settings_->setValue("edges_rgb_red", current_settings.edges_rgb.red);
  settings_->setValue("edges_rgb_green", current_settings.edges_rgb.green);
  settings_->setValue("edges_rgb_blue", current_settings.edges_rgb.blue);
  settings_->setValue("edges_type", current_settings.edges_type);
  settings_->setValue("edges_thickness", current_settings.edges_thickness);
  settings_->setValue("edges_red", ui_->edges_red->styleSheet());
  settings_->setValue("edges_orange", ui_->edges_orange->styleSheet());
  settings_->setValue("edges_yellow", ui_->edges_yellow->styleSheet());
  settings_->setValue("edges_green", ui_->edges_green->styleSheet());
  settings_->setValue("edges_blue", ui_->edges_blue->styleSheet());
  settings_->setValue("edges_purple", ui_->edges_purple->styleSheet());
  settings_->setValue("edges_white", ui_->edges_white->styleSheet());
  settings_->setValue("vertices_rgb_red", current_settings.vertices_rgb.red);
  settings_->setValue("vertices_rgb_green",
                      current_settings.vertices_rgb.green);
  settings_->setValue("vertices_rgb_blue", current_settings.vertices_rgb.blue);
  settings_->setValue("vertices_type", current_settings.vertices_type);
  settings_->setValue("vertices_size", current_settings.vertices_size);
  settings_->setValue("vertices_red", ui_->vertices_red->styleSheet());
  settings_->setValue("vertices_orange", ui_->vertices_orange->styleSheet());
  settings_->setValue("vertices_yellow", ui_->vertices_yellow->styleSheet());
  settings_->setValue("vertices_green", ui_->vertices_green->styleSheet());
  settings_->setValue("vertices_blue", ui_->vertices_blue->styleSheet());
  settings_->setValue("vertices_purple", ui_->vertices_purple->styleSheet());
  settings_->setValue("vertices_white", ui_->vertices_white->styleSheet());
  settings_->setValue("background_rgb_red",
                      current_settings.background_rgb.red);
  settings_->setValue("background_rgb_green",
                      current_settings.background_rgb.green);
  settings_->setValue("background_rgb_blue",
                      current_settings.background_rgb.blue);
  settings_->setValue("background_black", ui_->background_black->styleSheet());
  settings_->setValue("background_blue", ui_->background_blue->styleSheet());
  settings_->setValue("background_dark_gray",
                      ui_->background_dark_gray->styleSheet());
  settings_->setValue("background_light_gray",
                      ui_->background_light_gray->styleSheet());
  settings_->setValue("background_green", ui_->background_green->styleSheet());
  settings_->setValue("background_pink", ui_->background_pink->styleSheet());
  settings_->setValue("background_white", ui_->background_white->styleSheet());
  settings_->setValue("projection_type", current_settings.projection_type);
}

void Viewer::LoadSettings() {
  if (settings_->value("settings").toInt()) {
    s21::Settings s;
    s.edges_rgb.red = settings_->value("edges_rgb_red").toFloat() * 255;
    s.edges_rgb.green = settings_->value("edges_rgb_green").toFloat() * 255;
    s.edges_rgb.blue = settings_->value("edges_rgb_blue").toFloat() * 255;
    ui_->OGLWindow->SetEdgesColor(s.edges_rgb);
    ui_->edges_red->setStyleSheet(settings_->value("edges_red").toString());
    ui_->edges_orange->setStyleSheet(
        settings_->value("edges_orange").toString());
    ui_->edges_yellow->setStyleSheet(
        settings_->value("edges_yellow").toString());
    ui_->edges_green->setStyleSheet(settings_->value("edges_green").toString());
    ui_->edges_blue->setStyleSheet(settings_->value("edges_blue").toString());
    ui_->edges_purple->setStyleSheet(
        settings_->value("edges_purple").toString());
    ui_->edges_white->setStyleSheet(settings_->value("edges_white").toString());
    s.edges_type = settings_->value("edges_type").toInt();
    ui_->edges_type->setCurrentIndex(s.edges_type);
    s.edges_thickness = settings_->value("edges_thickness").toDouble();
    ui_->edges_thickness->setValue(s.edges_thickness);
    s.vertices_rgb.red = settings_->value("vertices_rgb_red").toFloat() * 255;
    s.vertices_rgb.green =
        settings_->value("vertices_rgb_green").toFloat() * 255;
    s.vertices_rgb.blue = settings_->value("vertices_rgb_blue").toFloat() * 255;
    ui_->OGLWindow->SetVerticesColor(s.vertices_rgb);
    ui_->vertices_red->setStyleSheet(
        settings_->value("vertices_red").toString());
    ui_->vertices_orange->setStyleSheet(
        settings_->value("vertices_orange").toString());
    ui_->vertices_yellow->setStyleSheet(
        settings_->value("vertices_yellow").toString());
    ui_->vertices_green->setStyleSheet(
        settings_->value("vertices_green").toString());
    ui_->vertices_blue->setStyleSheet(
        settings_->value("vertices_blue").toString());
    ui_->vertices_purple->setStyleSheet(
        settings_->value("vertices_purple").toString());
    ui_->vertices_white->setStyleSheet(
        settings_->value("vertices_white").toString());
    s.vertices_type = settings_->value("vertices_type").toInt();
    ui_->vertices_type->setCurrentIndex(s.vertices_type);
    s.vertices_size = settings_->value("vertices_size").toDouble();
    ui_->vertices_thickness->setValue(s.vertices_size);
    s.background_rgb.red =
        settings_->value("background_rgb_red").toFloat() * 255;
    s.background_rgb.green =
        settings_->value("background_rgb_green").toFloat() * 255;
    s.background_rgb.blue =
        settings_->value("background_rgb_blue").toFloat() * 255;
    ui_->OGLWindow->SetBackgroundColor(s.background_rgb);
    ui_->background_black->setStyleSheet(
        settings_->value("background_black").toString());
    ui_->background_blue->setStyleSheet(
        settings_->value("background_blue").toString());
    ui_->background_dark_gray->setStyleSheet(
        settings_->value("background_dark_gray").toString());
    ui_->background_light_gray->setStyleSheet(
        settings_->value("background_light_gray").toString());
    ui_->background_green->setStyleSheet(
        settings_->value("background_green").toString());
    ui_->background_pink->setStyleSheet(
        settings_->value("background_pink").toString());
    ui_->background_white->setStyleSheet(
        settings_->value("background_white").toString());
    s.projection_type = settings_->value("projection_type").toInt();
    ui_->combo_box_projection_type->setCurrentIndex(s.projection_type);
    ui_->OGLWindow->SetProjectionType(s.projection_type);
  }
}

void Viewer::SetStandartAffine() {
  ui_->slider_move_x->setValue(0);
  ui_->slider_move_y->setValue(0);
  ui_->slider_move_z->setValue(0);
  ui_->slider_rotate_x->setValue(0);
  ui_->slider_rotate_y->setValue(0);
  ui_->slider_rotate_z->setValue(0);
  ui_->slider_scale->setValue(50);
}

void Viewer::InitializeConnect() {
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
  connect(ui_->edges_red, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_orange, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_yellow, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_green, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_blue, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_purple, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_white, &QPushButton::clicked, this,
          &Viewer::ChangeColorEdges);
  connect(ui_->edges_type, &QComboBox::currentIndexChanged, this,
          &Viewer::ChangeTypeEdges);
  connect(ui_->edges_thickness, &QSlider::valueChanged, this,
          &Viewer::ChangeThicknessEdges);
  connect(ui_->vertices_red, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_orange, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_yellow, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_green, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_blue, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_purple, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_white, &QPushButton::clicked, this,
          &Viewer::ChangeColorVertices);
  connect(ui_->vertices_type, &QComboBox::currentIndexChanged, this,
          &Viewer::ChangeTypeVertices);
  connect(ui_->vertices_thickness, &QSlider::valueChanged, this,
          &Viewer::ChangeThicknessVertices);
  connect(ui_->background_black, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->background_blue, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->background_dark_gray, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->background_light_gray, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->background_green, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->background_pink, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->background_white, &QPushButton::clicked, this,
          &Viewer::ChangeColorBackground);
  connect(ui_->combo_box_projection_type,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &Viewer::ChangeProjectionType);
}
