#include <QApplication>

#include "QClass/controller.h"

int main(int argc, char *argv[]) {
//  setenv("LC_NUMERIC", "en_US.UTF-8", 1);
  QApplication app(argc, argv);
  s21::Controller window;
  window.show();
  return app.exec();
}
