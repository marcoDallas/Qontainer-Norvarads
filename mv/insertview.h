#ifndef INSERTVIEW_H
#define INSERTVIEW_H

#include "listview.h"
#include "listmodeladapter.h"
#include "proxymodeladapter.h"

#include <QDialog>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QDialogButtonBox>

class InsertView : public QDialog
{
  Q_OBJECT

private:
  static const double MAX_HEALTH_VALUE;
  static const double MAX_ATTACK_VALUE;
  static const int MAX_ARMOR_VALUE;
  ListView* list;
  ListModelAdapter* adapter;
  ProxyModelAdapter* proxy;
  QString type;
  QLineEdit* nameLine;
  QDoubleSpinBox* healthLine;
  QSpinBox* armorLine;
  QDoubleSpinBox* attackLine;


public:
  InsertView(QWidget * parent = nullptr, QString option = nullptr, ListView* list = nullptr,
             ListModelAdapter* adapter = nullptr, ProxyModelAdapter* proxy = nullptr);
  const static QString DEFENSE;
  const static QString ATTACK;
  const static QString MASTER;
  const static QString EVOLUTION;
  const static QString CONFUSED;

public slots:
  void accept();
};

#endif // INSERTVIEW_H
