#include "viewer.h"

#include <QFileInfo>

#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui_(new Ui::Viewer) {
  ui_->setupUi(this);
}

Viewer::~Viewer() { delete ui_; }

void Viewer::on_open_obj_file_clicked() {
  QString path_to_file = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), QDir::rootPath(), tr("Obj Files (*.obj)"));
  ui_->path_to_obj_file->setText(path_to_file);
}

void Viewer::on_render_obj_file_clicked() {
  if (QFile::exists(ui_->path_to_obj_file->text())) {
    QString current_open_file_name = ui_->objName->text();
    QFileInfo file_info(ui_->path_to_obj_file->text());
    QString file_name_to_render = file_info.fileName();
    if (current_open_file_name != file_name_to_render) {
      ui_->OGLWindow->ParseFile(ui_->path_to_obj_file->text());
      ui_->objName->setText(file_name_to_render);
      ui_->edgesCount->setText(ui_->OGLWindow->GetEdgeAmount());
      ui_->veticesCount->setText(ui_->OGLWindow->GetVertexAmount());
    }
  } else {
    QMessageBox::information(this, "ERROR", "Enter a path to file correctly");
    ui_->veticesCount->setText("");
    ui_->edgesCount->setText("");
    ui_->objName->setText("");
  }
}
