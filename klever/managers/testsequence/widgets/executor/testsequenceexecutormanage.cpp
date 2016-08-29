#include "testsequenceexecutorwidget.h"
#include "ui_testsequenceexecutorwidget.h"

/*
 * Запустить исполнение проверки последовательности скриптов
 */
bool TestsequenceExecutorWidget::start() {

  ModulesManager::instance().allModulesOff();

  /*
   *  TODO: Тут необходимо сделать задержку на факт того что  модули действительно отключили
   */
  for (int i=0; i<100000; i++) {
    ;;;
  }

  // Прежде чем запускать тестовую последовательность
  // необходимо  ее проверить, проверить наличие скриптов

  // Выбор начального элемента дерева
  QModelIndex in = QModelIndex();
  QString result = _model->treewalkVerify(in);
  if (result.isEmpty()) {
    messageLibrary msg;
    msg.createInfoMessage(tr("Верификация"), tr("Тестовая последовательность готова к исполнению"));

    chooseSerialNumberDialog chooseSerialForm;

    QString sn = Cve::instance().getParameterValue(QString("/serialNumber"), QString("123456"));
    chooseSerialForm.setSerialNumber(sn);

    if (chooseSerialForm.exec() == QDialog::Accepted) {
      Cve::instance().setParameterValue(QString("/serialNumber"),
                                        chooseSerialForm.getSerialNumber());
    }
  }
  else {
    messageLibrary msg;
    msg.createErrorMessage(tr("Верификация"), result);
    return false;
  }

  // Остановить таймер прорисовки времени исполнения теста
  _updateExecTimeAndIconTimer.stop();
  // Очистка полей времени исполнения
  _model->treewalkExecTimeClear(QModelIndex());

  // Если исполнитель не стоит на паузе
  if (!_executor.isPausedState()) {
    // Установить времени и даты на отчет
    _executor.setReportTimeDate(QString(""));
    // Создаем таблицу отчета
    _executor.createReportTable();
    _executor._isTestStartedAfterPause = false;
    Cve::instance().setParameterValue(QString("currentItemId"), QString(""));
  }
  else {
    // Получаем значения имени теста, даты исполнения теста
    // и идентификатора последнего исполненного тест-кейса
    QString datetime = Cve::instance().getParameterValue(QString("reportTimeDate"), QString(""));
    _executor.setReportTimeDate(datetime);
    _executor._isTestStartedAfterPause = true;
  }

  // Перезапустить время прошедшее с начала запуска теста
  _elapsedExecTime.restart();
  // Создание корневого узла
  _reportModel->createReportTreeItem();

  // Перевести поток в режим исполнения теста
  _executor.setRunState();

  // Запуск таймера который будет обновлять представление отчета
  if (!ui->updateReportOnTimer->isChecked()) {
    _reportUpdater.offUpdate();
  }
  else {
    _reportUpdater.onUpdate();
  }

  updateControls(START_TEST);

  // При запуске потока исполнения теста, spinbox с временем
  // обновления отчета
  ui->updateTimeBox->setEnabled(true);

  return true;
}


/*
 * Приостановить исполнение проверки последовательности скриптов
 */
bool TestsequenceExecutorWidget::pause() {
  // Перевод потока в режим паузы
  _executor.setPausedState();

  // Получаем значения имени теста, даты исполнения теста
  // и идентификатора последнего исполненного тест-кейса
  QString testname = Cve::instance().getParameterValue(QString("testTableName"), QString("NONE"));
  QString datetime = Cve::instance().getParameterValue(QString("reportTimeDate"),QString("NONE"));
  QString id = Cve::instance().getParameterValue(QString("currentItemId"), QString("NONE"));

  // Записываем текущее состояние исполнение теста в файл настроек
  AppSetupApi appsetup;
  appsetup.setApplicationParam(QString("Testsequence"), QString("/testname"), testname);
  appsetup.setApplicationParam(QString("Testsequence"), QString("/datetime"), datetime);
  appsetup.setApplicationParam(QString("Testsequence"), QString("/id"), id);

  // Обновление кнопок старта, паузы, остановки теста
  // TODO: Нет проверки что действительно тест-кейс остановлен
  updateControls(PAUSE_TEST);

  // Остановка таймера обновления отчета
  // TODO: возможно в этом нет необходимости
  _reportUpdater.offUpdate();

  Cve::instance().setParameterValue(QString("isWasPaused"), true);

  return true;
}

