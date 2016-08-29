#include "testsequenceexecutorwidget.h"
#include "ui_testsequenceexecutorwidget.h"


TestsequenceExecutorWidget::TestsequenceExecutorWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TestsequenceExecutorWidget)
{
  ui->setupUi(this);

  setObjectName("Исполнитель тестовой последовательности");

  bool ok;

  _updateReportTimer.setInterval(ui->updateTimeBox->text().toInt(&ok,10)*1000);
  // Настройка таймеров
  _updateExecTimeAndIconTimer.setInterval(600);

  // Настройка потока исполнения тестовой последовательности
  _executor.setTestsequenceExternalName(&_testExternalName);
  _executor.setTestsequenceInternalName(&_testInternalName);
  // Запуск потока исполнения тестовой последовательности в режиме простоя
  _executor.setIdleState();
  _executor.start();

  // Настройка потока обновления отчета
  _reportUpdater.setTestsequenceExternalName(&_testExternalName);
  _reportUpdater.setTestsequenceInternalName(&_testInternalName);
  _reportUpdater.setIdleState();
  _reportUpdater.start();

  // Создания представления тестовой последовательности
  setModels(new TestsequenceExecutorTreeModel(this),
            new ReportModel(this));

  _model->setTestsequenceExternalName(&_testExternalName);
  _model->setTestsequenceInternalName(&_testInternalName);

  _reportModel->setTestsequenceExternalName(&_testExternalName);
  _reportModel->setTestsequenceInternalName(&_testInternalName);

  _executor.setModels(_model, _reportModel);
  _reportUpdater.setModels(_model, _reportModel);

  ui->testView->setModel(_model);
  ui->reportView->setModel(_reportModel);
  ui->testView->setContextMenuPolicy(Qt::CustomContextMenu);

  ui->testView->setColumnWidth(0, 300);  // Установили ширину первой колонки (Название)
  ui->testView->setColumnWidth(1, 30);   // Установили ширину второй колонки (брейк-поинт)
  ui->testView->setColumnWidth(2, 200);  // Установили ширину третей колонки (состояния)
  ui->testView->setColumnWidth(3, 200);  // Установили ширину четвертой колонки (время исполнения)

  ui->openHtmlReportInDefaultBrowserButton->setVisible(false);
  ui->printReportButton->setVisible(false);
  ui->saveButton->setVisible(false);

  // При первоначальном запуске ПО спинбокс отвечающий за время срабатывания таймера
  // при обновлении отчета не доступен
  ui->updateTimeBox->setEnabled(false);

  // Подготовка принтера к работе
  _prevDialog = new QPrintPreviewDialog(&printer);

  createActions();
  createConnectors();
  createToolbar();

  setWindowIcon(QIcon(":/testsequence/img/testsequence.png"));

  AppSetupApi appsetup;
  appsetup.checkApplicationParam(QString("Testsequence"), QString("/testname"), QString("NONE"));
  appsetup.checkApplicationParam(QString("Testsequence"), QString("/datetime"), QString("NONE"));
  appsetup.checkApplicationParam(QString("Testsequence"), QString("/id"), QString("NONE"));

  // Настройка названий заголовков окон, хотелка Стерхова
  QString executorWindowName = appsetup.getApplicationParam(QString("Testsequence"),
                                                                QString("/executorWindowNameEdit"));
  QString chooseReportTabName = appsetup.getApplicationParam(QString("Testsequence"),
                              QString("/chooseReportTabNameEdit"));

  QString reportHtmlTabName = appsetup.getApplicationParam(QString("Testsequence"),
                              QString("/reportHtmlTabNameEdit"));

  QString reportTabName = appsetup.getApplicationParam(QString("Testsequence"),
                              QString("/reportTabNameEdit"));

  // Установка название таба Отчета
  ui->tabWidget->setTabText(1, reportTabName);
  // Установка название таба Отчета Html
  ui->tabWidget->setTabText(2, reportHtmlTabName);
  // Установка названия для вкладки Тулбокса (календарь отчетов)
  ui->reportToolBox->setItemText(0, chooseReportTabName);
  // Установка название окна
  setWindowTitle(executorWindowName);

}

