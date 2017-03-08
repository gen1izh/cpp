#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include <QStringListModel>
#include <QtSql/QSqlDatabase>
#include <library/orm/db/QDjango.h>
#include <library/orm/db/QDjangoQuerySet.h>
#include "loggerqdjangomodel.h"

class LoggerModel : public QObject
{

    Q_OBJECT

public:
    LoggerModel();
    ~LoggerModel();

    /*!
     * \brief Возвращает список сообщений
     * \return
     */
    QStringList filtredMessages(const QString &startDateTime, const QString &endDateTime,
                                bool isError, bool isWarning, bool isInformation,
                                const QStringList &sources);

    QStringList getSources();

    /*!
     * \brief Добавить запись в журнал
     * \param[in] source - источник сообщения
     * \param[in] datetime - дата\время сообщения
     * \param[in] txt - текст сообщения
     * \param[in] type - тип сообщения
     */
    void addMessage(const QString &source, const QString &datetime, const QString &txt, const QString &type);

    QStringList filtredSources(QDjangoQuerySet<LoggerQDjangoModel> someMessages, const QStringList &sources);
};

#endif // LOGGER_MODEL_H
