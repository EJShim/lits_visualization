#include <QApplication>
#include "E_Window.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  E_Window mainwindow;
  mainwindow.show();

  return app.exec();
}