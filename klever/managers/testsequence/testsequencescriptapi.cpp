#include "testsequencescriptapi.h"

TestsequenceScriptApi::TestsequenceScriptApi(QObject *parent) : QObject(parent) {
}

/*
 * Получить параметр по имени в тест-кейсе
 */
QString TestsequenceScriptApi::getArg(QString name) {
  if (_item == nullptr) {

    return QString();
  }

  for (int i = 0; i < _item->params().size(); i++) {
    if (_item->params().at(i).first == name) {
      return _item->params().at(i).second;
    }
  }
  return QString("Error: No some params!");
}


QString TestsequenceScriptApi::getArg(QString name, QString defaultValue) {
  if (_item == nullptr) {

    return QString();
  }

  for (int i = 0; i < _item->params().size(); i++) {
    if (_item->params().at(i).first == name) {
      return _item->params().at(i).second;
    }
  }
  return defaultValue;
}



/*
 * Запись ошибочного сообщения в таблицу отчета
 */
void TestsequenceScriptApi::error(QString content) {
  QString reportTimeDate = Cve::instance().getParameterValue(QString("reportTimeDate"), QString(""));
  QString testTableName  = Cve::instance().getParameterValue(QString("testTableName"), QString(""));
  Cve::instance().setParameterValue(QString("TestcaseState"),QString("Ошибка"));
  QString tablename = QString("report_%1_%2").arg(reportTimeDate).arg(testTableName);

  // Проверка существования такой таблицы
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence",
                                                              "testsequence_thread", tablename, "testsequencelist")) {

    qDebug().noquote() << "Таблица с именем " << tablename <<
                          " не существует. Вы запустили скрипт не в контексте теста, поэтому таблица отчета не создана.";
    return;
  }

  if (!MySQLDataBaseApi::instance().insertIntoTable(
       "cve_testsequence", "testsequence_thread",
       QString("%1 (id, Name_node, Parent_id, Status, msg , Exec_time)").arg(tablename),
       QString("(%1,\"%2\",%3,\"%4\",\"%5\",\"%6\")")
        .arg(-1).arg(_item->name()).arg(_item->id())
        .arg(tr("Ошибка")).arg(content).arg(_item->execTime()), "testsequencelist")) {
//    logWarning(this,QString("Не удалось добавить запись в таблицу!"));
  }
}

/*
 * Запись сообщения предупреждения в таблицу отчета
 */
void TestsequenceScriptApi::warning(QString content) {
  QString reportTimeDate = Cve::instance().getParameterValue(QString("reportTimeDate"),QString(""));
  QString testTableName = Cve::instance().getParameterValue(QString("testTableName"),QString(""));
  QString TestcaseState = Cve::instance().getParameterValue(QString("TestcaseState"),QString(""));
  if (TestcaseState!="Ошибка") {
    Cve::instance().setParameterValue(QString("TestcaseState"),QString("Предупреждение"));
  }
  QString tablename = QString("report_%1_%2").arg(reportTimeDate).arg(testTableName);

  // Проверка существования такой таблицы
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence",
                                                              "testsequence_thread", tablename, "testsequencelist")) {

    qDebug().noquote() << "Таблица с именем " << tablename <<
                          " не существует. Вы запустили скрипт не в контексте теста, поэтому таблица отчета не создана.";
    return;
  }

  if (!MySQLDataBaseApi::instance().insertIntoTable(
       "cve_testsequence", "testsequence_thread",
       QString("%1 (id, Name_node, Parent_id, Status, msg , Exec_time)").arg(tablename),
       QString("(%1,\"%2\",%3,\"%4\",\"%5\",\"%6\")")
        .arg(-1).arg(_item->name()).arg(_item->id())
        .arg(tr("Предупреждение")).arg(content).arg(_item->execTime()), "testsequencelist")) {
//    logWarning(this, QString("Не удалось добавить запись в таблицу!"));
  }
}

/*
 * Запись информационного сообщения в таблицу отчета
 */
void TestsequenceScriptApi::information(QString content) {
  QString reportTimeDate = Cve::instance().getParameterValue(QString("reportTimeDate"),QString(""));
  QString testTableName = Cve::instance().getParameterValue(QString("testTableName"),QString(""));
  QString TestcaseState = Cve::instance().getParameterValue(QString("TestcaseState"),QString(""));
  if ((TestcaseState!="Ошибка") && (TestcaseState!="Предупреждение")) {
    Cve::instance().setParameterValue(QString("TestcaseState"),QString("Информация"));
  }
  QString tablename = QString("report_%1_%2").arg(reportTimeDate).arg(testTableName);

  // Проверка существования такой таблицы
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence",
                                                              "testsequence_thread", tablename, "testsequencelist")) {

    qDebug().noquote() << "Таблица с именем " << tablename <<
                          " не существует. Вы запустили скрипт не в контексте теста, поэтому таблица отчета не создана.";
    return;
  }

  if (!MySQLDataBaseApi::instance().insertIntoTable(
       "cve_testsequence", "testsequence_thread",
       QString("%1 (id, Name_node, Parent_id, Status, msg , Exec_time)").arg(tablename),
       QString("(%1,\"%2\",%3,\"%4\",\"%5\",\"%6\")")
        .arg(-1).arg(_item->name()).arg(_item->id())
        .arg(tr("Информация")).arg(content).arg(_item->execTime()), "testsequencelist")) {
//    logWarning(this, QString("Не удалось добавить запись в таблицу!"));
  }
}
