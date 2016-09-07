#ifndef MAIN_QDJANGO_MODEL_H
#define MAIN_QDJANGO_MODEL_H

#include "../db/QDjangoModel.h"

class MainQDjangoModel : public QDjangoModel
{

    Q_OBJECT

    QString m_company;
    QString m_softwareNamePrefix;
    QString m_softwareNameSuffix;
    QString m_version;
    QString m_mainTitleApp;
    QString m_cveMessage;
    QString m_otherMessage;
    QString m_aboutMessageTitle;
    QString m_aboutMessageTop;
    QString m_aboutMessageBottom;

    QString m_specialParameters;

    Q_PROPERTY(QString company READ company WRITE setCompany)
    Q_CLASSINFO("company", "max_length=255")

    Q_PROPERTY(QString softwareNamePrefix READ softwareNamePrefix WRITE setSoftwareNamePrefix)
    Q_CLASSINFO("softwareNamePrefix", "max_length=255")

    Q_PROPERTY(QString softwareNameSuffix READ softwareNameSuffix WRITE setSoftwareNameSuffix)
    Q_CLASSINFO("softwareNameSuffix", "max_length=255")

    Q_PROPERTY(QString version READ version WRITE setVersion)
    Q_CLASSINFO("version", "max_length=255")

    Q_PROPERTY(QString mainTitleApp READ mainTitleApp WRITE setMainTitleApp)
    Q_CLASSINFO("mainTitleApp", "max_length=255")

    Q_PROPERTY(QString cveMessage READ cveMessage WRITE setCveMessage)
    Q_CLASSINFO("cveMessage", "max_length=255")

    Q_PROPERTY(QString otherMessage READ otherMessage WRITE setOtherMessage)
    Q_CLASSINFO("otherMessage", "max_length=255")

    Q_PROPERTY(QString aboutMessageTitle READ aboutMessageTitle WRITE setAboutMessageTitle)
    Q_CLASSINFO("aboutMessageTitle", "max_length=255")

    Q_PROPERTY(QString aboutMessageTop READ aboutMessageTop WRITE setAboutMessageTop)
    Q_CLASSINFO("aboutMessageTop", "max_length=255")

    Q_PROPERTY(QString aboutMessageBottom READ aboutMessageBottom WRITE setAboutMessageBottom)
    Q_CLASSINFO("aboutMessageBottom", "max_length=1024")

    Q_PROPERTY(QString specialParameters READ specialParameters WRITE setSpecialParameters)
    Q_CLASSINFO("specialParameters", "max_length=8192")

public:

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

    QString specialParameters() const;
    void setSpecialParameters(const QString &specialParameters);
};

#endif // MAIN_QDJANGO_MODEL_H
