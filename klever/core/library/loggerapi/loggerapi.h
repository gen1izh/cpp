#ifndef LOGGER_API_H
#define LOGGER_API_H
#include <QObject>



namespace Library {

    namespace LoggerApi {


        /*!
         * \brief Журналирование информационного сообщения
         * \param[in] ptr - указатель на источник сообщения
         * \param[in] txt - текст сообщения
         */
         void logInfo(QObject *ptr, QString txt);

        /*!
         * \brief Журналирование сообщения предупреждения
         * \param[in] ptr - указатель на источник сообщения
         * \param[in] txt - текст сообщения
         */
         void logWarning(QObject *ptr, QString txt);

        /*!
         * \brief Журналирование сообщения с ошибкой
         * \param[in] ptr - указатель на источник сообщения
         * \param[in] txt - текст сообщения
         */
         void logError(QObject *ptr, QString txt);

    }

}

#endif // LOGGER_API_H
