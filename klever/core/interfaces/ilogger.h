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
     * \param[in] datetime - дата и время
     * \param[in] txt - текст сообщения
     * \param[in] type - тип сообщения
     */
    virtual void log(QObject *ptr,
             const QString &datetime,
             const QString &txt,
             MessagesTypes type)=0;
};



#endif // ILOGGER


