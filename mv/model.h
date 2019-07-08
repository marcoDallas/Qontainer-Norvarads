#ifndef MODEL_H
#define MODEL_H

#include "container.h"
#include "deepptr.h"

#include "xmlutil.h"

#include "norvarad.h"
#include "nvdaconfused.h"
#include "nvdattack.h"
#include "nvddefense.h"
#include "nvddevo.h"
#include "nvdmaster.h"

#include <QRegExp>
#include <QString>

class Model
{
private:
  Container<DeepPtr<Norvarad>> cont;

public:
  Model();
  ~Model();

  bool saveToFile(const QString&) const;
  void loadFromFile(const QString&);

  int itemsCount() const;
  Norvarad& getNorvarad(unsigned int) const;
  void add(Norvarad*);
  void remove(unsigned int);
  void remove(Norvarad*);
  void updateName(unsigned int, std::string);
  double doAttack(unsigned int);
  double doDefense(unsigned int, double);
  bool searchString(unsigned int i, const QRegExp&, const QString&) const;
  bool searchValue(unsigned int, double, bool) const;

  const static QString searchValueMajor;
  const static QString searchValueMinor;
  const static QString searchName;
  const static QString searchType;
};

#endif // MODEL_H
