#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centralwidget.h"

#include <QMainWindow>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;
  QSize sizeHint() const;

public slots:
  void aboutDialog() const;
};

#endif // MAINWINDOW_H
