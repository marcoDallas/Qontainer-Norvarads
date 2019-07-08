#ifndef NVDDEFENSE_H
#define NVDDEFENSE_H

#include "norvarad.h"

class NvdDefense : virtual public Norvarad
{
private:
  percentage armorLevel;
  const static double armorValueBoost;
  const static percentage armorCap;

protected:
  void incrementArmorLevel(percentage);

public:
  explicit NvdDefense(double h = 0, std::string n = "", percentage a = 0, double dt = 0);

  std::string printDescription() const;
  std::string getType() const;
  double getAttackPower() const;
  NvdDefense* clone() const;
  double getValue() const;
  percentage getArmor() const;
  double takeDamage(double);
  double makeAttack();
  void toXml(QXmlStreamWriter& writer) const;
};

#endif // NVDDEFENSE_H
