#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QCursor>
#include "MainWindow.h"
//QListWidget для списка из QString
#include <QCursor>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
