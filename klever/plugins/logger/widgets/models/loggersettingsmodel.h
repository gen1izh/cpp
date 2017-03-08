#ifndef LOGGER_SETTINGS_MODEL_H
#define LOGGER_SETTINGS_MODEL_H

#include <QStringListModel>
#include <QtSql/QSqlDatabase>
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include "loggersettingsqdjangomodel.h"

class LoggerSettingsModel : public QObject
{
    Q_OBJECT

    QSqlDatabase m_db;

public:
    LoggerSettingsModel();
    ~LoggerSettingsModel();

    /*!
     * \brief Установить
     * \param[in] currentName - теккущий журнал
     */
    void setCurrentName(const QString &currentName);

    /*!
     * \brief Вернуть
     */
    QString getCurrentName();
};

#endif // LOGGER_SETTINGS_MODEL_H
