#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "loggerdata.h"
#include "iloggerstorage.h"

/*******************************************************************************
 *                 Файловый внешний источник данных ( хранилище csv-файл ).
 *******************************************************************************/


/*!
 *  \brief Класс, реализует внешнее хранилище журнала приложения (csv файл).
 *  \details
 */
class FileStorage : public ILoggerStorage {

  /*!
   *  \brief Файловый дескриптор на хранилище сообщений в файловой системе.
   */
    QFile     *_logFd;

    /*!
     *  \brief Перевод структуры сообщения в строку.
     */
   QString messageStructureToString( messageStructure st );

  public:

    /*!
     *  \brief Конструктор класса
     */
   FileStorage(){}

    /*!
     *  \brief Деструктор класса
     */
    ~FileStorage(){}

    /*!
     *  \brief Открытие сессии работы с хранилищем.
     *  \param fileName строка, путь до файла.
     */
    uint openSession( QString fileName );

    /*!
     *  \brief Закрытие сессии работы с хранилищем.
     */
    uint closeSession();

    /*!
     * \brief Помещение записи в хранилище
     * \param msg запись сообщения
     * \return Возвращает результат попытки поместить запись
     */
    uint push( messageStructure msg );

    /*!
     *  \brief Получение записи из хранилища
     *  \todo  Нет реализации, так как не нужна в данной версии лога
     *         То есть вытаскивать сообщения из csv-файл не требуется
     *  \return Возвращает запись
     */
    messageStructure pop();

};

#endif // FILESTORAGE_H
