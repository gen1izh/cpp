#ifndef TESTSEQUENCE_EXECUTOR_WIDGET_H
#define TESTSEQUENCE_EXECUTOR_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QModelIndex>
#include <QPrintPreviewDialog>
#include <QPrinter>

#include "testsequenceexecutor.h"
#include "testsequenceexecutortreemodel.h"
#include "report/htmlrep/htmlreport.h"
#include "report/reportmodel.h"
#include "report/reportupdatethread.h"
#include "chooseserialnumberdialog.h"

#include <settings/modules/modulesmanager.h>

#include <library/processDialog/processdialog.h>


namespace Ui {
class TestsequenceExecutorWidget;
}

class TestsequenceExecutorWidget : public QWidget
{
  Q_OBJECT

  // Состояния кнопок управления запуском теста
  enum {
    INITIAL_TEST, // Начальное состояние
    START_TEST,   // Тест запущен
    STOP_TEST,    // Тест остановлен
    RESET_TEST,   // Тест перезапущен
    PAUSE_TEST,   // Тест приостановлен, на паузе
    ABORT_TEST,   // Тест сброшен
    FINISH_TEST   // Остановка теста
  };

  void createToolbar();    // Создание панели быстрого запуска
  void createActions();    // Создание действий
  void createConnectors(); // Создание коннекторов


  /*!
   * \brief Список дат для виджета календаря,
   * отмечаются те даты в которые есть отчеты.
   */
  QList<QDate> _greenCellInCalendar;

  /*!
   * \brief Установка модели
   * \param[in] m - указатель на модель
   */
  void setModels(TestsequenceExecutorTreeModel *m, ReportModel *m1) {
    _model = m;
    _reportModel = m1;
  }

  /*!
   * \brief Запуск тестовой последовательности
   */
  QAction *_startAction;

  /*!
   * \brief Пауза тестовой последовательности
   */
  QAction *_pauseAction;

  /*!
   * \brief Остановка тестовой последовательности
   */
  QAction *_stopAction;

  /*!
   * \brief Прерывание тестовой последовательности
   */
  QAction *_abortAction;

  /*!
   * \brief Таймеры для учета времени исполнения тестовой последовательности
   * и отрисовки процесса исполнения тестовой последовательности
   */
  QTimer        _updateExecTimeAndIconTimer;

  /*!
   * \brief _
   */
  QTimer        _updateReportTimer;

  /*!
   * \brief Прошедшее время исполнения тест-кейса
   */
  QTime         _elapsedExecTime;

  /*!
   * \brief Модель дерева тестовых последовательностей
   */
  TestsequenceExecutorTreeModel   *_model;

  /*!
   * \brief Указатель на модель отчетов
   */
  ReportModel *_reportModel;

  /*!
   * \brief
   */
  ReportUpdateThread     _reportUpdater;

  /*!
   * \brief Поток исполнения команд
   */
  TestsequenceExecutor     _executor;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внешнее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString _testExternalName;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внутреннее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString _testInternalName;

  /*!
   * \brief printer
   */
  QPrinter printer;

  /*!
   * \brief _prevDialog
   */
  QPrintPreviewDialog *_prevDialog;

  /*!
   * \brief Список отчетов по времени
   */
  QList<QPair <QDate, QStringList> > _reportsByTimeComboBox;

  /*!
   * \brief Обновление элементов
   * \param[in] state - состояние
   */
  void updateControls(int state);

  public:
    explicit TestsequenceExecutorWidget(QWidget *parent = 0);
    ~TestsequenceExecutorWidget();

  /*!
   * \brief Модель дерева тестовых последовательностей
   */
  TestsequenceExecutorTreeModel *model() {
    return _model;
  }

  private:
    Ui::TestsequenceExecutorWidget *ui;

  public slots:

    /*!
    * \brief Успешная финализация отчета
    */
    void successfulyFinalize();

    /*!
     * \brief Функция заполняет в виджете календаря даты в которые производилось тестирование
     */
    void createReportsCalendar(int page);

    /*!
     * \brief Запустить на исполнение тестовой последовательности
     * \return
     */
    bool start();

    /*!
     * \brief Остановить исполнение тестовой последовательности
     * \return
     */
    bool stop();

    /*!
     * \brief Авайрийно остановить исполнение тестовой последовательности
     * \return
     */
    bool abortScript();

    /*!
     * \brief Приостановить исполнение тестовой последовательности
     * \return
     */
    bool pause();

    void startedTestsequence();

    /*!
     * \brief Обновление отчета. Представление в html.
     */
    void createlSmallReport();

    /*!
     * \brief Установить текущий индекс
     * \param[in] index - модельный индекс
     */
    void setCurrentIndexInTestViewer(const QModelIndex &index);

    /*!
     * \brief Сброс времени исполнения тест-кейса
     */
    void resetTime() {
      _elapsedExecTime.restart();
    }

    /*!
     * \brief Обновление иконок
     */
    void timeout();

    /*!
     * \brief Открытие тестовой последовательности
     * \param[in] name
     */
    void openTestsequenceForExecuting(QString name);

    /*!
     * \brief Завершение исполнения тестовой последовательности
     * \return
     */
    bool testExecuted();

    /*!
     * \brief Слот загрузки
     */
    void onLoaded();

    /*!
     * \brief updateReportTimerTimeout
     */
    void updateReportTimerTimeout();

private slots:

    /*!
     * \brief Обновление иконок
     * \param[in] frame - фрейм
     */
    void updateIcon(int frame);

    /*!
     * \brief  Создание полного отчета
     */
    void on_createFullReportButton_clicked();

    /*!
     * \brief Создание краткой версии отчета
     */
    void on_createSmallReportButton_clicked();

    /*!
     * \brief Удаление отчета
     */
    void on_deleteReportButton_clicked();

    /*!
     * \brief Нажатие на календарь
     * \param[in] date - дата которую выбрали
     */
    void on_calendarWidget_clicked(const QDate &date);

    /*!
     * \brief Открытие отчета
     */
    void on_openReportButton_clicked();

    /*!
     * \brief Открытие получившегося отчета хтмл вбраузере  по-умолчанию
     */
    void on_openHtmlReportInDefaultBrowserButton_clicked();

    /*!
     * \brief Печать отчета хтмл
     */
    void on_printReportButton_clicked();

    /*!
     * \brief Сохранение хтмл отчета
     */
    void on_saveButton_clicked();

    /*!
     * \brief reportLazyLoadFinished
     */
    void resizeReportViewer();

    /*!
     * \brief on_updateReportOnTimer_stateChanged
     * \param[in] arg1
     */
    void on_updateReportOnTimer_stateChanged(int arg1);

  signals:
    /*!
     * \brief Сигнал загрузки тестовой последователдьности
     */
    void loaded();

    /*!
     * \brief Запуск тестовой последовательности
     */
    void startedTestsequenceSignal();

    /*!
     * \brief Завершения тестовой последовательности
     */
    void finishedTestsequenceSignal();

};

#endif // TESTSEQUENCE_EXECUTOR_WIDGET_H
