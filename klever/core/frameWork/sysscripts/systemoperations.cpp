#include "systemoperations.h"
#include <frameWork/cve.h>


/*
 * Установка текущего для исполнения тест-кейса
 */
SystemOperations::SystemOperations() {
 _fileName.clear();
 _e = NULL;
  msgNumber = 0;
  //checkDatabaseAndTables();
}

/*
 * Подключить другие модули
 */
void SystemOperations::includeScript(QString fileName) {

  if (!QDir::isAbsolutePath(fileName)) {
    QScriptContextInfo contextInfo(_e->currentContext()->parentContext());
    fileName = QFileInfo(contextInfo.fileName()).path() + '/' + fileName;

    QChar ch = fileName.at(0);
    // Убиваем относительный путь
    if( ch == QChar('/')) {
      fileName = fileName.right(fileName.size()-1);
    }

    if (QDir::isRelativePath(fileName)) {
      // TODO: надо со всеми согласовать
      fileName = QString("%1/files/scripts/%2").arg(QDir::currentPath()).arg(fileName);
    }

    if (!QFileInfo(fileName).exists())
        return;
  }



  QFile file ( fileName );

  if ( file.open ( QFile::ReadOnly ) ) {
   QByteArray line = file.readAll();
   file.close();
   QString contents = QString::fromUtf8 ( line );

   _e->currentContext()->setActivationObject (
         _e->currentContext()->parentContext()->activationObject() );

   _e->evaluate ( contents, QFileInfo(file).absoluteFilePath() );
  }
}

/*
 * Задержка в миллесекундах
 */
void SystemOperations::msleep(int value) {
  QThread::msleep(value);
}

/*
 * Установка имени источника журналирования
 */
void SystemOperations::setMeName(QString name) {
  setObjectName(name);
}

/*
 * Получение имени источника журналирования
 */
QString SystemOperations::getMyName() {
  return objectName();
}

/*
 *  Задержка в секундах
 */
void SystemOperations::sleep(int value) {
  QTime timer;
  timer.start();
  while(timer.elapsed() < value) {
    ;;;
  }
}

/*
 * Прекращение исполнения тестовой последовательности
 */
void SystemOperations::exitFromTestsequence() {
  Cve::instance().setParameterValue(QString("exitFromTestsequence"), true);
}

/*
 * Возвращает текущую дату
 */
QString SystemOperations::getCurrentDate() {
  return QDateTime::currentDateTime().toString("dd:MM:yyyy");
}

/*
 * Возвращает текущее время
 */
QString SystemOperations::getCurrentTime() {
  return QDateTime::currentDateTime().toString("hh:mm:ss");
}


/*
 * Отображение сообщения пользователю
 */
void SystemOperations::showMessage(QString text, QString okText, QString cancelText) {
  _waitAnswerFlag = true;
  emit showMessageSignal(text,okText,cancelText);
}

/*
 * Выполнение приложения
 */
void SystemOperations::executeApplication(QString exeName, QString arguments) {
  emit executeApp(exeName,arguments);
}

/*
 * Открыть документ
 */
void SystemOperations::openDoc(QString filename) {
  emit openDocument(filename);
}

/*
 * Получение пути до сессии
 */
QString SystemOperations::getSessionPath() {
  return Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));;
}

QString SystemOperations::getSerialNumber(){
  return Cve::instance().getParameterValue(QString("/serialNumber"), QString(""));
}

QString SystemOperations::getStringParameter(QString name) {
  return Cve::instance().getParameterValue(name, QString(""));
}

void SystemOperations::setStringParameter(QString name, QString value) {
   Cve::instance().setParameterValue(name, value);
}

int SystemOperations::getElapsedTime() {
   QString tmp = Cve::instance().getParameterValue("/funcBeginTime", QString(""));
   QStringList tmpList = tmp.split(":");
   if (tmpList.size() < 3)
       return 0;

   int h = tmpList.at(0).toInt();
   int m = tmpList.at(1).toInt();
   int s = tmpList.at(2).toInt();

   QTime timeBegin(h, m, s);

   QTime currentTime;
   currentTime = QTime::currentTime();

   return currentTime.secsTo(timeBegin)*(-1);
}
