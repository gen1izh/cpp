#include "information.h"
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include <library/orm/models/mainqdjangomodel.h>

#include <library/message/messagelibrary.h>
#include <frameWork/base.h>

#include <QDebug>
#include <QCoreApplication>

Information::Information()
{
}

QString Information::style() const
{
    return m_style;
}

void Information::setStyle(const QString &style)
{
    m_style = style;
}

QString Information::logo() const
{
    return m_logo;
}

void Information::setLogo(const QString &name)
{
    m_logo = name;
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
    QDjango::setDatabase(*Core::Base::instance().database());
    QDjango::registerModel<MainQDjangoModel>();
    QDjango::createTables();
    QDjango::setDebugEnabled(false);

    QDjangoQuerySet<MainQDjangoModel> _info;

    // Если запись 1 одна есть,значит настройки записаны и их нужно считать,
    // иначе нужно создать запись с настройками.
    if (_info.count() == 1) {
        QList<QVariantMap> propertyMaps = _info.values( QStringList() << "company"
                                                                  << "softwareNamePrefix"
                                                                  << "softwareNameSuffix"
                                                                  << "version"
                                                                  << "mainTitleApp"
                                                                  << "changelog"
                                                                  << "aboutMessageTitle"
                                                                  << "aboutMessageTop"
                                                                  << "aboutMessageBottom"
                                                                  << "style"
                                                                  << "logo");
        foreach (const QVariantMap &propertyMap, propertyMaps) {
            setCompany(propertyMap["company"].toString());
            setSoftwareNamePrefix(propertyMap["softwareNamePrefix"].toString());
            setSoftwareNameSuffix(propertyMap["softwareNameSuffix"].toString());
            setVersion(propertyMap["version"].toString());
            setMainTitleApp(propertyMap["mainTitleApp"].toString());
            setChangelog(propertyMap["changelog"].toString());
            setStyle(propertyMap["style"].toString());
            setAboutMessageTitle(propertyMap["aboutMessageTitle"].toString());
            setAboutMessageTop(propertyMap["aboutMessageTop"].toString());
            setAboutMessageBottom(propertyMap["aboutMessageBottom"].toString());
            setIsDataReaded(true);
            setLogo(propertyMap["logo"].toString());
            return true;
        }
    }
    else {
        return false;
    }

    return true;
}

void Information::saveApplicationInformation()
{
//    QSqlDatabase m_db = QSqlDatabase::addDatabase("QODBC", "information");
//    m_db.setDatabaseName("DRIVER={SQL Server};SERVER=.\\SQLEXPRESS;DATABASE=__INFORMATION;Trusted_Connection=yes;");
//    m_db.setUserName("sa");
//    ;
//    if (!m_db.open()) {
//        messageLibrary msg;
//        QString text;
//        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db.lastError().text());

//        msg.createErrorMessage("Ошибка", text);
//    }
//    else {

//        QDjango::setDatabase(m_db);
        QDjango::setDatabase(*Core::Base::instance().database());
        QDjango::registerModel<MainQDjangoModel>();

        QDjango::dropTables();
        QDjango::createTables();

        MainQDjangoModel *information = new MainQDjangoModel;
        information->setCompany(m_company);
        information->setSoftwareNamePrefix(m_softwareNamePrefix);
        information->setSoftwareNameSuffix(m_softwareNameSuffix);
        information->setVersion(m_version);
        information->setMainTitleApp(m_mainTitleApp);
        information->setChangelog(m_changelog);
        information->setStyle(m_style);
        information->setAboutMessageTitle(m_aboutMessageTitle);
        information->setAboutMessageTop(m_aboutMessageTop);
        information->setAboutMessageBottom(m_aboutMessageBottom);
        information->setLogo(m_logo);
        information->save();
//    }
//    m_db.close();
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

QString Information::changelog()
{
  return m_changelog;
}

void Information::setChangelog(const QString &changelog)
{
  m_changelog = changelog;
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