TestsequenceExecutorWidget::~TestsequenceExecutorWidget()
{

  _reportUpdater.setTerminateState();

  while (_reportUpdater.isRunning()) {
    ;;;
  }

  delete _prevDialog;
  delete ui;
}

void TestsequenceExecutorWidget::createActions()
{
  // Запуск тестовой последовательности скриптов
  // -------------------------------------------------
  _startAction = new QAction(QIcon(":/testsequence/img/start.png"), tr("&Запуск..."),NULL);
  _startAction->setShortcut(QKeySequence( Qt::CTRL + Qt::Key_F5));
  _startAction->setStatusTip(tr("Запуск на исполнение тестовой последовательности"));
  // -------------------------------------------------

  // Пауза тестовой последовательности скриптов
  // -------------------------------------------------
  _pauseAction = new QAction(QIcon(":/testsequence/img/pause.png"), tr("&Пауза..."), NULL);
  _pauseAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F6));
  _pauseAction->setStatusTip(tr("Пауза исполнения тестовой последовательности"));
  // -------------------------------------------------

  // Остановка тестовой последовательности скриптов
  // -------------------------------------------------
  _stopAction = new QAction(QIcon(":/testsequence/img/stop.png"), tr("&Остановка..."), NULL);
  _stopAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F7));
  _stopAction->setStatusTip(tr("Остановка исполнения тестовой последовательности"));
  // -------------------------------------------------

  // Прекращение тестовой последовательности скриптов
  // -------------------------------------------------
  _abortAction = new QAction(QIcon(":/testsequence/img/abort.png"), tr("&Аварийная остановка..."), NULL);
  _abortAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F8));
  _abortAction->setStatusTip(tr("Аварийная остановка исполнения тестовой последовательности"));
  // -------------------------------------------------
}

/*
 * Создание коннекторов
 */
void TestsequenceExecutorWidget::createConnectors()
{
  // Запуск на исполнение тестовой последовательности
  connect(_startAction, SIGNAL(triggered()), this, SLOT(start()));

  // Пауза исполнения тестовой последовательности
  connect(_pauseAction,SIGNAL(triggered()), this, SLOT(pause()));

  // Остановка исполнения тестовой последовательности
  connect(_stopAction, SIGNAL(triggered()), this, SLOT(stop()));

  // Аварийная остановка исполнения тестовой последовательности
  connect(_abortAction, SIGNAL(triggered()), this, SLOT(abortScript()));

  // Сигнал завершения исполнения тестовой последовательности
  connect(&_executor, SIGNAL(finish()), this, SLOT(testExecuted()));

  // Сигнал запуска таймера отрисовки процесса исполнения теста
  // в тестовой последовательности
  connect(&_executor, SIGNAL(startTime()), &_updateExecTimeAndIconTimer, SLOT(start()));


  connect(&_executor, SIGNAL(startTime()), &_updateReportTimer, SLOT(start()));

  // Остановка таймера отрисовки процесса исполнения теста для тестовой последовательности
  connect(&_executor, SIGNAL(stopTime()), &_updateReportTimer, SLOT(stop()));

   connect(&_executor, SIGNAL(stopTime()), &_updateExecTimeAndIconTimer, SLOT(stop()));

  // Сигнал сброса таймера
  // Сброс переменной учета прошедшего времени, требуется при переходах
  // от одного теста к другому
  connect(&_executor, SIGNAL(resetTime()), this, SLOT(resetTime()));

  // Завершение исполнения тестовой последовательности
  connect(&_executor, SIGNAL(testExecuted()), this, SLOT(successfulyFinalize()));

  // Запуск на исполнение тестовое последовательности
  connect(&_executor, SIGNAL(startTestsequence()), this, SLOT(startedTestsequence()));

  // Сигнал таймера.
  // Обновление времени исполнения скрипта и иконки процесса исполнения.
  connect(&_updateExecTimeAndIconTimer, SIGNAL(timeout()), this, SLOT(timeout()));

  connect(&_updateReportTimer, SIGNAL(timeout()), this, SLOT(updateReportTimerTimeout()));


  // Смена текущего индекса исполнения в дереве тестовой последовательности
  connect(&_executor, SIGNAL(scrollTo(const QModelIndex &)),
           this, SLOT(setCurrentIndexInTestViewer(const QModelIndex &)));

  // Сигнал загрузки модели
  connect(_model, SIGNAL(loaded()), this, SLOT(onLoaded()));

  //----------------------------------------------------------------------------

  // Перепостроение миниотчета на html
  connect(&_reportUpdater, SIGNAL(updateModel()), this, SLOT(createlSmallReport()));

  // Ресайз вьювера отчетов, после операции обновления
  connect(&_reportUpdater, SIGNAL(updateModel()), this, SLOT(resizeReportViewer()));

  // Изменение времени обновления отчета
  connect(ui->updateTimeBox, SIGNAL(valueChanged(int)), &_reportUpdater, SLOT(setTimeout(int)));

  // Открытие диалогового окна для печати отчета
  connect(_prevDialog, SIGNAL(paintRequested(QPrinter*)), ui->htmlReportWebView, SLOT(print(QPrinter*)));

  // Открытие календаря с отчетами
  connect(ui->reportToolBox, SIGNAL(currentChanged(int)), this, SLOT(createReportsCalendar(int)));

}

