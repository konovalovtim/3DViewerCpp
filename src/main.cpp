#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow window;
  window.setWindowTitle("3D_Viewer_v2.0");
  window.show();
  return app.exec();
}
