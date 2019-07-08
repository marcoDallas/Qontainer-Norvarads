#include "nvdattack.h"

const double NvdAttack::attackValueBoost = 0.8;


NvdAttack::NvdAttack(double h, std::string n, double a, double dt) : Norvarad(h,n,dt), attackPower(a) { }

std::string NvdAttack::printDescription() const
{
  std::ostringstream oss;
  std::string aux = Norvarad::printDescription();
  oss << "Type: attack\n" << aux;
  oss << "Attack power: " << attackPower << "\n";
  return oss.str();
}

std::string NvdAttack::getType() const
{
  return "attack";
}

NvdAttack* NvdAttack::clone() const
{
  return new NvdAttack(*this);
}

double NvdAttack::getAttackPower() const
{
  return attackPower;
}

double NvdAttack::getValue() const
{
  return getRemainingHealth()+(getAttackPower()*attackValueBoost);
}

percentage NvdAttack::getArmor() const
{
  return 0;
}

double NvdAttack::takeDamage(double d)
{
  increaseDamageTaken(d);
  return d;
}

double NvdAttack::makeAttack()
{
  return attackPower;
}

void NvdAttack::toXml(QXmlStreamWriter &writer) const
{
  writer.writeStartElement(QString::fromStdString(xmlNameAttack));

  Norvarad::toXml(writer);

  writer.writeStartElement("attackPower");
  writer.writeCharacters(QString::number(getAttackPower()));
  writer.writeEndElement();

  writer.writeEndElement();
}
