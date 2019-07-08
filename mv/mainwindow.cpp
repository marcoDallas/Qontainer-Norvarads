#include "mainwindow.h"

#include <QMenuBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  setWindowTitle("Qontainer - Norvarads");
  setWindowIcon(QIcon(":/icons/favicon.ico"));

  QMenu* fileMenu;
  QMenu* helpMenu;
  QAction* loadAction = new QAction("Open", this);
  loadAction->setShortcuts(QKeySequence::Open);
  loadAction->setStatusTip("Load data from file");
  QAction* saveAction = new QAction("Save", this);
  saveAction->setShortcuts(QKeySequence::Save);
  saveAction->setStatusTip("Save data to file");
  QAction* exitAction = new QAction("Quit", this);
  exitAction->setShortcuts(QKeySequence::Quit);
  exitAction->setStatusTip("Close application");
  QAction* helpAction = new QAction("About", this);
  helpAction->setShortcuts(QKeySequence::WhatsThis);
  helpAction->setStatusTip("General info");
  fileMenu = menuBar()->addMenu("File");
  helpMenu = menuBar()->addMenu("Help");
  fileMenu->addAction(loadAction);
  fileMenu->addAction(saveAction);
  fileMenu->addAction(exitAction);
  helpMenu->addAction(helpAction);

  statusBar()->showMessage("Ready");

  // the main content will go inside the central widget
  CentralWidget* cw = new CentralWidget(this);
  setCentralWidget(cw);

  // add connects
  connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
  connect(helpAction, SIGNAL(triggered()), this, SLOT(aboutDialog()));
  connect(saveAction, SIGNAL(triggered()), cw, SLOT(saveAction()));
  connect(loadAction, SIGNAL(triggered()), cw, SLOT(loadAction()));
}

QSize MainWindow::sizeHint() const
{
  return (QSize(850, 500));
}

void MainWindow::aboutDialog() const
{
  QMessageBox msgBox; // don't need parent because it's in stack
  std::ostringstream oss;
  oss << "Progetto programmazione ad oggetti 2018/2019 \n";
  oss << "Studente: Marco Dalla Libera \n";
  msgBox.setText(QString::fromStdString(oss.str()));

  QPixmap img(":/img/base.png");
  img = img.scaled(100,100, Qt::KeepAspectRatio);
  msgBox.setIconPixmap(img);
  msgBox.setWindowTitle("About");
  msgBox.exec();
}
