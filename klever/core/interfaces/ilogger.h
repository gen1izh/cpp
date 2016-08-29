#ifndef ILOGGER
#define ILOGGER

#include <QObject>
#include <QMetaClassInfo>
#include <QChar>
#include <QHash>

// Перечисления типов сообщений
enum MessagesTypes{
  MESSAGE_ERROR,   // Ошибка
  MESSAGE_WARNING, // Предупреждение
  MESSAGE_INFO     // Информация
};

// Перечисления типов журналов
enum LoggersTypes{
  SYSTEM_LOG,        // Системный журнал (протоколируются сообщения core)
  USER_LOG,          // Пользовательский журнал (протоколируются сообщения
                     //  managers, formManager)
  MODULE_LOG,        // Журнал модулей (протоколируются сообщения из модулей)
  SCRIPT_LOG,        // Журнал скриптов (протоколируются сообщения скриптов)
};


/*!
 * \brief Интерфейс для журнала приложения
 */
class ILogger {

public:
    ILogger(){}

    virtual ~ILogger(){}

    /*!
     * \brief Функция журналирования сообщения
     * \param[in] ptr - указатель на объект источник сообщения
     * \param[in] txt - текст сообщения
     * \param[in] type - тип сообщения
     * \param[in] loggertype - тип журнала
     */
    virtual void log(QObject *ptr,
                     QString txt,
                     MessagesTypes type,
                     LoggersTypes loggertype = SYSTEM_LOG)=0;

};



#endif // ILOGGER

