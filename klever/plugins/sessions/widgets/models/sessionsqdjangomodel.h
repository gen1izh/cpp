#ifndef SESSION_QDJANGO_MODEL_H
#define SESSION_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class Sessions : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString parameters READ parameters WRITE setParameters)
    Q_PROPERTY(QString information READ information WRITE setInformation)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("parameters", "")
    Q_CLASSINFO("information", "max_length=1024")

public:
    QString name() const;
    void setName(const QString &name);

    QString parameters() const;
    void setParameters(const QString &parameters);

    QString information() const;
    void setInformation(const QString &information);

private:
    QString m_name;
    QString m_parameters;
    QString m_information;
};

#endif // SESSION_QDJANGO_MODEL_H
