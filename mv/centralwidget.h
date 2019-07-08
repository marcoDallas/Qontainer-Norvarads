#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "listview.h"
#include "listmodeladapter.h"
#include "proxymodeladapter.h"
#include "insertview.h"

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>

class CentralWidget : public QWidget
{
  Q_OBJECT

private:
  ListView* list;
  ListModelAdapter* adapter;
  ProxyModelAdapter* proxy;
  QComboBox* insType;
  QDoubleSpinBox* actionValue;
  QLineEdit* searchInput;
  QComboBox* searchFilters;
  QDoubleValidator* doubleValidator;

public:
  explicit CentralWidget(QWidget *parent = nullptr);
  ~CentralWidget() = default;
  QSize sizeHint() const;

public slots:
  void removeNorvarad();
  void insert();
  void simulateAttack();
  void simulateDefense();
  void textFilterChanged();
  void saveAction();
  void loadAction();
};

#endif // CENTRALWIDGET_H
