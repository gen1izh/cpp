#ifndef LOGGER_SETTINGS_QDJANGO_MODEL_H
#define LOGGER_SETTINGS_QDJANGO_MODEL_H

#include <library/orm/db/QDjangoModel.h>

class LoggerSettingsQDjangoModel : public QDjangoModel
{
    Q_OBJECT
    Q_PROPERTY(QString currentLoggerName READ currentLoggerName WRITE setCurrentLoggerName)

    Q_CLASSINFO("currentLoggerName", "max_length=64")

public:

    QString currentLoggerName() const;
    void setCurrentLoggerName(const QString &currentLoggerName);

private:
    QString m_currentLoggerName;
};

#endif // LOGGER_SETTINGS_QDJANGO_MODEL_H
