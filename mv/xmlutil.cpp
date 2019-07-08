#include "xmlutil.h"

const QString XmlUtil::startKeyword = "norvarads";

XmlUtil::XmlUtil() { }

Container<DeepPtr<Norvarad>> XmlUtil::load(const QString& fileName) const
{
  Container<DeepPtr<Norvarad>> aux;

  QFile saveFile(fileName);
  if (saveFile.open(QIODevice::ReadOnly))
  {
    QXmlStreamReader streamReader(&saveFile);
    if (streamReader.readNextStartElement() && streamReader.name() == startKeyword)
    {
      while (streamReader.readNextStartElement())
      {
        QStringRef type = streamReader.name();
        streamReader.readNextStartElement();
        double health = streamReader.readElementText().toDouble();
        streamReader.readNextStartElement();
        double damageTaken = streamReader.readElementText().toDouble();
        streamReader.readNextStartElement();
        std::string name = streamReader.readElementText().toStdString();

        // leggi i dati speciali di ogni classe
        if (type == QString::fromStdString(Norvarad::xmlNameDefense))
        {
          streamReader.readNextStartElement();
          percentage armorLevel = static_cast<percentage>(streamReader.readElementText().toShort());
          NvdDefense nvd(health,name,armorLevel,damageTaken);
          aux.push_back(&nvd);
        }
        else if (type == QString::fromStdString(Norvarad::xmlNameAttack))
        {
          streamReader.readNextStartElement();
          double attackPower = static_cast<percentage>(streamReader.readElementText().toDouble());
          NvdAttack nvd(health,name,attackPower,damageTaken);
          aux.push_back(&nvd);
        }
        else if (type == QString::fromStdString(Norvarad::xmlNameConfused))
        {
          streamReader.readNextStartElement();
          double attackPower = static_cast<percentage>(streamReader.readElementText().toDouble());
          NvdAConfused nvd(health,name,attackPower,damageTaken);
          aux.push_back(&nvd);
        }
        else if (type == QString::fromStdString(Norvarad::xmlNameEvo))
        {
          streamReader.readNextStartElement();
          percentage armorLevel = static_cast<percentage>(streamReader.readElementText().toShort());
          NvdDEvo nvd(health,name,armorLevel,damageTaken);
          aux.push_back(&nvd);
        }
        else if (type == QString::fromStdString(Norvarad::xmlNameMaster))
        {
          streamReader.readNextStartElement();
          double attackPower = static_cast<percentage>(streamReader.readElementText().toDouble());
          streamReader.readNextStartElement();
          percentage armorLevel = static_cast<percentage>(streamReader.readElementText().toShort());
          NvdMaster nvd(health,name,attackPower,armorLevel,damageTaken);
          aux.push_back(&nvd);
        }

        // read next element
        streamReader.skipCurrentElement();
      }
    }
  }

  saveFile.close();
  return aux;
}

bool XmlUtil::save(const QString& fileName, const Container<DeepPtr<Norvarad>>& cont) const
{
  QSaveFile saveFile(fileName);
  saveFile.setFileName(fileName);
  if (saveFile.open(QIODevice::WriteOnly))
  {
    QXmlStreamWriter streamWriter(&saveFile);
    streamWriter.setAutoFormatting(true);
    streamWriter.writeStartDocument();
    streamWriter.writeComment("Don't edit!");
    streamWriter.writeStartElement(startKeyword);
    for (auto cit = cont.begin(); cit != cont.end(); ++cit)
    {
        (*cit)->toXml(streamWriter);
    }
    streamWriter.writeEndElement();
    streamWriter.writeEndDocument();
    saveFile.commit();
    return true;
  }
  return false;
}
