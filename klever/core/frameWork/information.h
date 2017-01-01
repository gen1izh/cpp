#ifndef INFORMATION
#define INFORMATION

#include <QString>
#include <QHash>
#include <QSqlDatabase>

class Information {

  QString m_company            = "Company";
  QString m_softwareNamePrefix = "Klever_";
  QString m_softwareNameSuffix = "Software";
  QString m_version            = "0.0.1";
  QString m_mainTitleApp       = "Klever Software";
  QString m_cveMessage         = "deprecated";
  QString m_otherMessage       = "deprecated";
  QString m_aboutMessageTitle  = "Klever Software";
  QString m_aboutMessageTop    = "Klever easy framework";
  QString m_aboutMessageBottom = "Hello world!";

  bool m_isDataReaded = false;

  QHash<QString, QString> m_specialParameters;

  QSqlDatabase m_db;

  Information();

  Information(const Information&);

  Information& operator=(const Information&);

public:

  static Information& instance();

  bool readApplicationInformation();
  void saveApplicationInformation();

  QString company();
  void setCompany(const QString &company);

  QString softwareNamePrefix();
  void setSoftwareNamePrefix(const QString &softwareNamePrefix);

  QString softwareNameSuffix();
  void setSoftwareNameSuffix(const QString &softwareNameSuffix);
  QString version();
  void setVersion(const QString &version);
  QString mainTitleApp();
  void setMainTitleApp(const QString &mainTitleApp);
  QString cveMessage();
  void setCveMessage(const QString &cveMessage);
  QString otherMessage();
  void setOtherMessage(const QString &otherMessage);
  QString aboutMessageTitle();
  void setAboutMessageTitle(const QString &aboutMessageTitle);
  QString aboutMessageTop();
  void setAboutMessageTop(const QString &aboutMessageTop);
  QString aboutMessageBottom();
  void setAboutMessageBottom(const QString &aboutMessageBottom);
  QHash<QString, QString> specialParameters() const;
  QString specialParametersToString() const;
  void setSpecialParameters(const QString &specialParameters);

  bool isDataReaded();
  void setIsDataReaded(bool isDataReaded);

};


#endif // INFORMATION

