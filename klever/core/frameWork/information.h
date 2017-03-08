#ifndef INFORMATION
#define INFORMATION

#include <QString>
#include <QHash>
#include <QSqlDatabase>

class Information {

    Information();
    Information(const Information&);
    Information& operator=(const Information&);

    QString m_company            = "Company";
    QString m_softwareNamePrefix = "Klever_";
    QString m_softwareNameSuffix = "Software";
    QString m_version            = "0.0.1";
    QString m_mainTitleApp       = "Klever Software";
    QString m_changelog          = "";
    QString m_aboutMessageTitle  = "Klever Software";
    QString m_aboutMessageTop    = "Klever easy framework";
    QString m_aboutMessageBottom = "Hello world!";
    QString m_style              = "windows";
    QString m_logo               = "default";

    bool m_isDataReaded = false;

    QHash<QString, QString> m_specialParameters;


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

    QString changelog();
    void setChangelog(const QString &changelog);

    QString aboutMessageTitle();
    void setAboutMessageTitle(const QString &aboutMessageTitle);

    QString aboutMessageTop();
    void setAboutMessageTop(const QString &aboutMessageTop);

    QString aboutMessageBottom();
    void setAboutMessageBottom(const QString &aboutMessageBottom);

    bool isDataReaded();
    void setIsDataReaded(bool isDataReaded);

    QString style() const;
    void setStyle(const QString &style);

    QString logo() const;
    void setLogo(const QString &name);
};


#endif // INFORMATION