/*
 * Создание панели быстрого запуска для основных функций работы
 * с тестовой последовательностью
 */
void TestsequenceExecutorWidget::createToolbar() {
  ui->startPanel->setIconSize(QSize(50,50));
  ui->startPanel->addAction(_startAction);
  ui->startPanel->addAction(_stopAction);
  ui->startPanel->addAction(_abortAction);
  ui->startPanel->addAction(_pauseAction);
  ui->startPanel->addSeparator();
}

/*
 * Функция заполняет в виджете календаря даты в которые производилось тестирование
 */
void TestsequenceExecutorWidget::createReportsCalendar(int page)
{

  Q_UNUSED(page)

  QPair <QDate, QStringList> p;
  _reportsByTimeComboBox.clear();
  QTextCharFormat cellFormat;

  for ( int i = 0; i < _greenCellInCalendar.size(); i++) {
    cellFormat.setBackground(Qt::white);
    ui->calendarWidget->setDateTextFormat(_greenCellInCalendar.at(i), cellFormat);
  }

  _greenCellInCalendar.clear();

  // Создаем таблицу списка отчетов если ее нет
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence", "testsequence_gui", "reports", "testsequencelist")) {
    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui",
                                             "reports",
                                             "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, "
                                             "Testcase_table_name TEXT, Testcase_gui_name TEXT,"
                                             "Time_and_date TEXT)", "testsequencelist");
    return;
  }

  // Проход по таблице дерева тестовой последовательности
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_gui", "reports", "testsequencelist")) {
    logWarning(this,
               QString("Не удалось подгрузить отчет из БД(%1)!")
               .arg(MySQLDataBaseApi::instance().getDescriptor("cve_testsequence", "testsequence_gui").lastError().text()));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["testsequencelist"]->record();

    if (MySQLDataBaseApi::instance().query()["testsequencelist"]->size() > 0) {
      while (MySQLDataBaseApi::instance().query()["testsequencelist"]->next()) {
        p.first = QDate();
        p.second.clear();

        QString timeAndDate =
            MySQLDataBaseApi::instance().query()["testsequencelist"]->value(rec.indexOf("Time_and_date")).toString();

        QString testcaseTableName =
            MySQLDataBaseApi::instance().query()["testsequencelist"]->value(rec.indexOf("Testcase_table_name")).toString();

        if (testcaseTableName ==_testInternalName) {
          bool ok;

          int year  = QString(timeAndDate.split("_").at(0)).toInt(&ok,10); // Год
          int month = QString(timeAndDate.split("_").at(1)).toInt(&ok,10); // Месяц
          int day   = QString(timeAndDate.split("_").at(2)).toInt(&ok,10); // Дни

          int hour  = QString(timeAndDate.split("_").at(3)).toInt(&ok,10); // Часы
          int min   = QString(timeAndDate.split("_").at(4)).toInt(&ok,10); // Минуты
          int sec   = QString(timeAndDate.split("_").at(5)).toInt(&ok,10); // Секунды

          QString time = QString("%1:%2:%3").arg(hour).arg(min).arg(sec);
          const QDate reportDate(year, month, day);

          bool isReportAlreadyExist = false;

          for (int i = 0; i < _reportsByTimeComboBox.size(); i++) {
            if (year == _reportsByTimeComboBox.at(i).first.year())
              if (month == _reportsByTimeComboBox.at(i).first.month())
                if (day == _reportsByTimeComboBox.at(i).first.day()) {
                  isReportAlreadyExist = true;
                  p.first  = reportDate;
                  QStringList tmp = _reportsByTimeComboBox.at(i).second;
                  tmp.append(time);
                  p.second = tmp;
                  _reportsByTimeComboBox.removeAt(i);
                  _reportsByTimeComboBox.append(p);
                }
          }

          if (!isReportAlreadyExist) {
            p.first  = reportDate;
            p.second.clear();
            p.second.append(time);
            _reportsByTimeComboBox.append(p);
          }

          cellFormat.setBackground(Qt::green);
          ui->calendarWidget->setDateTextFormat(reportDate, cellFormat);
          _greenCellInCalendar.append(reportDate);

        }

      }
    }
  }

  on_calendarWidget_clicked(ui->calendarWidget->selectedDate());

}


