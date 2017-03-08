#include "project_manager.h"

ProjectManager::ProjectManager() {
    setName("ProjectManager");         // Установка имени плагина (внутреннее)
    setTextName("Менеджер проектов");  // Установка имени плагина (внешнее)
    m_settings = NULL;
    createActions();
    createWidgets();
}

/*
 * Создание виджетов модуля
 */
void ProjectManager::createWidgets() {

//    _widgetActionList[tr("(PM)BF_AnalizeForm")].first  = new BF_AnalizeForm();
//    _widgetActionList[tr("(PM)BF_AnalizeForm")].second = m_BF_AnalizeForm;

//    _widgetActionList[tr("(PM)BF_ArchitectForm")].first  = new BF_ArchitectForm();
//    _widgetActionList[tr("(PM)BF_ArchitectForm")].second = m_BF_ArchitectForm;

//    _widgetActionList[tr("(PM)BF_DeployBuildForm")].first  = new BF_DeployBuildForm();
//    _widgetActionList[tr("(PM)BF_DeployBuildForm")].second = m_BF_DeployBuildForm;

//    _widgetActionList[tr("(PM)BF_DocumentsForm")].first  = new BF_DocumentsForm();
//    _widgetActionList[tr("(PM)BF_DocumentsForm")].second = m_BF_DocumentsForm;


    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new SettingsForm(NULL);
    }
}

/*
 * Деинициализация элементов плагина
 */
void ProjectManager::finalize() {

}


/*
 * Возвращает виджет настроек плагина
 */
QWidget *ProjectManager::settingPage() {
    QWidget* wgt=static_cast<QWidget *>(m_settings);
    return wgt;
}

/*
 *  Возвращает иконку для настроек
 */
QIcon ProjectManager::settingIcon() {
    return QIcon(":/setting/img/project_manager.png");
}

void ProjectManager::createActions()
{
//    m_BF_AnalizeForm     = new QAction(QIcon(":/img/img/analyze.png"), tr("&Анализ требований"), this);
//    m_BF_ArchitectForm   = new QAction(QIcon(":/img/img/architect.png"), tr("&Структура системы"), this);
//    m_BF_DeployBuildForm = new QAction(QIcon(":/img/img/build.png"), tr("&Сборка установщика"), this);
//    m_BF_DocumentsForm   = new QAction(QIcon(":/img/img/documentation.png"), tr("&Документация"), this);
}

QString ProjectManager::information()
{
    QString msg = "project_manager";

    return msg;
}



