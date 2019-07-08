#include "nvddevo.h"

const double NvdDEvo::armorIncrementValue = 0.1;
const double NvdDEvo::evoValueBoost = 1.1;

NvdDEvo::NvdDEvo(double h, std::string n, percentage a, double dt) : Norvarad (h,n,dt), NvdDefense (h,n,a) { }

std::string NvdDEvo::printDescription() const

{
  std::ostringstream oss;
  std::string aux = NvdDefense::printDescription();
  oss << "Type: evolution based on " << aux;
  oss << "Armor boost: " << armorIncrementValue << "%\n";
  return oss.str();
}

std::string NvdDEvo::getType() const
{
  return "evolution based on defense";
}

NvdDEvo* NvdDEvo::clone() const
{
  return new NvdDEvo(*this);
}

double NvdDEvo::getValue() const
{
  return NvdDefense::getValue() * evoValueBoost;
}

double NvdDEvo::takeDamage(double d)

{
  incrementArmorLevel(static_cast<percentage>( getArmor() * armorIncrementValue ));
  return NvdDefense::takeDamage(d);
}

void NvdDEvo::toXml(QXmlStreamWriter &writer) const
{
  writer.writeStartElement(QString::fromStdString(xmlNameEvo));

  Norvarad::toXml(writer);

  writer.writeStartElement("armorLevel");
  writer.writeCharacters(QString::number(getArmor()));
  writer.writeEndElement();

  writer.writeEndElement();
}