/*
 * Создание мини отчета
 */
void TestsequenceExecutorWidget::createlSmallReport() {
  QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
  QString productType = Cve::instance().getParameterValue(QString("/productType"), QString(""));
  QString sessionName = Cve::instance().getParameterValue(QString("/sessionName"), QString(""));

  QString fileName = QString("%1/reports.html").arg(sessionPath);

  if (!fileName.isEmpty()) {

    HtmlReport hr(SHORT_REPORT);

    QString currentReportDateAndTime =
        Cve::instance().getParameterValue(QString("reportTimeDate"), QString(""));

    if (!currentReportDateAndTime.isEmpty()) {

      QDateTime dataTime;
      dataTime = QDateTime::fromString(currentReportDateAndTime, "yyyy_MM_dd_hh_mm_ss");

      hr.addInformation(_testExternalName, /*Название теста*/
                        productType,
                        sessionName,
                        dataTime.toString("hh:mm:ss dd.MM.yyyy"));

      hr.addHeader("Результаты тестирования");
      QList<smallReportContentListStruct> content;
      content.clear();
      _reportModel->treewalkGetMainResultsList(QModelIndex(), 1, content);
      for (int i=0; i < content.size(); i++) {

        hr.addElement(content.at(i).result,
                      content.at(i).testName,
                      content.at(i).time);
      }
    }

    if (!QDir(QString("%1/resources").arg(sessionPath)).exists()) {
      hr.createDocument(fileName, false, true);
    }
    else {
      hr.createDocument(fileName, false, false);
    }
  }

  ui->htmlReportWebView->load(QUrl::fromLocalFile(fileName));

  ui->openHtmlReportInDefaultBrowserButton->setVisible(true);
  ui->printReportButton->setVisible(true);
  ui->saveButton->setVisible(true);
}


/*
 * Сигнал загрузки тестовой последовательности
 */
void TestsequenceExecutorWidget::onLoaded() {
  // TODO: костыль
  // Без этой строки тествьювер будет пустым, после загрузки
  // данных в модель, ресайз - обновляет  тест вью
  // Возможно нужно использовать надо как-то
  // _model->dataChanged(QModelIndex(),QModelIndex());
  ui->testView->resizeColumnToContents(2);
  ui->testView->setCurrentIndex(QModelIndex());
}



/*
 * Открытие тестовой последовательности для исполнения
 */
