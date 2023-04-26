#include <QApplication>

#include "controller/controller.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  s21::Controller window;
  window.show();
  return app.exec();
}
