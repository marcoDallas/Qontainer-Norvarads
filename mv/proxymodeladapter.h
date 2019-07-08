#ifndef PROXYMODELADAPTER_H
#define PROXYMODELADAPTER_H

#include "listmodeladapter.h"

#include <QComboBox>
#include <QSortFilterProxyModel>

class ProxyModelAdapter : public QSortFilterProxyModel
{
private:
  double value;
  const QComboBox* filters;

protected:
  bool filterAcceptsRow(int, const QModelIndex&) const;

public:
  ProxyModelAdapter(QObject* = nullptr, const QComboBox* = nullptr);

  void setFilterValue(double);
  bool insertRows(int, int = 1, const QModelIndex& = QModelIndex());
};

#endif // PROXYMODELADAPTER_H
