#include "proxymodeladapter.h"

ProxyModelAdapter::ProxyModelAdapter(QObject* parent, const QComboBox* f) : QSortFilterProxyModel (parent), filters(f) { }

void ProxyModelAdapter::setFilterValue(double d)
{
  value = d;
}

bool ProxyModelAdapter::insertRows(int begin, int count, const QModelIndex& parent)
{
  bool result = sourceModel()->insertRows(begin, count, parent);
  invalidateFilter();
  return result;
}

bool ProxyModelAdapter::filterAcceptsRow(int row_source, const QModelIndex&) const
{
  return (static_cast<const ListModelAdapter*>(sourceModel())->search(static_cast<unsigned int>(row_source), filterRegExp(), value, filters->currentText()));
}

