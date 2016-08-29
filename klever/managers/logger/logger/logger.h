/*!
 * \brief     Модуль журналирования.
 * \details   Модуль журналирования требуется для протоколирования событий приложения
 *            в результате эксплуатации его пользователем.
 *            При запуске ПО по-умолчанию всегда создается sys(системый) журнал.
 *            Для добавления других типов журналов, необходимо воспользоваться
 *            настройками журналов(Через модуль настроек) и прописать нужные
 *            виды журналов. Например для модулей логично создать module журнал и т.д.
 * \todo      На данный момент в качестве хранилища данных выбран csv файл.
 *            С одной стороны с ним просто работать, но с другой рождаются разного рода проблемы.
 *            Например выборка записей, вывод записей по страницам(то есть вывод
 *            на одной странице N записей, а не всех записей (может их 10^10 и
 *            тогда ПО зависнет)). Поэтому в будущем считаю необходимо переработать
 *            этот компонент ядра и в качестве хранилища делать какую-нибудь из БД.
 *            Возможно какую-нибудь орм-логику...
 * \date      2015
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "loggerdata.h"
#include "iloggerstorage.h"
#include "logtablemodel.h"


/*******************************************************************************
 *                    Основной класс реализации журнала
 *******************************************************************************/

/*!
 *  \brief Класс, реализует журнал приложения.
 *  \details
 *  \note данная реализация класса позволяет производить запись только
 *        в текстовый файл. Интерфейс реализации записи в БД не проработан.
 */
class Logger : public QObject {
  Q_OBJECT

  /*!
   *  \brief Мьютекс для создания защищенной секции.
   *  \note  запись в хранилище сообщений необходимо защищать.
   *         Так как если несколько сразу источников будет писать,
   *         какая-то информация может быть потеряна. По этой
   *         причине секцию защищают мьютексом и другой поток записи в
   *         хранилище будет ждать своей очереди.
   */
  QMutex                  _putIntoStorageOperationMutex;

    /*!
     *  \brief Внешнее хранилище данных.
     */
  ILoggerStorage         *ds;

    /*!
     *  \brief Признак включенности журнала
     */
  bool                    _isLoggerEnabled;

  /*!
   *  \brief Флаг записи сообщений через фильтр.
   *         При _hasFilterFlag = true сообщение сначало идет в фильтр, а затем
   *         выводится в tableView. При _hasFilterFlag = false наоборот.
   */
  bool                    _hasFilterFlag;

  /*!
   *  \brief Флаг редактирования записей журнала.
   *         При _isEditableFlag = true появляется возможность фильтровать
   *         сообщения в tableView. При _isEditableFlag = false нет.
   *         Этот флаг нужен для просмотрщика логов.
   */
  bool                    _isEditableFlag;

  /*!
   *  \brief Имя объекта.
   */
  QString                  objName;

  private slots:

    /*!
     * \brief Изменение модели данных. То есть добавление сообщения.
     * \note  Проверить на необходимость.
     */
    void onDataChanged( QModelIndex, QModelIndex );

    /*!
     *  \brief Запрос контекстного меню действий по фильтрации журнала.
     */
    void onContextMenuRequest( QPoint point );

  public:

   /*!
    *  \brief Конструктор класса Logger.
    */
   Logger( QObject *parent = 0,
           ILoggerStorage  *dataStorage = NULL,
           QString logPath = "",
           bool hasFilter  = false,
           bool isEditable = false,
           bool isLoggerEnabled = false
            );

   /*!
    *  \brief Хранилище данных в памяти программы.
    *  \details Содержит буффер всех сообщений и операции работы с ним.
    */
   LogTableModel          *logTableModel;

   /*!
    *  \brief Деструктор класса Logger.
    */
    ~Logger();

   /*!
    *  \brief Графическое представление журнала в виде таблицы.
    */
    QTableView *logViewer;

  public slots:
    /*!
     *  \brief Функции записи сообщений в журнал различного типа.
     *  \param[in] sender - указатель на объект-источник. Необходим для того
     *                      чтобы указать на тот объект, в котором производится
     *                      протоколирование события.
     *  \param[in] text - строка, содержит текст сообщения.
     *  \param[in] type - число, указывает тип сообщения.
     */
    virtual void logMessage( QObject *sender, QString text, MESSAGE_TYPES type );
    /*!
     *  \brief Функции записи сообщений, предупреждающих об ошибке, в журнал.
     *  \param[in] sender - указатель на объект-источник. Необходим для того
     *                      чтобы указать на тот объект, в котором производится
     *                      протоколирование события.
     *  \param[in] text - строка, содержит текст сообщения.
     */
    virtual void errorMessage( QObject *sender, QString text );
    /*!
     *  \brief Функции записи сообщений, информирующих о событии, в журнал.
     *  \param[in] sender - указатель на объект-источник. Необходим для того
     *                      чтобы указать на тот объект, в котором производится
     *                      протоколирование события.
     *  \param[in] text - строка, содержит текст сообщения.
     */
    virtual void infoMessage( QObject *sender, QString text );
    /*!
     *  \brief Функции записи предупреждающих сообщений в журнал.
     *  \param[in] sender - указатель на объект-источник. Необходим для того
     *                      чтобы указать на тот объект, в котором производится
     *                      протоколирование события.
     *  \param[in] text - строка, содержит текст сообщения.
     */
    virtual void warnMessage( QObject *sender, QString text );

};


#endif // LOGGER_H
