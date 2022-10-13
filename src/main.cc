#include <QApplication>

#include "view/view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  view w;
  w.show();
  return QApplication::exec();
}
