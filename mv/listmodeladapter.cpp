#include "listmodeladapter.h"

ListModelAdapter::ListModelAdapter(QObject* parent) :
  QAbstractListModel(parent),
  model(new Model()) {}

ListModelAdapter::~ListModelAdapter()
{
  delete model;
}

int ListModelAdapter::rowCount(const QModelIndex &) const
{
  return model->itemsCount();
}

QVariant ListModelAdapter::data(const QModelIndex& index, int role) const
{
  if (!index.isValid() || index.row() >= model->itemsCount())
    return QVariant();

  switch (role)
  {
  case Qt::DisplayRole:
  {
    return QString::fromStdString(model->getNorvarad(static_cast<unsigned int>(index.row())).printDescription());
  }

  case Qt::EditRole:
  {
    return QString::fromStdString(model->getNorvarad(static_cast<unsigned int>(index.row())).getName());
  }

  case Qt::BackgroundRole:
  {
    if (index.row() % 2)
    {
      return QBrush(QColor(203,234,239,75));
    }
    else
    {
      return QBrush(QColor(184,214,219,75));
    }
  }

  case Qt::DecorationRole:
  {
    Norvarad* aux = &(model->getNorvarad(static_cast<unsigned int>(index.row())));

    QPixmap img;
    if (!(aux->isAlive()))
    {
      img = QPixmap(":/img/grave.png");
    }
    else if (dynamic_cast<NvdMaster*>(aux))
    {
      img = QPixmap(":/img/master.png");
    }
    else if (dynamic_cast<NvdDEvo*>(aux))
    {
      img = QPixmap(":/img/evo.png");
    }
    else if (dynamic_cast<NvdAConfused*>(aux))
    {
      img = QPixmap(":/img/confused.png");
    }
    else if (dynamic_cast<NvdDefense*>(aux))
    {
      img = QPixmap(":/img/defense.png");
    }
    else if (dynamic_cast<NvdAttack*>(aux))
    {
      img = QPixmap(":/img/attack.png");
    }
    img = img.scaledToHeight(200, Qt::FastTransformation);
    return img;
  }

  default :
    break;
  }

  return QVariant();
}

bool ListModelAdapter::setData(const QModelIndex& index, const QVariant& value, int role)
{
  if (!index.isValid() && role != Qt::EditRole)
    return false;

  model->updateName(static_cast<unsigned int>(index.row()), value.toString().toStdString());

  emit dataChanged(index, index);

  return true;
}

Qt::ItemFlags ListModelAdapter::flags(const QModelIndex & index) const
{
  if (!index.isValid())
    return Qt::ItemIsEnabled;

  return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void ListModelAdapter::setupInsert(const Norvarad& norv)
{
  itemToInsert = &norv;
}

bool ListModelAdapter::insertRows(int begin, int count, const QModelIndex& parent)
{
  beginInsertRows(parent, begin, begin + count - 1);
  model->add(&(*itemToInsert));
  endInsertRows();
  return true;
}

bool ListModelAdapter::removeRows(int begin, int count, const QModelIndex& parent)
{
  beginRemoveRows(parent, begin, begin + count - 1);
  model->remove(static_cast<unsigned int>(begin));
  endRemoveRows();
  return true;
}

double ListModelAdapter::performAttack(const QModelIndex & index)
{
  double aux = model->doAttack(static_cast<unsigned int>(index.row()));
  return aux;
}

double ListModelAdapter::performDefense(const QModelIndex & index, double d)
{
  double aux = model->doDefense(static_cast<unsigned int>(index.row()),d);
  return aux;
}

bool ListModelAdapter::search(unsigned int i, const QRegExp& re, double val, const QString& data) const
{
  if (data == Model::searchName || data == Model::searchType)
  {
    return model->searchString(i,re,data);
  }
  else if(data == Model::searchValueMajor)
  {
    return model->searchValue(i,val,true);
  }
  else if (data == Model::searchValueMinor)
  {
    return model->searchValue(i,val,false);
  }
  return false;
}

bool ListModelAdapter::doSaveToFile(const QString& fileName) const
{
  return model->saveToFile(fileName);
}

void ListModelAdapter::doLoadFromFile(const QString& fileName)
{
  beginResetModel();
  model->loadFromFile(fileName);
  endResetModel();
}
