#ifndef XMLUTIL_H
#define XMLUTIL_H

#include <QString>
#include <QSaveFile>
#include <QFile>

#include "container.h"
#include "deepptr.h"
#include "norvarad.h"
#include "nvddefense.h"
#include "nvdattack.h"
#include "nvdmaster.h"
#include "nvddevo.h"
#include "nvdaconfused.h"

class XmlUtil
{
private:
  const static QString startKeyword;

public:
  XmlUtil();
  ~XmlUtil() = default;

  Container<DeepPtr<Norvarad>> load(const QString&) const;
  bool save(const QString&, const Container<DeepPtr<Norvarad>>&) const;
};

#endif // XMLUTIL_H