/*
 * Остановить исполнение проверки последовательности скриптов
 */
bool TestsequenceExecutorWidget::stop() {

  // Получаем значения имени теста, даты исполнения теста
  // и идентификатора последнего исполненного тест-кейса
  QString testname = Cve::instance().getParameterValue(QString("testTableName"), QString("NONE"));
  QString datetime = Cve::instance().getParameterValue(QString("reportTimeDate"),QString("NONE"));
  QString id = Cve::instance().getParameterValue(QString("currentItemId"), QString("NONE"));

  _executor.setIdleState();

  if ((testname == "NONE")&&
      (datetime == "NONE")&&
      (id == "NONE")) {
     updateControls(INITIAL_TEST);
  }
  else {
    // Кнопка сброса должна быть активной, чтобы аварийно отключить исполнение скрипта.
    // Кнопки запуска, остановки, паузы должны быть не активны
    // после финализации исполнения теста, эти кнопки станут активны
    updateControls(ABORT_TEST);

    timeout(); // update to now
    _model->setIconForTimedItem();

    _reportUpdater.offUpdate();

    Cve::instance().setParameterValue(QString("EarlyExecutedOrAbortedTestcaseState"),
                                      _model->getStatusString(_model->TS_ABORTING));
  }

  return true;
}


/*
 * Аварийная остановка исполнение проверки последовательности скриптов
 */
bool TestsequenceExecutorWidget::abortScript() {
  QScriptValue result;

  _executor.setIdleState();

  qDebug().noquote() << "isEvaluating=" << Cve::instance().scriptEngine()->isEvaluating();

  // Прервать исполнение тестовой последовательности
  Cve::instance().scriptEngine()->abortEvaluation(result);

  qDebug().noquote() << "result=" << result.toString();
  qDebug().noquote() << "isEvaluating=" << Cve::instance().scriptEngine()->isEvaluating();

  // TODO: Нет проверки что действительно тест-кейс остановлен
  updateControls(STOP_TEST);

  timeout(); // update to now
  _model->setIconForTimedItem();

  _reportUpdater.offUpdate();

  Cve::instance().setParameterValue(QString("EarlyExecutedOrAbortedTestcaseState"),
                                    _model->getStatusString(_model->TS_ABORTING));

  return true;
}

/*
 * Создание полного отчета
 */
void TestsequenceExecutorWidget::on_createFullReportButton_clicked()
{
  QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
  QString productType = Cve::instance().getParameterValue(QString("/productType"), QString(""));
  QString sessionName = Cve::instance().getParameterValue(QString("/sessionName"), QString(""));

  QString fileName = QFileDialog::getSaveFileName(this,
                                  tr("Сохранить полную форму отчета..." ),
                                  QString("%1/reports").arg(sessionPath),
                                  tr("(*.html)" ) );

  if (!fileName.isEmpty()) {
    HtmlReport hr(FULL_REPORT);

    QString currentReportDateAndTime =
        Cve::instance().getParameterValue(QString("reportTimeDate"),QString(""));

    if (!currentReportDateAndTime.isEmpty()) {

      QDateTime dataTime;
      dataTime = QDateTime::fromString(currentReportDateAndTime, "yyyy_MM_dd_hh_mm_ss");

      hr.addInformation(_testExternalName,/* Название теста */
                        productType,
                        sessionName,
                        dataTime.toString("hh:mm:ss dd.MM.yyyy"));

      hr.addHeader("Результаты тестирования");
      QList<smallReportContentListStruct> content;
      _reportModel->treewalkGetAllResultsList(QModelIndex(), 1, content);
      for (int i=0; i < content.size(); i++) {
        hr.addToTree( content.at(i).level,
                      content.at(i).result,
                      content.at(i).testName,
                      content.at(i).description,
                      content.at(i).time,
                      true );
      }
    }
    if (!QDir(QString("%1/resources").arg(sessionPath)).exists()) {
      hr.createDocument(fileName, false, true);
    }
    else {
      hr.createDocument(fileName, false, false);
    }
  }
}

