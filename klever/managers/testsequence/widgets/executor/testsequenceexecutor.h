#ifndef TESTSEQUENCE_EXECUTOR_THREAD_H
#define TESTSEQUENCE_EXECUTOR_THREAD_H

/*!
 * \brief   Исполнитель тестовой последовательности
 * \details Данный класс реализует поток исполнения тестовой последоавтельности
 * \date    2015
 */

#include <QThread>
#include <interfaces/ilogger.h>

#include "testsequenceexecutortreemodel.h"
#include "testsequencedebugger.h"

#include "report/reportmodel.h"


/*!
 * \brief Класс потока исполнителя тестовой последовательности
 */
class TestsequenceExecutor : public QThread {

  Q_OBJECT

  void createConnectors();

  /*!
   * \brief Состояние потока
   */
  int _state;

  /*!
   * Состояния потока исполнения тестовой последовательности
   */
   enum {
     EXECUTOR_PAUSED,     // исполнение тестовой последовательности приостановлено
     EXECUTOR_RUN,        // исполнение тестовой последовательности начато
     EXECUTOR_IDLE,       // исполнение тестовой последовательности не происходит
     EXECUTOR_TERMINATE   // завершение работы потока
   };

   /*!
    * Состояние изменения состояния таймера подсчета времени исполнения скрипта теста
    */
   enum {
     TIMER_RESET,
     TIMER_START,
     TIMER_STOP
   };

   /*!
    * \brief Дата создания отчета (для создания каталога)
    */
   QString _reportTimeDate;

   /*!
    * \brief Название тестовой последовательности открытой для редактирования(внешнее представление)
    * Если создаем тест, то первоначально это поле будет пустым
    */
   QString *_testExternalName;

   /*!
    * \brief Название тестовой последовательности открытой для редактирования(внутреннее представление)
    * Если создаем тест, то первоначально это поле будет пустым
    */
   QString *_testInternalName;

   /*!
    * \brief Модель дерева тестовых последовательностей
    */
   TestsequenceExecutorTreeModel   *_model;

   /*!
    * \brief Указатель на модель отчетов
    */
   ReportModel *_reportModel;

   /*!
    * \brief Указатель на отладчик в тестовой последовательности
    */
   TestSequenceDebugger     *_debugger;

   /*!
    * \brief Запись содержимого в файл телеметрией ( содержимое по тест-кейсу ).
    * \param content
    */
   void writeTelemetryReport( QString content );

   /*!
    * \brief Проход по всему дереву тестовой последовательности
    * \param index
    */
   void execTestSequence( const QModelIndex &index );

   /*!
    * \brief Помещаем текущий тест-кейс в трубу
    * \param[in] item - тест-кейс
    */
   void pushTestcaseToTube(TestsequenceExecutorTreeItem *item);

   /*!
    * \brief Проверка наличия скрипта
    * \param[in] item - тест-кейс
    * \param[in] contents - содержание скрипта
    * \return
    */
   bool isFileScriptExist(TestsequenceExecutorTreeItem *item, QString &contents);

   /*!
    * \brief Установка текущего модельного индекса и тест-кейса в модель
    * \param[in] id - модельный индекс текущего тест-кейса
    * \param[in] item - текущий тест-кейс
    */
   void setCurrentIndexItemInModel(QModelIndex &id, TestsequenceExecutorTreeItem *item);

   /*!
    * \brief Изменение состояния таймера
    * \param[in] state - состояние
    */
   void changeTimerState(QModelIndex &id, int state);

   /*!
    * \brief Исполнение скрипта
    */
   void executeScript(QModelIndex &indexCurrent, TestsequenceExecutorTreeItem *item, QString contents);

   /*!
    * \brief Вставка тест-кейса в отчет
    * \param[in] item - элемент тест-кейс
    */
   void insertTestcaseIntoReport(TestsequenceExecutorTreeItem *item);

  signals:

    /*!
     * \brief Cигнал завершения исполнения тестовой последовательности
     */
    void finish();

    /*!
     * \brief Установка текущего указателя для viewer
     */
    void scrollTo( const QModelIndex & );

    /*!
     * \brief Cвернуть и развернуть  тестовую последовательность
     */
    void collapseAndExpandView();

    /*!
     * \brief Cброс времени таймера
     */
    void resetTime();

    /*!
     * \brief Запуск таймера длительности исполнения скрипта
     */
    void startTime();

    /*!
     * \brief Остановка таймера длительности исполнения скрипта
     */
    void stopTime();

    /*!
     * \brief Успешная финализация
     */
    void testExecuted();

    /*!
     * \brief Сигнал запуска тестовой последовательности
     */
    void startTestsequence();

  public:
    /*!
     * \brief Конструктор потока исполнения тестовой последовательности
     */
    TestsequenceExecutor();

    /*!
     * \brief Деструктор потока исполнения тестовой последовательности
     */
     ~TestsequenceExecutor() {
       setTerminateState();
     }

    /*!
     * \brief Флаг того что тест запущен после остановки
     */
    bool _isTestStartedAfterPause;

    /*!
     * \brief Установка моделей
     * \param[in] m  - модель исполнения тестовой последовательности
     * \param[in] m1 - модель отчета
     * \details При проходе по тестовой последовательности нужно
     *  обращаться к элементам модели.
     */
    void setModels(TestsequenceExecutorTreeModel *m, ReportModel *m1) {
      _model = m;
      _reportModel = m1;
    }

    /*!
     * \brief Возвращает время и дату начала исполнения отчета
     * \return
     */
    QString reportTimeDate() {
      return _reportTimeDate;
    }

    /*!
     * \brief Установка указателя на внешнее имя тестовой последовательности
     * \param[in] name - название
     */
    void setTestsequenceExternalName(QString *name) { _testExternalName = name; }

    /*!
     * \brief Установка указателя на внутреннее имя тестовой последовательности
     * \param[in] name - название
     */
    void setTestsequenceInternalName(QString *name) { _testInternalName = name; }

    /*!
     * \brief Запуск потока
     */
    void run();

    /*!
     * \brief Создание таблицы отчета
     */
    void createReportTable();

    /*!
     * \brief Установка времени начала исполнения тестовой последовательности.
     */
    void setReportTimeDate(QString timedate);

    /*!
     * \brief Установка состояния IDLE
     */
    void setIdleState() {
      _state = EXECUTOR_IDLE;
    }

    /*!
     * \brief Установка состояния TERMINATE
     */
    void setTerminateState();

    /*!
     * \brief Установка состояния RUN
     */
    void setRunState() {
      _state = EXECUTOR_RUN;
    }

    /*!
     * \brief Установка состояния PAUSED
     */
    void setPausedState() {
      _state = EXECUTOR_PAUSED;
    }

    /*!
     * \brief Проверка состояния IDLE
     * \return
     */
    bool isIdleState() {
      if ( _state == EXECUTOR_IDLE ) {
        return true;
      }
      else {
        return false;
      }
    }

    /*!
     * \brief Проверка состояния RUN
     * \return
     */
    bool isRunState() {
      if ( _state == EXECUTOR_RUN ) {
        return true;
      }
      else {
        return false;
      }
    }

    /*!
     * \brief Проверка состояния PAUSED
     * \return
     */
    bool isPausedState() {
      if ( _state == EXECUTOR_PAUSED ) {
        return true;
      }
      else {
        return false;
      }
    }

    /*!
     * \brief Отключение всех модулей
     * \return
     */
    void allModulesOff();

    /*!
     * \brief Включение всех модулей
     * \return
     */
    void allModulesOn();
};


#endif // TESTSEQUENCE_EXECUTOR_THREAD_H
