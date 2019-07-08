#include <QApplication>
#include <QStyle>
#include <QScreen>

#include "mainwindow.h"
#include "container.h"
#include "deepptr.h"
#include "nvdattack.h"
#include "nvddefense.h"
#include "nvdmaster.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setGeometry(
      QStyle::alignedRect(
          Qt::LeftToRight,
          Qt::AlignCenter,
          w.sizeHint(),
          QGuiApplication::screens().first()->geometry()
      )
  );
  w.show();

  return a.exec();
}
