#include "model.h"

const QString Model::searchValueMajor = "Value >=";
const QString Model::searchValueMinor = "Value <=";
const QString Model::searchName = "Name";
const QString Model::searchType = "Type";

Model::Model() { }

Model::~Model()
{
  cont.clear();
}

bool Model::saveToFile(const QString& fileName) const
{
  XmlUtil xu;
  return xu.save(fileName, cont);
}

void Model::loadFromFile(const QString& fileName)
{
  XmlUtil xu;
  cont = xu.load(fileName);
}

int Model::itemsCount() const
{
  return cont.getSize();
}

Norvarad& Model::getNorvarad(unsigned int i) const
{
  return **(cont.begin() + i);
}

void Model::add(Norvarad* nvd)
{
  cont.push_back(nvd);
}

void Model::remove(unsigned int i)
{
  cont.erase(cont.begin() + i);
}

void Model::remove(Norvarad* n)
{
  cont.remove(n);
}

void Model::updateName(unsigned int i, std::string n)
{
  (*(cont.begin() + i))->setName(n);
}

double Model::doAttack(unsigned int i)
{
  return (*(cont.begin() + i))->makeAttack();
}

double Model::doDefense(unsigned int i, double d)
{
  return (*(cont.begin() + i))->takeDamage(d);
}

bool Model::searchString(unsigned int i, const QRegExp& re, const QString& data) const
{
  if (data == searchName)
  {
    return (QString::fromStdString((*(cont.begin() + i))->getName()).contains(re));
  }
  else if (data == searchType)
  {
    return (QString::fromStdString((*(cont.begin() + i))->getType()).contains(re));
  }

  return false;
}

bool Model::searchValue(unsigned int i, double value, bool major) const
{
  if (major)
  {
    if ( (*(cont.begin() + i))->getValue() >= value )
      return true;
  }
  else
  {
    if ( (*(cont.begin() + i))->getValue() <= value )
      return true;
  }

  return false;
}
