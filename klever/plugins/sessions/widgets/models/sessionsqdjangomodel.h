#ifndef SESSION_QDJANGO_MODEL_H
#define SESSION_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class Sessions : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString parameters READ parameters WRITE setParameters)

    Q_CLASSINFO("name", "max_length=255")
    Q_CLASSINFO("parameters", "max_length=8192")

public:
    QString name() const;
    void setName(const QString &name);

    QString parameters() const;
    void setParameters(const QString &parameters);

private:
    QString m_name;
    QString m_parameters;
};

#endif // SESSION_QDJANGO_MODEL_H
