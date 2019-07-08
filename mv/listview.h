#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>
#include <QMouseEvent>

class ListView : public QListView
{
public:
  ListView(QWidget *parent = nullptr);
  QSize sizeHint() const;
  void mousePressEvent(QMouseEvent*);
};

#endif // LISTVIEW_H