/*
 * Создание краткой версии отчета
 */
void TestsequenceExecutorWidget::on_createSmallReportButton_clicked()
{
  QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
  QString productType = Cve::instance().getParameterValue(QString("/productType"), QString(""));
  QString sessionName = Cve::instance().getParameterValue(QString("/sessionName"), QString(""));

  QString fileName = QFileDialog::getSaveFileName(this,
                                  tr("Сохранить краткую форму отчета..." ),
                                  QString("%1/reports").arg(sessionPath),
                                  tr("(*.html)" ) );

  if (!fileName.isEmpty()) {
    HtmlReport hr(SHORT_REPORT);

    QString currentReportDateAndTime =
        Cve::instance().getParameterValue(QString("reportTimeDate"),QString(""));

    if (!currentReportDateAndTime.isEmpty()) {

      QDateTime dataTime;
      dataTime = QDateTime::fromString(currentReportDateAndTime, "yyyy_MM_dd_hh_mm_ss");

      hr.addInformation(_testExternalName,/*Название теста*/
                        productType,
                        sessionName,
                        dataTime.toString("hh:mm:ss dd.MM.yyyy"));

      hr.addHeader("Результаты тестирования");
      QList<smallReportContentListStruct> content;
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
}


/*
 * Удаление отчета
 */
void TestsequenceExecutorWidget::on_deleteReportButton_clicked()
{
  bool ok;

  if ((ui->testListBox->currentText().isEmpty()) || (ui->testListBox->currentText() == "Пусто")) {
    return;
  }

  int hour = QString(ui->testListBox->currentText().split(QString(":")).at(0)).toInt(&ok, 10);
  int min  = QString(ui->testListBox->currentText().split(QString(":")).at(1)).toInt(&ok, 10);
  int sec  = QString(ui->testListBox->currentText().split(QString(":")).at(2)).toInt(&ok, 10);

  QString time = QString("%1_%2_%3").arg(hour, 2, 10, QChar('0'))
                                    .arg(min,  2, 10, QChar('0'))
                                    .arg(sec,  2, 10, QChar('0'));

  QString date = QString("%1_%2_%3").arg(ui->calendarWidget->selectedDate().year(),  2, 10, QChar('0'))
                                    .arg(ui->calendarWidget->selectedDate().month(), 2, 10, QChar('0'))
                                    .arg(ui->calendarWidget->selectedDate().day(),   2, 10, QChar('0'));

  QString _reportTimeDate = QString("%1_%2").arg(date).arg(time);
  Cve::instance().setParameterValue(QString("reportTimeDate"), _reportTimeDate);
  QString table = QString("report_%1_%2").arg(_reportTimeDate).arg(_testInternalName);

  if (!MySQLDataBaseApi::instance().dropTable("cve_testsequence", "testsequence_gui", table, "droptable")) {
    logWarning(this, QString("Не удалось удалить отчет!"));
  }

  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_gui", "reports", "droptable")) {
    logWarning(this, QString("Не удалось отобразить отчеты!"));
  }
  else {
    QSqlRecord rec    = MySQLDataBaseApi::instance().query()["droptable"]->record();
    int id            = rec.indexOf("id");
    int testGuiName   = rec.indexOf("Testcase_gui_name");
    int testTableName = rec.indexOf("Testcase_table_name");
    int timeAndDate   = rec.indexOf("Time_and_date");

    while (MySQLDataBaseApi::instance().query()["droptable"]->next()) {
      if (MySQLDataBaseApi::instance().query()["droptable"]->value(testGuiName).toString() == _testExternalName) {
        if (MySQLDataBaseApi::instance().query()["droptable"]->value(testTableName).toString() == _testInternalName) {
          if (MySQLDataBaseApi::instance().query()["droptable"]->value(timeAndDate).toString() == _reportTimeDate) {
            if (!MySQLDataBaseApi::instance().deleteRecordById( "cve_testsequence", "testsequence_gui", "reports",
                  MySQLDataBaseApi::instance().query()["droptable"]->value(id).toInt(&ok), "droptable")) {
                logWarning(this,QString("Не удалось отобразить отчеты!"));
            }
            break;
          }
        }
      }
    }
  }

  // Необходимо обновить комбобокс времени и даты после удаления отчета
  createReportsCalendar(0);
}


/*
 * Обработчик нажатия на календарь
 */
void TestsequenceExecutorWidget::on_calendarWidget_clicked(const QDate &date)
{
  ui->testListBox->clear();
  ui->testListBox->addItem("Пусто");

  for (int i = 0; i < _reportsByTimeComboBox.size(); i++) {
    if (date.year() == _reportsByTimeComboBox.at(i).first.year())
      if (date.month() == _reportsByTimeComboBox.at(i).first.month())
        if (date.day() == _reportsByTimeComboBox.at(i).first.day()) {
           ui->testListBox->clear();
           for (int j = 0; j < _reportsByTimeComboBox.at(i).second.size(); j++) {
             ui->testListBox->addItem(_reportsByTimeComboBox.at(i).second.at(j));
           }
          break;
        }
  }

  if (ui->testListBox->currentText()=="Пусто") {
    ui->openReportButton->setEnabled(false);
    ui->deleteReportButton->setEnabled(false);
    ui->createFullReportButton->setEnabled(false);
    ui->createSmallReportButton->setEnabled(false);
  }
  else {
    ui->openReportButton->setEnabled(true);
    ui->deleteReportButton->setEnabled(true);
    ui->createFullReportButton->setEnabled(true);
    ui->createSmallReportButton->setEnabled(true);
  }
}

/*
 * Открытие отчета
 */
void TestsequenceExecutorWidget::on_openReportButton_clicked()
{
  bool ok;

  int hour = QString(ui->testListBox->currentText().split(QString(":")).at(0)).toInt(&ok, 10);
  int min  = QString(ui->testListBox->currentText().split(QString(":")).at(1)).toInt(&ok, 10);
  int sec  = QString(ui->testListBox->currentText().split(QString(":")).at(2)).toInt(&ok, 10);

  QString time = QString("%1_%2_%3").arg(hour, 2, 10, QChar('0'))
                                    .arg(min, 2, 10, QChar('0'))
                                    .arg(sec, 2, 10, QChar('0'));

  QString date = QString("%1_%2_%3").arg(ui->calendarWidget->selectedDate().year(), 2, 10, QChar('0'))
                                    .arg(ui->calendarWidget->selectedDate().month(), 2, 10, QChar('0'))
                                    .arg(ui->calendarWidget->selectedDate().day(), 2, 10, QChar('0'));

  Cve::instance().setParameterValue(QString("reportTimeDate"), QString("%1_%2").arg(date).arg(time));

  // Удаление корневого элемента дерева
  // TODO: Тут возможна утечка памяти
  _reportModel->deleteRootItem();
  // Создание заново рутового узла дерева
  _reportModel->createReportTreeItem();
  // Загрузка тестовой последовательности
  _reportUpdater.setUpdateReportModelState();
  // Переводим поток в состояние простоя
  _reportUpdater.setIdleState();
  // Переход на вкладку с деревом отчета
  ui->reportToolBox->setCurrentIndex(1);
}

/*
 * Открытие отчета, который получен во время исполнения теста в браузере по умолчанию.
 */
void TestsequenceExecutorWidget::on_openHtmlReportInDefaultBrowserButton_clicked()
{
  QString sessionPath = Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));
  QString filepath = QString("%1/reports.html").arg(sessionPath);
  QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(filepath)));
}

/*
 * Печать отчета, представленного в виде html
 */
void TestsequenceExecutorWidget::on_printReportButton_clicked()
{
  _prevDialog->exec();
}

/*
 * Сохранение краткой версии отчета
 */
void TestsequenceExecutorWidget::on_saveButton_clicked()
{
  on_createSmallReportButton_clicked();
}

/*
 * Изменение состояния таймера обновления отчета
 */
void TestsequenceExecutorWidget::on_updateReportOnTimer_stateChanged(int arg1)
{
  Q_UNUSED(arg1)
  if (!ui->updateReportOnTimer->isChecked()) {
    _reportUpdater.offUpdate();
  }
  else {
    _reportUpdater.onUpdate();
  }
}

