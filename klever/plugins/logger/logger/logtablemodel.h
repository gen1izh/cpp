#ifndef LOGTABLEMODEL_H
#define LOGTABLEMODEL_H

#include "loggerdata.h"
#include "customfilterdialog.h"

/*******************************************************************************
 *                    Модель данных сообщений.
 *******************************************************************************/

/*!
 *  \brief Класс, реализует модель журнала приложения.
 *  \details
 */
class LogTableModel : public QAbstractTableModel {
      Q_OBJECT

    /**************************************************************************
     *                  Действия по работе с журналом
     **************************************************************************/
    /*!
     *  \brief Действие по фильтрации по информационным сообщениям.
     */
    QAction *_infoMessageFilterAct;

    /*!
     *  \brief Действие по фильтрации по сообщениям предупреждений.
     */
    QAction *_warnMessageFilterAct;

    /*!
     *  \brief Действие по фильтрации сообщений ошибок.
     */
    QAction *_errMessageFilterAct;

    /*!
     *  \brief Действие по выводу всех типов сообщений.
     */
    QAction *_allMessageFilterAct;

    /*!
     *  \brief Действие по фильтрации сообщений по источнику.
     */
    QAction *_sourceMessageFilterAct;

    /*!
     *  \brief Действие по очистке всех сообщений.
     */
    QAction *_deleteAllMessageAct;

    /*!
     *  \brief Действие открытию журнала сообщений.
     */
    QAction *_openReportAct;

    /*!
     *  \brief Действие по фильтрации по дате и времени.
     */
    QAction *_dateMessageFilterAct;

    /*!
     *  \brief Создание действий для модуля журналирования.
     */
    void createActions();

    /*!
     *  \brief Создание соединений для модуля журналирования.
     */
    void createConnections();

    /*!
     *  \brief Флаг изменения содержания параметров.
     */
    bool          _isParamChanged;

    /*!
     *  \brief Дата и время начальной границы фильтрации.
     */
    QDateTime     _dtimeStart;

    /*!
     *  \brief Дата и время конечной границы фильтрации.
     */
    QDateTime     _dtimeStop;

    /*!
     *  \brief Флаг необходимости фильтрации по времени.
     */
    bool          _isOnDataTimeFilterFlag;

    /*!
     *  \brief Тип сообщения.
     */
    MESSAGE_TYPES _msgType;

    /*!
     *  \brief  Карта источников событий для фильтрации по ним.
     */
    MessagesSourcesMap    _mapSources;

    /*!
     *  \brief
     */
    MESSAGE_TYPES_FILTR_FLAGS _filterFlags;

    /*!
     *  \brief Фильтрация по типу сообщений.
     */
    void filterByMsgType(messageStructure msg , bool isWatcher);

    /*!
     *  \brief Проверка на наличие даты сообщения временному промежутку.
     */
    bool isMsgInFiltredTimeAndDateRange( messageStructure msg );

    /*!
     *  \brief Буфер нефильтрованных записей.
     *  \note "Сырые данные" при протоколировании события содержатся в этом буфере.
     */
    QList<messageStructure> _noFiltredMessageBuffer;

    /*!
     * \brief Буфер всех отфильтрованных записей.
     * \details При просмотре журнала сообщений все сообщения, после фильтрации
     * поступают в этот список, затем эти данные используются для заполенения
     * _filtredMessageBuffer.
     */
    QList<messageStructure> _fullFiltredMessageBuffer;

    /*!
     *  \brief Буфер записей, для непосредственного отображения.
     */
    QList<messageStructure> _filtredMessageBuffer;

    /*!
     * \brief _openReportState
     */
    bool _openReportState;
    /*!
     * \brief _openReportState
     */
    bool _filtrReportState;

    /*!
     *  \brief Счетчик сообщений в модели.
     *  \details  Необходим для того чтобы вести счет текущего количества отображенных
     * данных в таблице представления журнала. Зависит от PAGE_SIZE.
     */
    int _messagesCount;

    /*!
     * \brief Dialog
     */
    QDialog *_openReportProcessDialog;

    /*!
     * \brief _filtrReportProcessDialog
     */
    QDialog *_filtrReportProcessDialog;

  public:

