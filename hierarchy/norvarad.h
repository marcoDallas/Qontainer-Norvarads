#ifndef NORVARAD_H
#define NORVARAD_H

#include <sstream>
#include <string>
#include <cmath>
#include <QXmlStreamWriter>

typedef unsigned short percentage;

class Norvarad
{
private:
  double health;
  std::string name;
  double damageTaken;

protected:
  void increaseDamageTaken(double);

public:
  explicit Norvarad(double h = 0, std::string n = "", double dt = 0);
  Norvarad(const Norvarad&) = default;
  virtual ~Norvarad() = default;
  // operator =
  virtual Norvarad& operator = (const Norvarad&) = default;
  /*
   * compare by name and value
   */
  bool operator == (const Norvarad&) const;
  bool operator != (const Norvarad&) const;
  /*
   * compare by value (value is based on actual health level)
   */
  bool operator < (const Norvarad&) const;
  bool operator <= (const Norvarad&) const;
  bool operator > (const Norvarad&) const;
  bool operator >= (const Norvarad&) const;

  double getHealth() const;
  double getRemainingHealth() const;
  std::string getName() const;
  virtual std::string getType() const = 0;
  virtual std::string printDescription() const;
  void setName(std::string n);
  /**
   * @brief isAlive tells if a player is alive or not
   * @return true if player has remaining health greater than 0, false otherwise
   */
  bool isAlive() const;

  /**
   * @brief clone
   * @return a default copy of this player
   */
  virtual Norvarad* clone() const = 0;
  /**
   * @brief getValue tells the value of a player based on its properties
   * @return the value of a player
   */
  virtual double getValue() const = 0;
  /**
   * @brief getArmor
   * @return  armor level
   */
  virtual percentage getArmor() const = 0;
  /**
   * @brief getAttackPower
   * @return the attack power of a player
   */
  virtual double getAttackPower() const = 0;
  /**
   * @brief takeDamage increase the damage taken by a player
   * @return the effective damage taken (after armor effect)
   */
  virtual double takeDamage(double) = 0;
  /**
   * @brief attack effectively performs an attack (so may attivate triggers).
   *        not const because it may alter the health of the player in some
   *        situations
   * @return the attack power of a player
   */
  virtual double makeAttack() = 0;

  /**
   * @brief toXml saves the object to an XML file using the given writer
   * @param writer the xml writer to use
   */
  virtual void toXml(QXmlStreamWriter& writer) const;

  const static std::string xmlNameDefense;
  const static std::string xmlNameAttack;
  const static std::string xmlNameEvo;
  const static std::string xmlNameConfused;
  const static std::string xmlNameMaster;
};

#endif // NORVARAD_H
