#ifndef NVDACONFUSED_H
#define NVDACONFUSED_H

#include "nvdattack.h"

class NvdAConfused : public NvdAttack
{
private:
  const static double healthMalusValue;
  const static double confusedValueBoost;

public:
  explicit NvdAConfused(double h = 0, std::string n = "", double a = 0, double dt = 0);

  std::string printDescription() const;
  std::string getType() const;
  NvdAConfused* clone() const;
  double getValue() const;
  double makeAttack();
  void toXml(QXmlStreamWriter& writer) const;
};

#endif // NVDACONFUSED_H
