#include "viewer.h"

#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
}

Viewer::~Viewer() { delete ui; }

void Viewer::on_open_obj_file_clicked() {
  QString rootPath = QDir::rootPath();
  QString QString_filename = QFileDialog::getOpenFileName(
      this, tr("Open .obj file:"), rootPath, tr("Obj Files (*.obj)"));
  ui->pathToObjFile->setText(QString_filename);
}

void Viewer::on_render_obj_file_clicked() {
  QString fileNameStr = ui->pathToObjFile->text();
  QByteArray fileNameUtf8 = fileNameStr.toUtf8();
  char *fileName = fileNameUtf8.data();
  if (QFile::exists(fileName)) {
    ui->OGLWindow->parse_file(fileName);
  } else {
    QMessageBox::information(this, "ERROR", "Enter a path to file correctly");
    ui->veticesCount->setText("");
    ui->edgesCount->setText("");
    ui->objName->setText("");
  }
}
