#ifndef NVDMASTER_H
#define NVDMASTER_H

#include "nvdattack.h"
#include "nvddefense.h"

class NvdMaster : public NvdAttack, NvdDefense
{
private:
  const static double masterValueBoost;

public:
  explicit NvdMaster(double h = 0, std::string n = "", double att = 0, percentage arm = 0, double dt = 0);

  std::string printDescription() const;
  std::string getType() const;
  NvdMaster* clone() const;
  double getAttackPower() const;
  double getValue() const;
  percentage getArmor() const;
  double takeDamage(double);
  double makeAttack();
  void toXml(QXmlStreamWriter& writer) const;
};

#endif // NVDMASTER_H
