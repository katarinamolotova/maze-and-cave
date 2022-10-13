#include "view.h"

#include "ui_view.h"

view::view(QWidget* parent) : QMainWindow(parent), ui_(new Ui::view) {
  ui_->setupUi(this);
  startSettings();
  controller = s21::Controller::GetInstance();
}

view::~view() {
  delete scene_;
  delete pen_;
  delete ui_;
}

bool view::openFile() {
  QString fileTmp = QFileDialog::getOpenFileName(
      this, tr("Open file"), QCoreApplication::applicationDirPath(),
      tr("*.txt"));
  file_ = fileTmp.toStdString();
  return (fileTmp != nullptr);
}

void view::on_download_maze_clicked() {
  if (openFile()) {
    controller->ReadMaze(file_);
    drawMaze();
    setMaxPoint(controller->GetColsMaze() - 1, controller->GetRowsMaze() - 1);
  }
}

void view::on_download_cave_clicked() {
  if (openFile()) {
    int limit_dead = ui_->limit_dead->text().toInt();
    int limit_life = ui_->limit_life->text().toInt();
    controller->ReadCave(file_, {limit_dead, limit_life});
    nonStepMode();
    drawCave();
  }
}

void view::on_generation_cave_clicked() {
  int rows = ui_->rows_cave->currentText().toInt();
  int cols = ui_->cols_cave->currentText().toInt();
  int limit_dead = ui_->limit_dead->text().toInt();
  int limit_life = ui_->limit_life->text().toInt();
  controller->GenerationCave(rows, cols, {limit_dead, limit_life});
  nonStepMode();
  drawCave();
}

void view::nonStepMode() {
  if (!ui_->checkBox->isChecked()) {
    while (!controller->GetFlagEnd()) controller->UpdateCave();
  }
}

void view::on_start_clicked() {
  timer_ = new QTimer();
  connect(timer_, SIGNAL(timeout()), this, SLOT(on_next_step_clicked()));
  timer_->start(ui_->miliseconds->text().toInt());
}

void view::stopTimer() {
  if (timer_ != nullptr && controller->GetFlagEnd()) {
    timer_->stop();
    timer_ = nullptr;
  }
}

void view::on_next_step_clicked() {
  if (!controller->GetFlagEnd()) {
    controller->UpdateCave();
    drawCave();
  }
  stopTimer();
}

void view::on_generation_maze_clicked() {
  int rows = ui_->rows_maze->currentText().toInt();
  int cols = ui_->cols_maze->currentText().toInt();
  controller->GenerateMaze(rows, cols);
  drawMaze();
  setMaxPoint(controller->GetColsMaze() - 1, controller->GetRowsMaze() - 1);
}

void view::setMaxPoint(int x_max, int y_max) {
  ui_->y_start->setMaximum(y_max);
  ui_->y_finish->setMaximum(y_max);
  ui_->x_start->setMaximum(x_max);
  ui_->x_finish->setMaximum(x_max);
}

void view::on_maze_way_clicked() {
  if (controller->GetColsMaze()) {
    pen_->setColor(QColor("#FFFFFF"));
    if (x_start_way < 50) drawWay(true);
    int row_start = ui_->y_start->text().toInt();
    int col_start = ui_->x_start->text().toInt();
    int row_end = ui_->y_finish->text().toInt();
    int col_end = ui_->x_finish->text().toInt();
    controller->CreateMazeWay({row_start, col_start}, {row_end, col_end});
    x_start_way = ui_->x_start->text().toInt();
    y_start_way = ui_->y_start->text().toInt();
    pen_->setColor(QColor("#FF0000"));
    drawWay(false);
  }
}

void view::drawCave() {
  scene_->clear();
  int px_x = 0, px_y = 0;
  int step_x = 500 / controller->GetColsCave();
  int step_y = 500 / controller->GetRowsCave();

  for (int i = 0; i < controller->GetRowsCave(); i++) {
    for (int j = 0; j < controller->GetColsCave(); j++) {
      if (controller->GetCave(i, j))
        scene_->addRect(px_x, px_y, step_x, step_y, *pen_, QColor("#000000"));
      px_x += step_x;
    }
    px_x = 0;
    px_y += step_y;
  }
}

void view::drawMaze() {
  scene_->clear();
  int px_x = 0, px_y = 0;
  int step_x = 500 / controller->GetColsMaze();
  int step_y = 500 / controller->GetRowsMaze();

  for (int i = 0; i < controller->GetRowsMaze(); i++) {
    for (int j = 0; j < controller->GetColsMaze(); j++) {
      std::pair<bool, bool> wall = controller->GetMazeBorders(i, j);
      if (wall.first)
        scene_->addLine(px_x + step_x, px_y, px_x + step_x, px_y + step_y,
                        *pen_);
      if (wall.second)
        scene_->addLine(px_x, px_y + step_y, px_x + step_x, px_y + step_y,
                        *pen_);
      px_x += step_x;
    }
    px_x = 0;
    px_y += step_y;
  }

  pen_->setColor(QColor("#FF0000"));
  scene_->addRect(0, 0, 499, 499, *pen_);
  pen_->setColor(QColor("#000000"));
}

