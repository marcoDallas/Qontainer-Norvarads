#include "nvdaconfused.h"

const double NvdAConfused::healthMalusValue = 0.1;
const double NvdAConfused::confusedValueBoost = 0.9;


NvdAConfused::NvdAConfused(double h, std::string n, double a, double dt) : Norvarad (h,n,dt), NvdAttack(h,n,a) { }

std::string NvdAConfused::printDescription() const
{
  std::ostringstream oss;
  std::string aux = NvdAttack::printDescription();
  oss << "Type: confused based on " << aux;
  oss << "Health malus: " << healthMalusValue << "%\n";
  return oss.str();
}

std::string NvdAConfused::getType() const
{
  return "confused based on attack";
}

NvdAConfused* NvdAConfused::clone() const
{
  return new NvdAConfused(*this);
}

double NvdAConfused::getValue() const
{
  return NvdAttack::getValue()*confusedValueBoost;
}

double NvdAConfused::makeAttack()
{
  takeDamage( getRemainingHealth() * healthMalusValue );
  return NvdAttack::makeAttack();
}

void NvdAConfused::toXml(QXmlStreamWriter &writer) const
{
  writer.writeStartElement(QString::fromStdString(xmlNameConfused));

  Norvarad::toXml(writer);

  writer.writeStartElement("attackPower");
  writer.writeCharacters(QString::number(getAttackPower()));
  writer.writeEndElement();

  writer.writeEndElement();
}
