#include "testsequenceexecutor.h"

// Глобальные объекты
#include <QHashIterator>
#include <frameWork/cveManager.h>
#include <frameWork/cve.h>
#include <frameWork/gui/cvegui.h>

/*
 * Установка времени начала исполнения тестовой последовательности.
 */
void TestsequenceExecutor::setReportTimeDate(QString timedate) {

  if (timedate==QString("")) {
    _reportTimeDate =
        QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
    Cve::instance().setParameterValue(QString("reportTimeDate"),_reportTimeDate);
  }
  else {
    _reportTimeDate = timedate;
  }

}

/*
 * Установить состояние отключения
 */
void TestsequenceExecutor::setTerminateState() {
  _state = EXECUTOR_TERMINATE;
     /*
      * Эта операция нужна для того чтобы правильно завершить функцию run
      * до удаления объекта потока из памяти
      */
  if (!wait(1000)) {
    logWarning(this,QString("Таймаут отключения потока исполнения скрипта!"));
  }
}

/*
 * Создание таблицы отчета
 */
void TestsequenceExecutor::createReportTable() {

  QString tablename;

  tablename = QString("report_%1_%2").arg(_reportTimeDate).arg(*_testInternalName);

  // Проверка существования таблицы тестовых последовательностей
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence", "testsequence_thread", tablename, "testsequencelist")) {
    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_thread", tablename,
                                             "(id INT, Name_node TEXT, Parent_id INT,"
                                             "Status TEXT, msg TEXT, Exec_time TEXT)", "testsequencelist");
  }

  // Добавляем в таблицу reports запись
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence", "testsequence_thread", "reports", "testsequencelist")) {
    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_thread",
                                             "reports",
                                             "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, "
                                             "Testcase_table_name TEXT, Testcase_gui_name TEXT,"
                                             "Time_and_date TEXT)", "testsequencelist");
  }

  if (!MySQLDataBaseApi::instance().insertIntoTable(
           "cve_testsequence", "testsequence_thread",
           QString("reports"),
           QString("(NULL,'%1','%2','%3')")
                 .arg(*_testInternalName)
                 .arg(*_testExternalName)
                 .arg(_reportTimeDate), "testsequencelist")) {

    logWarning(this,QString("Не удалось добавить запись в таблицу!"));
  }
}


/*
 * Конструктор для дебаггера в тестовых последовательностях
 */
TestsequenceExecutor::TestsequenceExecutor() /*:
    _debugger(new TestSequenceDebugger)*/
{
  setObjectName("Поток исполнения скриптов");

  setIdleState(); // установка состояния простоя
}

/*
 * Запуск исполнения скриптов
 */
void TestsequenceExecutor::run() {
  // Устанавливаем признак исполнения тестовой последовательности
  bool isExecuting = true;
  QModelIndex index = QModelIndex();
  bool isIdled = false;

  while(isExecuting) {
    switch (_state) {
      case EXECUTOR_RUN:
        isIdled = false;
        Cve::instance().setParameterValue(QString("testStarted"),   true);
        Cve::instance().setParameterValue(QString("testTableName"),*_testInternalName);

        // Результат исполнения тестовой последовательности (информация,
        // предупреждение, ошибка)
        Cve::instance().setParameterValue(QString("TestResult"), QString(""));

        // Например тест выполнен был ранее или пропущен (при этом эти состояния не информация,
        // предупреждения, ошибки). Это уточнение для TestResult.
        Cve::instance().setParameterValue(QString("EarlyExecutedOrAbortedTestcaseState"), QString(""));

        // Сбросили состояние  тест-кейса
        Cve::instance().setParameterValue(QString("TestcaseState"), QString(""));

        emit startTestsequence();
        // Исполнение всей тестовой последовательности
        execTestSequence(QModelIndex());
        changeTimerState(index, TIMER_STOP);
        emit testExecuted();

        break;

      case EXECUTOR_IDLE:
        if (!isIdled) {
          Cve::instance().setParameterValue(QString("testStarted"), false);
          isIdled = true;
        }
        msleep(500);
        break;

      case EXECUTOR_TERMINATE:
        isExecuting = false;
        break;

      default:
        break;
    };
  }
}


/*
 * Проход по всему дереву тестовой последовательности
 */
void TestsequenceExecutor::createConnectors()
{
}

/*
 * Помещаем текущий тест-кейс в трубу
 */
void TestsequenceExecutor::pushTestcaseToTube(TestsequenceExecutorTreeItem *item)
{
  QVariant testcaseItemVariantType;
  testcaseItemVariantType.fromValue(static_cast<QList< QPair <QString, QString> > >(item->params()));
  Cve::instance().setParameterValue(QString("currentTestsequenceItem"), testcaseItemVariantType);
}

/*
 * Проверка наличия скрипта
 */
bool TestsequenceExecutor::isFileScriptExist(TestsequenceExecutorTreeItem *item, QString &contents) {
  // Формируем путь до скрипта
  QString scriptPath = QString("%1/files/scripts%2").arg(QDir::currentPath()).arg(item->path());

  // Открытие файла скрипта
  QFile scriptFile(scriptPath);

  // Открытие файла скрипта
  if (scriptFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream stream(&scriptFile);
    // Получение содержимого файла скрипта
    contents = stream.readAll();
    scriptFile.close();
    return true;
  }
  return false;
}

