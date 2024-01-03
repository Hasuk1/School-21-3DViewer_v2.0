#ifndef CPP4_3DVIEWER_V2_SRC_VIEWER_H_
#define CPP4_3DVIEWER_V2_SRC_VIEWER_H_

#include <QFileInfo>
#include <QMainWindow>
#include <QSettings>

#include "ui_viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Viewer;
}
QT_END_NAMESPACE

class Viewer : public QMainWindow {
  Q_OBJECT

 public:
  Viewer(QWidget *parent = nullptr);
  ~Viewer();

 private:
  void SaveSettings();
  void LoadSettings();
  void SetLoadedSettings(s21::Settings settings);

  void ChangeColorEdges();
  void ChangeProjectionType();

  void InitializeConnect();

  Ui::Viewer *ui_;
  QSettings *settings_;

 private slots:
  void on_open_obj_file_clicked();
  void on_render_obj_file_clicked();
  void on_close_object_clicked();
  void Transform(int value);
};
#endif  // CPP4_3DVIEWER_V2_SRC_VIEWER_H_
