#include "norvarad.h"

const std::string Norvarad::xmlNameDefense = "defense";
const std::string Norvarad::xmlNameAttack = "attack";
const std::string Norvarad::xmlNameEvo = "evo";
const std::string Norvarad::xmlNameConfused = "confused";
const std::string Norvarad::xmlNameMaster = "master";

Norvarad::Norvarad(double h, std::string n, double dt) : health(h), name(n), damageTaken(dt) { }

bool Norvarad::operator ==(const Norvarad& n) const
{
  return (n.name == name && n.getValue() == getValue());
}

bool Norvarad::operator !=(const Norvarad& n) const
{
  return (n.name != name || n.getValue() != getValue());
}

bool Norvarad::operator <(const Norvarad& n) const
{
 return (getValue() < n.getValue());
}

bool Norvarad::operator <=(const Norvarad& n) const
{
  return (getValue() <= n.getValue());
}

bool Norvarad::operator >(const Norvarad& n) const
{
  return (getValue() > n.getValue());
}

bool Norvarad::operator >=(const Norvarad& n) const
{
  return (getValue() >= n.getValue());
}

double Norvarad::getHealth() const
{
  return health;
}

double Norvarad::getRemainingHealth() const
{
  return ((health - damageTaken) < 0 ? 0 : (health - damageTaken));
}

std::string Norvarad::getName() const
{
  return name;
}

std::string Norvarad::printDescription() const
{
  std::ostringstream oss;
  oss << "Name: " << name << "\n";
  oss << "Value: " << getValue() << "\n";
  oss << "Maximum health: " << health << "\n";
  oss << "Remaining health: " << getRemainingHealth() << "\n";
  oss << "Damage Taken: " << damageTaken << "\n";
  return oss.str();
}

void Norvarad::setName(std::string n)
{
  name = n;
}

void Norvarad::increaseDamageTaken(double d)
{
  damageTaken += std::abs(d);
}

bool Norvarad::isAlive() const
{
  return (getRemainingHealth() > 0);
}

void Norvarad::toXml(QXmlStreamWriter &writer) const
{
  writer.writeStartElement("health");
  writer.writeCharacters(QString::number(health));
  writer.writeEndElement();
  writer.writeStartElement("damageTaken");
  writer.writeCharacters(QString::number(damageTaken));
  writer.writeEndElement();
  writer.writeStartElement("name");
  writer.writeCharacters(QString::fromStdString(name));
  writer.writeEndElement();
}
