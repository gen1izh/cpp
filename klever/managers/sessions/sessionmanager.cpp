#include "sessionmanager.h"

SessionManager::SessionManager()
{
    Q_INIT_RESOURCE(sessionmanager_resources);
    setName(QString("session"));
    setTextName(tr("Менеджер сессий"));

    // Проверка состояния менеджера
    checkManagerState();

    createWidgets();
    createActions();
    createConnectors();
}

SessionManager::~SessionManager()
{
    finalize();
}

// Проверка существования каталога sessions
void SessionManager::checkSessionContent()
{
    SysLibrary::UtilsLibrary utils;
    // Если каталог sessions не существовал, то создаем его...
    utils.checkFolder(QString("%1//%2").arg(QDir::currentPath()).arg("sessions"));
}



// Открытие всех сессий
bool SessionManager::execute() {
    if (m_sessionsListForm->exec() == QDialog::Accepted) {
        return true;
    }

    return false;
}

// Создание виджетов
void SessionManager::createWidgets()
{
    if (m_setting==nullptr) {
        m_setting = new SettingWidget(NULL);
    }

    if (m_sessionsListForm) {
        m_sessionsListForm = new SessionsListForm(NULL);
    }

    if (m_informationDialog) {
        m_informationDialog = new InformationDialog(NULL);
    }
}

void SessionManager::createActions()
{
    // TODO: ...
}

void SessionManager::createConnectors()
{
    // TODO: ...
}

QWidget *SessionManager::getSettingPage()
{
    QWidget* wgt=static_cast<QWidget *>(m_setting);
    return wgt;
}

QIcon SessionManager::settingIcon()
{
    return QIcon(":/sessionmanager/img/settings/sessions.png");
}


// Деинициализация элементов менеджера сессии
int SessionManager::finalize() {
    // TODO: ...
}