/*
 * Установка текущего модельного индекса и тест-кейса в модель
 */
void TestsequenceExecutor::setCurrentIndexItemInModel(QModelIndex &id, TestsequenceExecutorTreeItem *item) {
  // Запись временого индекса элемента тест-кейса.
  // Это необходимо для прорисовки времени исполнения тест-кейса.
  _model->currentExecIndex = id;

  // Запись временого элемента тест-кейса.
  // Это необходимо для прорисовки премени исполнения тест-кейса.
  _model->currentExecItem = item;
  _model->script()->setItem(item);
}

/*
 * Изменение состояния таймера
 */
void TestsequenceExecutor::changeTimerState(QModelIndex &id, int state) {
  switch (state) {
  case TIMER_RESET:
    // Сигнал сброса таймера.
    // Находится в этом месте, чтобы производить сброс таймера при переходе на следующий
    // Тест-кейс. Если убрать, то время исполнения тест-кейсов будет происходить
    // неверно.
    emit resetTime();
    // Установка текущего индекса в view.
    emit scrollTo(id);
    break;
  case TIMER_START:
    // Запуск таймера длительности исполнения скрипта
    emit startTime();
    break;
  case TIMER_STOP:
    // Остановка таймера длительности исполнения скрипта
    emit stopTime();
    // Установка состояния простоя цикла.
    // Перевод в состояние EXECUTOR_IDLE
    setIdleState();
    // Сигнал завершения исполнения тестовой последовательности
    emit finish();
    Cve::instance().setParameterValue(QString("exitFromTestsequence"), false);

    break;

  default:
    break;
  };

  msleep(1);
}


/*
 * Исполнение скрипта
 */
void TestsequenceExecutor::executeScript(QModelIndex &indexCurrent,
                                         TestsequenceExecutorTreeItem *item,
                                         QString contents) {
  // Непосредственное исполнение скрипта (либо в отладке, либо напрямую)
  QScriptValue value;
  // TODO: КРЕШИТСЯ первая строчка
//  _debugger->setEngine(Cve::instance().scriptEngine());
//  _debugger->setProgram(contents, item->path());
//  if (item->debugBreak()) {
//      QEventLoop loop;
//      QTimer::singleShot(0, _debugger, SLOT(exec()));
//      connect(_debugger, SIGNAL(finished()), &loop, SLOT(quit()));
//      item->setStatus(_model->getStatusString(_model->TS_DEBUG));
//      loop.exec();
//      value = _debugger->result();
//  } else {
    value = Cve::instance().scriptEngine()->evaluate(contents, item->path());

    // Проверить наличие ошибок при исполнении скрипта
    if (value.isError()) {
      // Установили состояние текущего тест-кейса
      item->setStatus(_model->getStatusString(_model->TS_EXEC_FAIL));
      logError(this,QString("%1").arg(value.toString()));
      Cve::instance().setParameterValue(QString("TestcaseState"), QString("Ошибка"));
    }
    else {
      // Установили состояние текущего тест-кейса
      // Если скрипт вернул значение TC_FAIL, значит произошла Error.
      if ( value.toNumber() !=
          _model->TC_FAIL) {
        item->setStatus(_model->getStatusString(_model->TS_EXEC_SUCCESS));
      }
      else {
        item->setStatus(
              _model->getStatusString(_model->TS_EXEC_FAIL) );
        Cve::instance().setParameterValue(QString("TestcaseState"), QString("Ошибка"));
      }
    }
    // Проверяем состояние тест-кейса
    QString testcaseState = Cve::instance().getParameterValue(
                                                      QString("TestcaseState"),
                                                      QString(""));

    // Проверяем состояние теста
    QString testResult = Cve::instance().getParameterValue(QString("TestResult"), QString(""));

    if ((testcaseState == "Ошибка") && (testResult != "Ошибка")) {
      Cve::instance().setParameterValue(QString("TestResult"), QString("Ошибка"));
    }

    if ((testcaseState == "Предупреждение") && (testResult != "Ошибка")) {
      Cve::instance().setParameterValue(QString("TestResult"), QString("Предупреждение"));
    }

    if ((testcaseState == "Информация") && ((testResult != "Ошибка")||(testResult != "Предупреждение"))) {
      Cve::instance().setParameterValue(QString("TestResult"), QString("Информация"));
    }

    // Если в скрипте протоколировались ошибки в журнал или отчет,
    // то устанавливаем ветку дерева в состояние "Ошибки"
    if (testcaseState == "Ошибка") {
      item->setStatus(_model->getStatusString(TestsequenceExecutorTreeModel::TS_EXEC_FAIL));
      bool isNeedAbort = Cve::instance().getParameterValue(QString("AbortAfterError"), false);
      if (isNeedAbort) {
        changeTimerState(indexCurrent, TIMER_STOP);
      }
      else {
        Cve::instance().setParameterValue(QString("TestcaseState"), QString(""));
      }
    }

//  }
}

