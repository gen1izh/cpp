#include "autorizationmanager.h"

#include <library/message/messagelibrary.h>

AutorizationManager::AutorizationManager() {
    initialize(tr("autorization"), tr("Авторизация"));
}

AutorizationManager::~AutorizationManager()
{
    finalize();
}

/*
 * Вызов окна авторизации
 */
bool AutorizationManager::execute()
{
    // Инициализация моделей происходит после подключения к сессии
    if (m_settings!=NULL) {
        m_settings->d->InitializeModels();
    }

    if (m_autorizationDialog->exec() == QDialog::Accepted) {

        if (m_autorizationDialog->autorizatedSuccessful()) {
           return true;
        }
        else {
            messageLibrary msg;
            msg.createWarnMessage(tr("Предупреждение"),
                                  tr("Вы неверно ввели пароль. "
                                     "Программа будет закрыта. Повторите позже."));
           return false;
        }
    }

    messageLibrary msg;
    msg.createInfoMessage(tr("Информация"),
                          tr("Вы отменили процесс авторизации. "
                             "Программа будет закрыта."));

    return false;
}

/*
 * Создание виджетов модуля
 */
void AutorizationManager::createWidgets() {

    // Необходимо добавить остальные виджеты

    m_autorizationDialog = new AutorizationDialog();

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new autorizationSettings(NULL);
    }

}

/*
 * Деинициализация элементов плагина
 */
void AutorizationManager::finalize() {
    // TODO: ...
}


/*
 * Возвращает виджет настроек плагина
 */
QWidget *AutorizationManager::settingPage() {
    QWidget* wgt=static_cast<QWidget *>(m_settings);
    return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon AutorizationManager::settingIcon() {
    return QIcon(":/autorizationmanager/img/manager.png");
}

void AutorizationManager::createActions()
{
    // TODO: ...
}

void AutorizationManager::createConnectors()
{
    // TODO: ...
}

QString AutorizationManager::information()
{
    QString msg = "auto";

    return msg;
}