void TestsequenceExecutorWidget::openTestsequenceForExecuting(QString name) {
  _testExternalName = name;

  _testInternalName = _model->getTestsequenceStructureName();

  Cve::instance().setParameterValue(QString("currentItemId"), QString(""));

  AppSetupApi appsetup;
  QString testname = appsetup.getApplicationParam(QString("Testsequence"), QString("/testname"));
  QString datetime = appsetup.getApplicationParam(QString("Testsequence"), QString("/datetime"));
  QString id = appsetup.getApplicationParam(QString("Testsequence"), QString("/id"));

  if ((testname == "NONE")&&
      (datetime == "NONE")&&
      (id == "NONE")) {
     updateControls(INITIAL_TEST);
     _executor.setIdleState();
  }
  else {
    if (QString("testcase_structure_%1").arg(testname)==_testInternalName) {
      updateControls(PAUSE_TEST);
      _executor.setPausedState();

      // Получаем значения имени теста, даты исполнения теста
      // и идентификатора последнего исполненного тест-кейса
      Cve::instance().setParameterValue(QString("testTableName"), testname);
      Cve::instance().setParameterValue(QString("reportTimeDate"),datetime);
      Cve::instance().setParameterValue(QString("currentItemId"), id);
    }
    else {
      updateControls(INITIAL_TEST);
      _executor.setIdleState();
    }
  }

  // Загрузили в модель дерево теста
  _model->load();
}


/*
 * Запуск тестовой последовательности
 */
void TestsequenceExecutorWidget::startedTestsequence()
{
  emit startedTestsequenceSignal();
}

/*
 * Успешная финализация отчета
 */
void TestsequenceExecutorWidget::successfulyFinalize() {
  // спинбокс обновления таймера обновления отчета
  ui->updateTimeBox->setEnabled(false);

  _reportUpdater.onUpdate();

  // Запрос состояния тестовой последовательности после исполнения
  QString testResult = Cve::instance().getParameterValue(QString("TestResult"), QString(""));

  // Если был тест ранее выполнен полностью или прерван, то тут будет об этом информация
  QString testCommonState = Cve::instance().getParameterValue(
        QString("EarlyExecutedOrAbortedTestcaseState"), QString(""));

  // Рекурсивно проставляем время и состояния тесткейсов
  _reportUpdater.setRecursiveSetStatesState();

  // Чтение отчета в дерево отчета теста
  _reportUpdater.setUpdateReportModelState();

  // Проставка среднего времени
  if ((testResult == "Информация")&&(testCommonState.isEmpty())) {
    messageLibrary msg;
    if (msg.createQuestionMessage(tr("Успех!"), tr("Тест выполнен успешно!"
                                                   " Хотите актуализировать среднее время исполнения?"))
        == QMessageBox::Yes) {
      // Актуализация среднего времени
      _reportUpdater.setRecursiveSetTimeState();
    }
  }

  // Переводим поток в состояние простоя
  _reportUpdater.setIdleState();

  // Тест дошел до конца, то есть он не на паузе
  if (_executor._isTestStartedAfterPause) {
    // Записываем пустоту состояние исполнение теста в файл настроек
    AppSetupApi appsetup;
    appsetup.setApplicationParam(QString("Testsequence"), QString("/testname"), "NONE");
    appsetup.setApplicationParam(QString("Testsequence"), QString("/datetime"), "NONE");
    appsetup.setApplicationParam(QString("Testsequence"), QString("/id"), "NONE");
    _executor._isTestStartedAfterPause = false;
  }

  emit finishedTestsequenceSignal();
}


/*
 * Завершение исполнения тестовой последовательности
 */
bool TestsequenceExecutorWidget::testExecuted() {

  _executor.setIdleState();

  bool isWasPaused = Cve::instance().getParameterValue(QString("isWasPaused"), false);

  if (!isWasPaused) {
    updateControls(FINISH_TEST);
  }
  else {
    updateControls(PAUSE_TEST);
  }

  _reportUpdater.setUpdateReportModelState();

  // Переводим поток в состояние простоя
  _reportUpdater.setIdleState();

  _model->setIconForTimedItem();
  ModulesManager::instance().allModulesOn();

  return true;
}


/*
 * Обновление элементов
 */
