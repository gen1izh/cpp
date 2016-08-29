#ifndef MODULE_THREAD_H
#define MODULE_THREAD_H

#include <QDebug>
#include <QList>
#include <QThread>
#include <QUndoCommand>

/*!
 * \brief Поток модуля
 * Необходим для отвязки длительных команд от ГИП (чтоб зависаний не было)
 */
class ModuleThread : public QThread
{
    Q_OBJECT

    /*!
     * \brief Соятояние потока
     */
    int state;

    enum {
      WORKING = 0,
      TERMINATE
    };

  public:

    explicit ModuleThread( QObject *parent = 0 );
    ~ModuleThread();

    /*!
     * \brief Таймаут на в потоке в случае отсутствия команд
     */
    int timeoutValHi;

    /*!
     * \brief Таймаут на в потоке в случае наличия команд
     */
    int timeoutValLo;

    /*!
     * \brief Таймаут на ожидание команды
     */
    quint32 timeout;

    /*!
     * \brief Проверка на то что поток находится в рабочем состоянии
     * \return
     */
    bool isWorking() const;

    /*!
     * \brief Установка потока в рабочее состояние
     */
    void setWorkingState();

    /*!
     * \brief Отключение работы цикла потока
     */
    void setTerminateState();

    /*!
     * \brief setTimeout Устанавливает таймауты между выполнением команд для потока модуля
     * \param[in] timeoutValHi_ Таймаут при непустом списке
     * \param[in] timeoutValLo_ Таймаут при пустом списке
     */
    void setTimeout(int timeoutValHi_ = 500, int timeoutValLo_ = 10);

    /*!
     * \brief getTimeout Возвращает значение таймаутов
     * \param[out] timeoutValHi_ Таймаут при непустом списке
     * \param[out] timeoutValLo_ Таймаут при пустом списке
     */
    void getTimeout(int *timeoutValHi_ = NULL, int *timeoutValLo_ = NULL) const;

    /*!
     * \brief Признак того что  список команд пустой
     * \return
     */
    bool isCommandsListEmpty() const;

  protected:

    /*!
     * \brief список команд
     */
    QList<QUndoCommand*>  commandsList;

    /*!
     * \brief  Основное тело потока
     */
    void run();

    /*!
     * \brief Фоновые операции
     */
    virtual void execBackgroundOperations() = 0;
};

#endif // MODULE_THREAD_H
