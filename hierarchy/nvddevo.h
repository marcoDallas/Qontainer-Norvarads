#ifndef NVDDEVO_H
#define NVDDEVO_H

#include "nvddefense.h"

/**
 * @brief The NvdDEvo class for each attack taken the armor gets stronger
 */
class NvdDEvo : public NvdDefense
{
private:
  const static double armorIncrementValue;
  const static double evoValueBoost;

public:
  explicit NvdDEvo(double h = 0, std::string n = "", percentage a = 0, double dt = 0);

  std::string printDescription() const;
  std::string getType() const;
  NvdDEvo* clone() const;
  double getValue() const;
  double takeDamage(double);
  void toXml(QXmlStreamWriter& writer) const;
};

#endif // NVDDEVO_H
