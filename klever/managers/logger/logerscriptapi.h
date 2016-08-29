#ifndef LOGER_SCRIPT_API_H
#define LOGER_SCRIPT_API_H

#include <QObject>
#include <library/loggerapi/loggerapi.h>

class LogerScriptApi : public QObject
{
    Q_OBJECT
  public:
    explicit LogerScriptApi(QObject *parent = 0);

  signals:

  public slots:

    /*!
     * \brief Журналирование ошибочного сообщения в журнал
     * \param[in] txt - текст сообщения
     */
    void error(QString txt);

    /*!
     * \brief Журналирование сообщения предупреждения в журнал
     * \param[in] txt - текст сообщения
     */
    void warning(QString txt);

    /*!
     * \brief Журналирование информационного сообщения в журнал
     * \param[in] txt - текст сообщения
     */
    void information(QString txt);
};

#endif // LOGER_SCRIPT_API_H
