#include "base.h"
#include <frameWork/plugins.h>
#include <frameWork/gui/klevergui.h>
#include <QtConcurrent>

int Core::Base::initializeDatabase()
{
    m_db = new QSqlDatabase( QSqlDatabase::addDatabase("QODBC", "klever") );
    m_db->setDatabaseName("DRIVER={SQL Server};SERVER=.\\SQLEXPRESS;DATABASE=klever;Trusted_Connection=yes;");
    m_db->setUserName("sa");
    m_db->setPassword("111");

    if (!m_db->open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_db->lastError().text());
        msg.createErrorMessage("Ошибка", text);
        return -1;
    }
    return 1;
}

QSqlDatabase *Core::Base::database() {
    return m_db;
}

void Core::Base::closeDatabase() {
    m_db->close();
    QSqlDatabase::removeDatabase("klever");
}



int Core::Base::initializeSessionDatabase(const QString &name)
{
    m_session_db = new QSqlDatabase( QSqlDatabase::addDatabase("QODBC", name) );
    m_session_db->setDatabaseName(QString("DRIVER={SQL Server};SERVER=.\\SQLEXPRESS;DATABASE=%1;Trusted_Connection=yes;").arg(name));
    m_session_db->setUserName("sa");
    m_session_db->setPassword("111");

    if (!m_session_db->open()) {
        messageLibrary msg;
        QString text;
        text = QString("%1. %2").arg("Не удалось открыть БД").arg(m_session_db->lastError().text());
        msg.createErrorMessage("Ошибка", text);
        return -1;
    }
    return 1;
}

QSqlDatabase *Core::Base::sessionDatabase() {
    return m_session_db;
}

void Core::Base::closeSessionDatabase() {
    QString name = m_session_db->databaseName();
    m_session_db->close();
    QSqlDatabase::removeDatabase(name);
}




Core::Base::Base()
{
    setObjectName(tr("Система"));

    _sysops               = new SystemOperations();
    _scriptEvaluteEngine  = new QScriptEngine();

    QScriptValue value = _scriptEvaluteEngine->newQObject(_sysops);


    _value.append(value);
    _scriptEvaluteEngine->globalObject().setProperty(tr("iam"), value);

    // Передаем указатель на движок qtscript.
    // Необходим для реализации функции setEngine.
    _sysops->setEngine(_scriptEvaluteEngine);

    connect(_sysops, SIGNAL(showMessageSignal(QString,QString,QString)),
            this, SLOT(showMessage(QString,QString,QString)));

    connect(_sysops, SIGNAL(executeApp(QString,QString)),
            this, SLOT(executeApplication(QString,QString)));

    connect(_sysops, SIGNAL(openDocument(QString)),
            this, SLOT(openDocument(QString)));

}

// Инстанцирование объекта Cve
Core::Base &Core::Base::instance() {
    static Base singleObject;
    return singleObject;
}


// Завершаем работу всех плагинов
int Core::Base::finalize() {
    // Завершаем работу всех плагинов
    Plugins::instance().finalize();

    // Удаление всех объектов parameter из хеша
    QHashIterator<QString, Parameter *> i(_parameters);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }

    closeDatabase();

    return 0;
}


// Открытие окна сообщений
void Core::Base::showMessage(QString text, QString okText, QString cancelText) {
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
void Core::Base::executeApplication(QString exeName, QString arguments) {
    QFuture<void> future;

    future = QtConcurrent::run(this,
                               &Base::startApp,
                               exeName,
                               arguments);
}

/*
 * Функция запуска проги(используется в скриптах)
 */
void Core::Base::startApp(QString exeName, QString arguments) {
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
void Core::Base::openDocument(QString filename) {
    QString _fileName;
    QString sessionPath =
            Base::instance().getParameterValue(QString("/sessionPath"), QString(""));

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
void Core::Base::initializeSettings() {
    _appSettings = new AppSettings();
}

int Core::Base::load()
{
    return 0;
}

