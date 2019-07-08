#ifndef NVDATTACK_H
#define NVDATTACK_H

#include "norvarad.h"

class NvdAttack : virtual public Norvarad
{
private:
  double attackPower;
  const static double attackValueBoost;

public:
  explicit NvdAttack(double h = 0, std::string n = "", double a = 0, double dt = 0);

  std::string printDescription() const;
  std::string getType() const;
  double getAttackPower() const;
  NvdAttack* clone() const;
  double getValue() const;
  percentage getArmor() const;
  double takeDamage(double);
  double makeAttack();
  void toXml(QXmlStreamWriter& writer) const;
};

#endif // NVDATTACK_H
