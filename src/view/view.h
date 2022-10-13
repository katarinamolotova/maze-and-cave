#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QColor>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPainter>
#include <QTextStream>
#include <QTimer>
#include <QValidator>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class view;
}
QT_END_NAMESPACE

class view : public QMainWindow {
  Q_OBJECT

 public:
  explicit view(QWidget *parent = nullptr);
  ~view() override;

 private:
  Ui::view *ui_;

  bool openFile();
  void drawCave();
  void drawMaze();
  void drawWay(bool isClear);
  void change_visible_check_box(bool visible);
  void change_visible_radio_button(bool visible);
  void startSettings();
  void nonStepMode();
  void stopTimer();
  QString getFileName();
  static void writeSizeInFile(int cols, int rows, const QString &file_name);
  void writeMatrixInFile(const QString &file_name, int flag);
  void setMaxPoint(int x_max, int y_max);

  std::string file_;
  s21::Controller *controller;
  QGraphicsScene *scene_{};
  QPen *pen_{};
  QTimer *timer_ = nullptr;
  int x_start_way = 50;
  int y_start_way = 50;

 private slots:
  void on_generation_maze_clicked();
  void on_generation_cave_clicked();
  void on_download_maze_clicked();
  void on_download_cave_clicked();
  void on_checkBox_clicked();
  void on_radioButton_2_clicked();
  void on_radioButton_clicked();
  void on_save_maze_clicked();
  void on_save_cave_clicked();
  void on_next_step_clicked();
  void on_start_clicked();
  void on_tabWidget_currentChanged(int index);
  void on_maze_way_clicked();
};
#endif  // SRC_VIEW_VIEW_H_
