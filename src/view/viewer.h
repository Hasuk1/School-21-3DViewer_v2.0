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
  void ChangeColorEdges();
  void SetStandartEdgesButtonStyle();
  void ChangeTypeEdges();
  void ChangeThicknessEdges();
  void ChangeColorVertices();
  void SetStandarVerticesButtonStyle();
  void ChangeTypeVertices();
  void ChangeThicknessVertices();
  void ChangeColorBackground();
  void SetStandarBackgroundButtonStyle();
  void ChangeProjectionType();
  void SetStandartAffine();
  void InitializeConnect();

  Ui::Viewer *ui_;
  QSettings *settings_;

 private slots:
  void Transform(int value);
  void on_open_obj_file_clicked();
  void on_render_obj_file_clicked();
  void on_button_close_object_clicked();
  void on_edges_reset_clicked();
  void on_vertices_reset_clicked();
  void on_background_reset_clicked();
  void on_button_get_screenshot_clicked();
  void on_button_get_gif_clicked();
};
#endif  // CPP4_3DVIEWER_V2_SRC_VIEWER_H_
