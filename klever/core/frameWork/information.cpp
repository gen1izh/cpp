#include "information.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <library/orm/models/mainqdjangomodel.h>

#include <QDebug>
#include <QCoreApplication>

Information::Information()
{

}



Information &Information::instance()
{
  static Information info;
  return info;
}

bool Information::isDataReaded()
{
  return m_isDataReaded;
}

void Information::setIsDataReaded(bool isDataReaded)
{
  m_isDataReaded = isDataReaded;
}


bool Information::readApplicationInformation()
{
    QSqlDatabase db = QSqlDatabase::database("information");
    if (db.driverName()!="QSQLITE") {
        db = QSqlDatabase::addDatabase("QSQLITE", "information");
    }
    QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__information");
    db.setDatabaseName(path);
    db.open();

  QDjango::registerModel<MainQDjangoModel>();

  QDjango::createTables();

  QDjangoQuerySet<MainQDjangoModel> allModelRecords;

  // Если запись 1 одна есть,значит настройки записаны и их нужно считать,
  // иначе нужно создать запись с настройками.
  if (allModelRecords.size() == 1) {
      QList<QVariantMap> propertyMaps = allModelRecords.values( QStringList() << "company"
                                                                              << "softwareNamePrefix"
                                                                              << "softwareNameSuffix"
                                                                              << "version"
                                                                              << "mainTitleApp"
                                                                              << "cveMessage"
                                                                              << "otherMessage"
                                                                              << "aboutMessageTitle"
                                                                              << "aboutMessageTop"
                                                                              << "aboutMessageBottom"
                                                                              << "specialParameters");
      foreach (const QVariantMap &propertyMap, propertyMaps) {
        setCompany(propertyMap["company"].toString());
        setSoftwareNamePrefix(propertyMap["softwareNamePrefix"].toString());
        setSoftwareNameSuffix(propertyMap["softwareNameSuffix"].toString());
        setVersion(propertyMap["version"].toString());
        setMainTitleApp(propertyMap["mainTitleApp"].toString());
        setCveMessage(propertyMap["cveMessage"].toString());
        setOtherMessage(propertyMap["otherMessage"].toString());
        setAboutMessageTitle(propertyMap["aboutMessageTitle"].toString());
        setAboutMessageTop(propertyMap["aboutMessageTop"].toString());
        setAboutMessageBottom(propertyMap["aboutMessageBottom"].toString());
        setSpecialParameters(propertyMap["specialParameters"].toString());
        setIsDataReaded(true);
        return true;
      }
  }
  else {
    return false;
  }

  db.close();
  return true;
}

void Information::saveApplicationInformation()
{
  QSqlDatabase db = QSqlDatabase::database("information");
  if (db.driverName()!="QSQLITE") {
      db = QSqlDatabase::addDatabase("QSQLITE", "information");
  }
  QString path = QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg("__information");
  db.setDatabaseName(path);
  db.open();

  QDjango::setDatabase(db);
  QDjango::registerModel<MainQDjangoModel>();

  QDjango::dropTables();
  QDjango::createTables();

  MainQDjangoModel *information = new MainQDjangoModel;
  information->setCompany(m_company);
  information->setSoftwareNamePrefix(m_softwareNamePrefix);
  information->setSoftwareNameSuffix(m_softwareNameSuffix);
  information->setVersion(m_version);
  information->setMainTitleApp(m_mainTitleApp);
  information->setCveMessage(m_cveMessage);
  information->setOtherMessage(m_otherMessage);
  information->setAboutMessageTitle(m_aboutMessageTitle);
  information->setAboutMessageTop(m_aboutMessageTop);
  information->setAboutMessageBottom(m_aboutMessageBottom);

  information->save();

  db.close();
}

QString Information::company()
{
  return m_company;
}

void Information::setCompany(const QString &company)
{
  m_company = company;
}

QString Information::softwareNamePrefix()
{
  return m_softwareNamePrefix;
}

void Information::setSoftwareNamePrefix(const QString &softwareNamePrefix)
{
  m_softwareNamePrefix = softwareNamePrefix;
}

QString Information::softwareNameSuffix()
{
  return m_softwareNameSuffix;
}

void Information::setSoftwareNameSuffix(const QString &softwareNameSuffix)
{
  m_softwareNameSuffix = softwareNameSuffix;
}

QString Information::version()
{
  return m_version;
}

void Information::setVersion(const QString &version)
{
  m_version = version;
}

QString Information::mainTitleApp()
{
  return m_mainTitleApp;
}

void Information::setMainTitleApp(const QString &mainTitleApp)
{
  m_mainTitleApp = mainTitleApp;
}

QString Information::cveMessage()
{
  return m_cveMessage;
}

void Information::setCveMessage(const QString &cveMessage)
{
  m_cveMessage = cveMessage;
}

QString Information::otherMessage()
{
  return m_otherMessage;
}

void Information::setOtherMessage(const QString &otherMessage)
{
  m_otherMessage = otherMessage;
}

QString Information::aboutMessageTitle()
{
  return m_aboutMessageTitle;
}

void Information::setAboutMessageTitle(const QString &aboutMessageTitle)
{
  m_aboutMessageTitle = aboutMessageTitle;
}

QString Information::aboutMessageTop()
{
  return m_aboutMessageTop;
}

void Information::setAboutMessageTop(const QString &aboutMessageTop)
{
  m_aboutMessageTop = aboutMessageTop;
}

QString Information::aboutMessageBottom()
{
  return m_aboutMessageBottom;
}

void Information::setAboutMessageBottom(const QString &aboutMessageBottom)
{
  m_aboutMessageBottom = aboutMessageBottom;
}

QHash<QString, QString> Information::specialParameters() const
{
  return m_specialParameters;
}

QString Information::specialParametersToString() const
{
  QString params = "";
  QHashIterator<QString, QString> i(m_specialParameters);
  while (i.hasNext()) {
      i.next();
      if (!params.isEmpty()) {
        params+=";";
      }
      params += QString("{'%1'='%2'}").arg(i.key()).arg(i.value());
  }

  params += "{" + params + "}";

  return params;

}

void Information::setSpecialParameters(const QString &specialParameters)
{
  // Формат специальных параметров следующий
  // {{'key'='value'};...}


  QString parseString = specialParameters;

  // Удалил все пробелмы вначале и в конце предложения
  parseString.trimmed();

  // Удалил все  символы ; внутри ключей или значений, если таковые есть.
  for (int i = 0; i < parseString.size(); i++) {
    if ((i >0) && (i < parseString.size())) {
      if ((parseString.at(i) == QString(";")) && ((parseString.at(i-1) != QString("}"))||(parseString.at(i+1) != QString("{")))) {
        parseString.replace(i, 1, QString(""));
      }
    }
  }

  if ((parseString.at(0) == QString("{")) && (parseString.at(parseString.size()) == QString("}"))) {

    QStringList tmp = parseString.split(";");

    foreach (QString param, tmp) {
      if ((param.at(0) == QString("{")) && (param.at(param.size()) == QString("}"))) {
        param.remove(0,1);
        param.remove(param.size()-1,1);
        QStringList keyValue = param.split("=");
        QString key = keyValue.at(0);
        QString value = keyValue.at(1);
        key = key.trimmed();
        value = value.trimmed();

        key.remove(0,1);
        key.remove(key.size()-1,1);

        value.remove(0,1);
        value.remove(value.size()-1,1);

        m_specialParameters[key] = value;

      }
    }

  }

}