void view::drawWay(bool isClear) {
  int step_x = 500 / controller->GetColsMaze();
  int step_y = 500 / controller->GetRowsMaze();
  int px_x = (isClear ? x_start_way : ui_->x_start->text().toInt()) * step_x +
             step_x / 2;
  int px_y = (isClear ? y_start_way : ui_->y_start->text().toInt()) * step_y +
             step_y / 2;

  std::vector<s21::Direction> way = controller->GetMazeWay();
  for (auto& direction : way) {
    if (direction == s21::LEFT) {
      scene_->addLine(px_x, px_y, px_x - step_x, px_y, *pen_);
      px_x -= step_x;
    } else if (direction == s21::RIGHT) {
      scene_->addLine(px_x, px_y, px_x + step_x, px_y, *pen_);
      px_x += step_x;
    } else if (direction == s21::UP) {
      scene_->addLine(px_x, px_y, px_x, px_y - step_y, *pen_);
      px_y -= step_y;
    } else {
      scene_->addLine(px_x, px_y, px_x, px_y + step_y, *pen_);
      px_y += step_y;
    }
  }
  pen_->setColor(QColor("#000000"));
}

void view::on_tabWidget_currentChanged(int index) {
  if (controller->GetColsCave() != 0 && index == 1)
    drawCave();
  else if (controller->GetColsMaze() != 0 && index == 0)
    drawMaze();
  else
    scene_->clear();
}

void view::on_checkBox_clicked() {
  change_visible_check_box(ui_->checkBox->isChecked());
}

void view::change_visible_check_box(bool visible) {
  if (ui_->radioButton->isChecked()) {
    ui_->next_step->setVisible(visible);
  } else {
    ui_->label->setVisible(visible);
    ui_->miliseconds->setVisible(visible);
    ui_->start->setVisible(visible);
  }
  ui_->radioButton->setVisible(visible);
  ui_->radioButton_2->setVisible(visible);
}

void view::on_radioButton_2_clicked() { change_visible_radio_button(false); }

void view::on_radioButton_clicked() { change_visible_radio_button(true); }

void view::change_visible_radio_button(bool visible) {
  ui_->next_step->setVisible(visible);
  ui_->miliseconds->setVisible(!visible);
  ui_->label->setVisible(!visible);
  ui_->start->setVisible(!visible);
}

void view::on_save_maze_clicked() {
  QString file_name = getFileName();
  writeSizeInFile(controller->GetColsMaze(), controller->GetRowsMaze(),
                  file_name);
  writeMatrixInFile(file_name, 1);
  writeMatrixInFile(file_name, 2);
}

void view::on_save_cave_clicked() {
  QString file_name = getFileName();
  writeSizeInFile(controller->GetColsCave(), controller->GetRowsCave(),
                  file_name);
  writeMatrixInFile(file_name, 0);
}

QString view::getFileName() {
  QFileDialog dialog;
  QString file_name =
      QFileDialog::getSaveFileName(this, tr("Save as"), "", tr("*.txt"));
  return file_name;
}

void view::writeSizeInFile(int cols, int rows, const QString& file_name) {
  QFile file(file_name);
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&file);
    out << cols << " " << rows << "\n";
    file.close();
  }
}

void view::writeMatrixInFile(const QString& file_name, int flag) {
  int rows = (!flag) ? controller->GetRowsCave() : controller->GetRowsMaze();
  int cols = (!flag) ? controller->GetColsCave() : controller->GetColsMaze();
  QFile file(file_name);
  if (file.open(QIODevice::Append | QIODevice::Text)) {
    QTextStream out(&file);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        bool cell = (!flag)       ? controller->GetCave(i, j)
                    : (flag == 1) ? controller->GetMazeBorders(i, j).first
                                  : controller->GetMazeBorders(i, j).second;
        out << QString::number(cell) << " ";
      }
      out << "\n";
    }
    out << "\n";
    file.close();
  }
}

void view::startSettings() {
  ui_->miliseconds->setVisible(false);
  ui_->label->setVisible(false);
  ui_->start->setVisible(false);

  scene_ = new QGraphicsScene();
  ui_->graphicsView->setScene(scene_);
  pen_ = new QPen();
  pen_->setWidth(2);

  ui_->graphicsView->centerOn(0, 0);
  scene_->setSceneRect(0, 0, 498, 498);

  ui_->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui_->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scene_->setBackgroundBrush(QColor("#FFFFFF"));
}
