#ifndef VIEWER_H
#define VIEWER_H

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

 private slots:
  void on_open_obj_file_clicked();

  void on_render_obj_file_clicked();

 private:
  Ui::Viewer *ui;
};
#endif  // VIEWER_H
