#ifndef CPP4_3DVIEWER_V2_SRC_VIEWER_H_
#define CPP4_3DVIEWER_V2_SRC_VIEWER_H_

#include <QMainWindow>

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
  Ui::Viewer *ui_;

 private slots:
  void on_open_obj_file_clicked();
  void on_render_obj_file_clicked();
  void MoveModelX(int value);
  void MoveModelY(int value);
};
#endif  // CPP4_3DVIEWER_V2_SRC_VIEWER_H_
