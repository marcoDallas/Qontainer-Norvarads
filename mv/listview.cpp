#include "listview.h"

ListView::ListView(QWidget *parent) : QListView (parent)
{
  setSelectionMode(QAbstractItemView::SingleSelection);
}

QSize ListView::sizeHint() const
{
  return (QSize(700, 500));
}

void ListView::mousePressEvent(QMouseEvent* event) {
   if (!indexAt(event->pos()).isValid()) {
      clearSelection();
      selectionModel()->clearCurrentIndex();
  }

   QListView::mousePressEvent(event);
}