/*
 * Вставка тест-кейса в отчет
 */
void TestsequenceExecutor::insertTestcaseIntoReport(TestsequenceExecutorTreeItem *item) {
  int id;

  QString tablename = QString("report_%1_%2").arg(_reportTimeDate).arg(*_testInternalName);
  if (_model->currentExecIndex.parent() == QModelIndex()) {
    id = 0;
  }
  else {
    id = item->parent()->id();
  }

  if (!MySQLDataBaseApi::instance().insertIntoTable(
       "cve_testsequence", "testsequence_thread",
       QString("%1 (id, Name_node, Parent_id, Status, msg , Exec_time)").arg(tablename),
       QString("(%1,\"%2\",%3,\"%4\",\"%5\",\"%6\")")
        .arg(item->id()).arg(item->name()).arg(id)
        .arg(tr("")).arg(tr("")).arg(tr("")), "testsequencelist")) {
//    logWarning(this,QString("Не удалось добавить запись в таблицу!"));
  }

}

/*
 * Основная функция исполнения теста
 */
void TestsequenceExecutor::execTestSequence(const QModelIndex &index) {

  QModelIndex indexCurrent;
  QString     contents;
  bool        ok;

  QString pausedId = Cve::instance().getParameterValue(QString("currentItemId"), QString("-1"));

  // Перебор всех тест-кейсов в тестовой последовательности
  for (int row = 0; row < _model->rowCount(index); ++row) {
    // Получение модельного индекса тест-кейса
    indexCurrent = _model->index(row, 0, index);

    // Получение тест-кейса по модельному индексу
    TestsequenceExecutorTreeItem *item = _model->itemForIndex(indexCurrent);

    if (item->status()==_model->getStatusString(_model->TS_SKIPED)) {
      // Установка текущего идентификатора тест-кейса, который исполняется
      Cve::instance().setParameterValue(QString("currentItemId"), QString("%1").arg(item->id()));
      // Установка текущего модельного индекса и тест-кейса в модель
      setCurrentIndexItemInModel(indexCurrent, item);
      // Вставить элемент тест-кейса в таблицу отчета
      insertTestcaseIntoReport(item);
      item->setExecTime(QString("0:00:00:000"));
    }
    else {

      bool isContinue = false;
      if (pausedId.toInt(&ok, 10)!=-1) {
        if (item->id()<=pausedId.toInt(&ok, 10)) {
          item->setStatus(_model->getStatusString(_model->TS_EXECUTED_EARLY));
          Cve::instance().setParameterValue(QString("EarlyExecutedOrAbortedTestcaseState"),
                                            _model->getStatusString(_model->TS_EXECUTED_EARLY));
          isContinue = true;
        }
      }

      if (!isContinue) {
        // Установка текущего идентификатора тест-кейса, который исполняется
        Cve::instance().setParameterValue(QString("currentItemId"), QString("%1").arg(item->id()));

        // Установка текущего модельного индекса и тест-кейса в модель
        setCurrentIndexItemInModel(indexCurrent, item);

        if (!_isTestStartedAfterPause) {
          // Вставить элемент тест-кейса в таблицу отчета
          insertTestcaseIntoReport(item);
        }

        // Если узел содержит скрипт и должен быть исполнен, то
        // инициализируем время исполнения нулем
        if (!item->path().isEmpty()) {
          item->setExecTime(QString("0:00:00:000"));
        }

        // Помещаем текущий тест-кейс в трубу
        pushTestcaseToTube(item);
        // Изменение состояния таймера
        changeTimerState(indexCurrent, TIMER_RESET);

        // Читаем признак того что надо отменить исполнение тестовой последовательности
        bool isNeedAbort = Cve::instance().getParameterValue(QString("exitFromTestsequence"), false);

        // Исполнение скрипта
        if ((isRunState())&&(!isNeedAbort)) {
          // Проверка существования файла скрипта
          if (isFileScriptExist(item, contents)) {
            // Установили состояние текущего тест-кейса
            item->setStatus(_model->getStatusString(_model->TS_EXECUTING));
            changeTimerState(indexCurrent, TIMER_START);
            // Помещаем текущий тест-кейс в трубу
            pushTestcaseToTube(item);
            // Исполнение скрипта
            executeScript(indexCurrent, item, contents);
          }
        } else {

          if (isPausedState()) {
            // Приостановка исполнения теста
            item->setStatus(_model->getStatusString(_model->TS_PAUSED) );
          }
          else {
            // Отмена исполнения теста. Из скрипта пользователь вызвал функцию прекращения исполенения.
            item->setStatus(_model->getStatusString(_model->TS_ABORTING) );
            Cve::instance().setParameterValue(QString("EarlyExecutedOrAbortedTestcaseState"),
                                              _model->getStatusString(_model->TS_ABORTING));
          }
        }
      }
    }
    // Рекурсивный вызов. Поиск дочерних для id индекса.
    execTestSequence(indexCurrent);
  }

}
