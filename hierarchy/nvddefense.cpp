#include "nvddefense.h"

const double NvdDefense::armorValueBoost = 0.8;
const percentage NvdDefense::armorCap = 85;


NvdDefense::NvdDefense(double h, std::string n, percentage a, double dt) : Norvarad(h,n,dt), armorLevel(a > armorCap ? armorCap : a) { }

std::string NvdDefense::printDescription() const
{
  std::ostringstream oss;
  std::string aux = Norvarad::printDescription();
  oss << "Type: defense\n" << aux;
  oss << "percentage of armor: " << armorLevel << "%\n";
  return oss.str();
}

std::string NvdDefense::getType() const
{
  return "defense";
}

void NvdDefense::incrementArmorLevel(percentage p)
{
  (armorLevel += p) > armorCap ? armorLevel = armorCap : armorLevel += p;
}

NvdDefense* NvdDefense::clone() const
{
  return new NvdDefense(*this);
}

double NvdDefense::getAttackPower() const
{
  return 0;
}

double NvdDefense::getValue() const
{
  return getRemainingHealth()+(armorLevel*armorValueBoost);
}

percentage NvdDefense::getArmor() const
{
  return armorLevel;
}

double NvdDefense::takeDamage(double d)
{
  double dT = d * (static_cast<double>(( 100 - getArmor() )) / 100 );
  increaseDamageTaken(dT);
  return dT;
}

double NvdDefense::makeAttack()
{
  return 0;
}

void NvdDefense::toXml(QXmlStreamWriter &writer) const
{
  writer.writeStartElement(QString::fromStdString(xmlNameDefense));

  Norvarad::toXml(writer);

  writer.writeStartElement("armorLevel");
  writer.writeCharacters(QString::number(getArmor()));
  writer.writeEndElement();

  writer.writeEndElement();
}
