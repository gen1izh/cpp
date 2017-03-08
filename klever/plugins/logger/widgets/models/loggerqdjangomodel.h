#ifndef LOGGER_QDJANGO_MODEL_H
#define LOGGER_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class LoggerQDjangoModel : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource)
    Q_PROPERTY(QString datetime READ datetime WRITE setDatetime)
    Q_PROPERTY(QString txt READ txt WRITE setTxt)
    Q_PROPERTY(QString type READ type WRITE setType)

    Q_CLASSINFO("source", "max_length=64")
    Q_CLASSINFO("datetime", "max_length=64")
    Q_CLASSINFO("txt", "max_length=256")
    Q_CLASSINFO("type", "max_length=32")

public:

    QString source() const;
    void setSource(const QString &source);

    QString datetime() const;
    void setDatetime(const QString &datetime);

    QString txt() const;
    void setTxt(const QString &txt);

    QString type() const;
    void setType(const QString &type);

private:
    QString m_source;
    QString m_datetime;
    QString m_txt;
    QString m_type;
};

#endif // LOGGER_QDJANGO_MODEL_H
