#include "mainqdjangomodel.h"

QString MainQDjangoModel::softwareNamePrefix()
{
  return m_softwareNamePrefix;
}

void MainQDjangoModel::setSoftwareNamePrefix(const QString &softwareNamePrefix)
{
  m_softwareNamePrefix = softwareNamePrefix;
}

QString MainQDjangoModel::softwareNameSuffix()
{
  return m_softwareNameSuffix;
}

void MainQDjangoModel::setSoftwareNameSuffix(const QString &softwareNameSuffix)
{
  m_softwareNameSuffix = softwareNameSuffix;
}

QString MainQDjangoModel::version()
{
  return m_version;
}

void MainQDjangoModel::setVersion(const QString &version)
{
  m_version = version;
}

QString MainQDjangoModel::mainTitleApp()
{
  return m_mainTitleApp;
}

void MainQDjangoModel::setMainTitleApp(const QString &mainTitleApp)
{
  m_mainTitleApp = mainTitleApp;
}

QString MainQDjangoModel::changelog()
{
  return m_changelog;
}

void MainQDjangoModel::setChangelog(const QString &changelog)
{
  m_changelog = changelog;
}

QString MainQDjangoModel::aboutMessageTitle()
{
  return m_aboutMessageTitle;
}

void MainQDjangoModel::setAboutMessageTitle(const QString &aboutMessageTitle)
{
  m_aboutMessageTitle = aboutMessageTitle;
}

QString MainQDjangoModel::aboutMessageTop()
{
  return m_aboutMessageTop;
}

void MainQDjangoModel::setAboutMessageTop(const QString &aboutMessageTop)
{
  m_aboutMessageTop = aboutMessageTop;
}

QString MainQDjangoModel::aboutMessageBottom()
{
  return m_aboutMessageBottom;
}

void MainQDjangoModel::setAboutMessageBottom(const QString &aboutMessageBottom)
{
  m_aboutMessageBottom = aboutMessageBottom;
}

QString MainQDjangoModel::style() const
{
    return m_style;
}

void MainQDjangoModel::setStyle(const QString &style)
{
    m_style = style;
}

QString MainQDjangoModel::logo() const
{
    return m_logo;
}

void MainQDjangoModel::setLogo(const QString &logo)
{
    m_logo = logo;
}

QString MainQDjangoModel::company()
{
    return m_company;
}

void MainQDjangoModel::setCompany(const QString &company)
{
    m_company = company;
}