void TestsequenceExecutorWidget::updateControls(int state) {
  switch (state) {
    case INITIAL_TEST:
      _startAction->setIcon(QIcon(":/testsequence/img/start.png"));
      _startAction->setEnabled(true);
      _pauseAction->setEnabled(false);
      _stopAction->setEnabled(false);
      _abortAction->setEnabled(false);
    break;
    case ABORT_TEST:
      _startAction->setIcon(QIcon(":/testsequence/img/start.png"));
      _startAction->setEnabled(false);
      _pauseAction->setEnabled(false);
      _stopAction->setEnabled(false);
      _abortAction->setEnabled(true);
    break;
    case START_TEST:
      _startAction->setIcon(QIcon(":/testsequence/img/start.png"));
      _startAction->setEnabled(false);
      _pauseAction->setEnabled(true);
      _stopAction->setEnabled(true);
      _abortAction->setEnabled(true);
      break;
    case STOP_TEST:
      _startAction->setIcon(QIcon(":/testsequence/img/start.png"));
      _startAction->setEnabled(true);
      _stopAction->setEnabled(false);
      _abortAction->setEnabled(false);
      _pauseAction->setEnabled(false);
      break;
    case PAUSE_TEST:
      _startAction->setIcon(QIcon(":/testsequence/img/restart.png"));
      _startAction->setEnabled(true);
      _pauseAction->setEnabled(false);
      _stopAction->setEnabled(true);
      _abortAction->setEnabled(true);
      break;
    case FINISH_TEST:
      _startAction->setIcon(QIcon(":/testsequence/img/start.png"));
      _startAction->setEnabled(true);
      _pauseAction->setEnabled(false);
      _stopAction->setEnabled(false);
      _abortAction->setEnabled(false);
      break;

    default:
      break;
  };
}

/*
 * Обновление иконок
 */
void TestsequenceExecutorWidget::updateIcon(int frame) {
  // 5 - число фреймов анимации процесса исполнения скрипта
  if (frame > 5) {
    return;
  }
  QIcon icon(QString( ":/testsequence/img/%1.png").arg(frame));
  _model->setIconForTimedItem(icon);
}


/*
 *
 */
void TestsequenceExecutorWidget::updateReportTimerTimeout() {

  if (!ui->updateReportOnTimer->isChecked()) {
    _reportUpdater.offUpdate();
  }
  else {
    _reportUpdater.onUpdate();
    // Рекурсивно проставляем время и состояния тесткейсов
    _reportUpdater.setRecursiveSetStatesState();

    // Чтение отчета в дерево отчета теста
    _reportUpdater.setUpdateReportModelState();
  }

}

/*
 * Обновление иконок времени исполнения тест-кейса
 */
void TestsequenceExecutorWidget::timeout() {

  // Изменить ширину колонки состояния исполнения тестовой последовательности
  ui->testView->resizeColumnToContents(_model->Status);

  // Подсчет времени исполнения тестовой последовательности (часы, минуты, секунды)
  int hour = ( ( ( ( _elapsedExecTime.elapsed() / 1000 ) / 60 ) / 60 ) % 24 );
  int min  = ( ( ( _elapsedExecTime.elapsed() / 1000 ) / 60 ) ) % 60 ;
  int sec  = ( _elapsedExecTime.elapsed() / 1000 ) % 60;
  int msec = ( _elapsedExecTime.elapsed() % 1000 );

  QString time = QString("%1:%2:%3:%4")
                .arg(hour)
                .arg(min,  2, 10, QChar('0'))
                .arg(sec,  2, 10, QChar('0'))
                .arg(msec, 3, 10, QChar('0'));

  // Записать значение времени исполнения в модель
  _model->currentExecItem->setExecTime(time);

  // Установка времени исполнения для тест-кейса по идентификатору
  _reportModel->setExecTimeToReportById(_model->currentExecItem->id(),
                                        _model->currentExecItem->execTime());

  // Обновить иконку состояния
  updateIcon(sec % (5)); // 5 - число фреймов анимации процесса исполнения скрипта

  // Уведомление изменения состояния состояния
  _model->announceItemChanged(_model->currentExecItem);

}

/*
 * Обработка окончания загрузки отчета
 */
void TestsequenceExecutorWidget::resizeReportViewer()
{
  ui->reportView->expandAll();
  ui->reportView->resizeColumnToContents(0);
  ui->reportView->resizeColumnToContents(1);
  ui->reportView->collapseAll();
}

/*
 * Установить текущий индекс
 */
void TestsequenceExecutorWidget::setCurrentIndexInTestViewer(const QModelIndex &index) {
  if (index.isValid()) {
    ui->testView->scrollTo(index);
    ui->testView->setCurrentIndex(index);
  }
}
