#include "cve.h"
#include <frameWork/cveManager.h>
#include <frameWork/gui/cvegui.h>

using namespace Core;

/*
 * Инстанцирование объекта Cve
 */
Cve &Cve::instance() {
  static Cve singleObject;
  return singleObject;
}

/*
 * Удаление объектов модулей устройств
 */
void Cve::finalize() {
  // Завершаем работу всех модулей
  ModulesManager::instance().deleteAllModules();
  // Завершаем работу всех менеджеров
  CveManager::instance().finalize();

  // Удаление всех объектов parameter из хеша
  QHashIterator<QString, Parameter *> i(_parameters);
  while (i.hasNext()) {
    i.next();
    delete i.value();
  }
}

/*
 * Открытие окна сообщений
 */
void Cve::showMessage(QString text, QString okText, QString cancelText) {
  QMessageBox msgBox;
  msgBox.setText(text);
  QPushButton *okButton     = msgBox.addButton(okText, QMessageBox::ActionRole);
  QPushButton *cancelButton = msgBox.addButton(cancelText, QMessageBox::ActionRole);

  Q_UNUSED(cancelButton)

  msgBox.exec();

  if (msgBox.clickedButton() == okButton) {
    _sysops->setShowMessageResult(true);
  } else {
    _sysops->setShowMessageResult(false);
  }

  _sysops->resetWaitUserAnswerFlag();
}

/*
 * Функция запуска проги(используется в скриптах). Запуск в потоке.
 */
void Cve::executeApplication(QString exeName, QString arguments) {
  QFuture<void> future;

  future = QtConcurrent::run(this,
                            &Cve::startApp,
                            exeName,
                            arguments);
}

/*
 * Функция запуска проги(используется в скриптах)
 */
void Cve::startApp(QString exeName, QString arguments) {
  QProcess *process = new QProcess(this);
//  QString cmd = QString("%1 %2").arg(exeName).arg(arguments);
  QFileInfo g(arguments);
  process->setWorkingDirectory(g.absolutePath());
//  qDebug() << "cmd = "<< cmd << " absolute path= " << g.absolutePath() << " arguments = " << arguments;

  QStringList args;
  args << arguments;

//  qDebug() << args << process->state();

  process->start(exeName.toStdString().c_str(),args/*cmd.toStdString().c_str()*/);
//  qDebug() << process->state();

//  process->closeWriteChannel();
  process->waitForFinished(-1);
//  qDebug() << process->readAll();
  process->close();
}

/*
 * Открыть документ сформированный
 */
void Cve::openDocument(QString filename) {
  QString _fileName;
  QString sessionPath =
      Cve::instance().getParameterValue(QString("/sessionPath"), QString(""));

  _fileName = QString("%1/%2")
      .arg(sessionPath)
      .arg(filename);

  QFileInfo file(_fileName);

  if (file.exists()) {
    QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(_fileName)));
  }
  else {
    QMessageBox msgBox;
    msgBox.setText(QString("Проблемы с открытием файла(%1)! Проверьте наличие файла.")
                   .arg(_fileName));
    msgBox.exec();
  }
}


/*
 * Инициализация настроек приложения
 */
void Cve::initializeSettings() {
  _appSettings = new AppSettings();
}


/*
 * Запуск модулей через 100 мс после прогрузки модулей
 */
void Cve::startModulesBy100ms() {
  /*
   * Отложенная инициализация
   * TODO. Нужная для порядка инициализации объектов. Требуется доработка.
   * Это связано с тем что настройки подгружаются потом.
   */

  // TODO: Убрать, проверить, должно работать без этого
  QTimer::singleShot(100,
                     &ModulesManager::instance(),
                     SLOT(instanceModulesLater()));

}






