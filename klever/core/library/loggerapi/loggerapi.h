#ifndef LOGGERAPI_H
#define LOGGERAPI_H

#include <QObject>
#include <frameWork/cveManager.h>
#include <interfaces/ilogger.h>

namespace Library {

  namespace LoggerApi {

    /*!
     * \brief Журналирование информационного сообщения. Журнал системный (по-умолчанию)
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logInfo(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование сообщения предупреждения. Журнал системный (по-умолчанию)
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logWarning(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование сообщения с ошибкой. Журнал системный (по-умолчанию)
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logError(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование информационного сообщения. Журнал модулей
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logInfo_ToModuleJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование сообщения предупреждения. Журнал модулей
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logWarning_ToModuleJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование сообщения об ошибке. Журнал модулей
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logError_ToModuleJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование информационного сообщения. Журнал пользователя
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logInfo_ToUserJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование информационного сообщения. Журнал пользователя
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logWarning_ToUserJournal(QObject *ptr, QString txt);
    /*!
     * \brief Журналирование информационного сообщения. Журнал пользователя
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logError_ToUserJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование информационного сообщения. Журнал скриптов
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logInfo_ToScriptJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование информационного сообщения. Журнал скриптов
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logWarning_ToScriptJournal(QObject *ptr, QString txt);

    /*!
     * \brief Журналирование информационного сообщения. Журнал скриптов
     * \param[in] ptr - указатель на источник сообщения
     * \param[in] txt - текст сообщения
     */
    void logError_ToScriptJournal(QObject *ptr, QString txt);

  }
}

#endif // LOGGERAPI_H
