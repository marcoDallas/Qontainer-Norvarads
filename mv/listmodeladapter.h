#ifndef LISTMODELADAPTER_H
#define LISTMODELADAPTER_H

#include "model.h"
#include "deepptr.h"

#include <QAbstractListModel>
#include <QPixmap>
#include <QPalette>

class ListModelAdapter : public QAbstractListModel
{
private:
    Model* model;
    DeepPtr<Norvarad> itemToInsert;

public:
  ListModelAdapter(QObject* parent = nullptr);
  ~ListModelAdapter();

  int rowCount(const QModelIndex& = QModelIndex()) const;
  QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex&, const QVariant&, int);

  Qt::ItemFlags flags(const QModelIndex&) const;

  void setupInsert(const Norvarad&);
  bool insertRows(int, int = 1, const QModelIndex& = QModelIndex());
  bool removeRows(int, int = 1, const QModelIndex& = QModelIndex());
  double performAttack(const QModelIndex &);
  double performDefense(const QModelIndex &, double);
  bool search(unsigned int, const QRegExp&, double, const QString&) const;

  bool doSaveToFile(const QString&) const;
  void doLoadFromFile(const QString&);
};

#endif // LISTMODELADAPTER_H
