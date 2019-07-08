#include "nvdmaster.h"

const double NvdMaster::masterValueBoost = 1.5;


NvdMaster::NvdMaster(double h, std::string n, double att, percentage arm, double dt) : Norvarad(h,n,dt), NvdAttack(h,n,att), NvdDefense(h,n,arm) { }

std::string NvdMaster::printDescription() const
{
  std::ostringstream oss;
  std::string aux = NvdDefense::printDescription();
  oss << "Type: master based on Type: attack and " << aux;
  oss << "Attack power: " << getAttackPower() << "\n";
  return oss.str();
}

std::string NvdMaster::getType() const
{
  return "master based on attack and defense";
}

NvdMaster* NvdMaster::clone() const
{
  return new NvdMaster(*this);
}

double NvdMaster::getAttackPower() const
{
  return NvdAttack::getAttackPower();
}

double NvdMaster::getValue() const
{
  return (( NvdAttack::getValue() + NvdDefense::getValue() ) / 2 ) * masterValueBoost;
}

percentage NvdMaster::getArmor() const
{
  return NvdDefense::getArmor();
}

double NvdMaster::takeDamage(double d)
{
  return NvdDefense::takeDamage(d);
}

double NvdMaster::makeAttack()
{
  return NvdAttack::makeAttack();
}

void NvdMaster::toXml(QXmlStreamWriter &writer) const
{
  writer.writeStartElement(QString::fromStdString(xmlNameMaster));

  Norvarad::toXml(writer);

  writer.writeStartElement("attackPower");
  writer.writeCharacters(QString::number(getAttackPower()));
  writer.writeEndElement();
  writer.writeStartElement("armorLevel");
  writer.writeCharacters(QString::number(getArmor()));
  writer.writeEndElement();

  writer.writeEndElement();
}