  /*!
   *  \brief Список всех действий, надо для PopMenu
   */
  QList<QAction*> msgTypeFilterActionsList;

  /*!
   *  \brief Конструктор класса.
   */
    explicit LogTableModel( QObject *parent = 0 );

  /*!
   *  \brief Деструктор класса.
   */
    ~LogTableModel();

  /*!
   *  \brief Деструктор класса.
   */
    void addMessage( messageStructure msg );
  /*!
   *  \brief Возвращает данные хранящиеся под role.
   */
    QVariant data( const QModelIndex &index, int role ) const;

    /*!
     *  \brief Sets the role data for the item at index to value.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    /*!
     *  \brief Формирование заголовка таблицы.
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /*!
     *  \brief Возвращает количество столбцов таблицы.
     */
    int columnCount(const QModelIndex &parent) const;

    /*!
     *  \brief возвращает количество строк.
     */
    int rowCount(const QModelIndex &parent) const;

    /*!
     *  \brief
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*!
     *  \brief
     */
//    MESSAGE_TYPES_FILTR_FLAGS filter_flags();


    /*!
     *  \brief
     */
    void setFilterFlags( MESSAGE_TYPES_FILTR_FLAGS a_filter_flags );

    /*!
     *  \brief Очистка таблицы.
     */
    void clearTable();

    /*!
     *  \brief Фильтрация по источнику.
     */
    void filterBySource(messageStructure msg , bool isWatcher);

    /*!
     *  \brief Выдача сигнала изменения данных.
     */
//    void dataChangedSignal();

    /*!
     *  \brief Добавить строку сообщения.
     */
    void insertRow( messageStructure msg );

    /*!
     * \brief Вставка записей в буфер _fullFiltredMessageBuffer
     * \param Содержимое записи.
     */
    void insertRowForWatcher( messageStructure msg );

    /*!
     * \brief Начало вставки строк записей
     */
    void lock();

    /*!
     * \brief Окончание вставки строк записей
     */
    void unlock();

    /*!
     * \brief openReportByQtConcurrent
     * \param fileName
     */
    void openReportByQtConcurrent(QString fileName);

    /*!
     * \brief filtrReportByQtConcurrent
     */
    void filtrReportByQtConcurrent();

public slots:

    /*!
     *  \brief Открытие диалогового окна фильтрации данных
     */
    void filtrReport();

    /*!
     *  \brief Очистка открытых журналов
     *  \details Производит очистку всех вспомогательных буферов с записями.
     */
    void clearReport();

    /*!
     *  \brief Открытие журнала
     *  \details Производит заполнение буферов записями из хранилища
     */
    void openReport();

    /*!
     * \brief Открытие старница журнала в просмторщике
     * \param Индексный номер страницы
     * \return Возвращает индекс страницы, либо если произошел выход за границы страниц,
     * то выводит границу(0 или page_counts).
     */
    int openOnePageOfReport(int pageIndex , int *pages);

    /*!
     *  \brief Обработчик нажатия на combobox с типом сообщений
     *  \details
     */
    void onChanged_msgTypeComboBox(QString type);

  private slots:

    /*!
     *  \brief Функция фильтрации сообщений в журнале по типу ошибочных.
     *  \note Оставляет только ошибочные.
     */
//    void filterByErrorMsg();
    /*!
     *  \brief Функция фильтрации сообщений в журнале по типу предупреждающих.
     *  \note Оставляет только сообщения с предупреждением.
     */
//    void filterByWarnMsg();
    /*!
     *  \brief Функция фильтрации сообщений в журнале по типу информирующих.
     *  \note Оставляет только информационные сообщения.
     */
//    void filterByInfoMsg();
    /*!
     *  \brief Функция фильтрации сообщений в журнале
     *  \note Оставляет все сообщения.
     */
//    void filterByAllMsg();

signals:
    /*!
     * \brief openReportByQtConcurrentFinished
     */
    void openReportByQtConcurrentFinished();

    /*!
     * \brief filtrReportByQtConcurrentFinished
     */
    void filtrReportByQtConcurrentFinished();

    /*!
     * \brief setPageCountsAndCurrentPageSignal
     * \param i
     * \param count
     */
    void setPageCountsAndCurrentPageSignal(int i, int count);
};

#endif // LOGTABLEMODEL_H
