#include "architectplugin.h"

architectPlugin::architectPlugin() {
    setName("architect");
    setTextName("architect");
    createActions();
    createWidgets();
    createConnectors();
}

void architectPlugin::prepare() {
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
}

void architectPlugin::createWidgets() {

    _widgetActionList[tr("(PM)BF_ArchitectForm")].first  = new BF_ArchitectForm();
    _widgetActionList[tr("(PM)BF_ArchitectForm")].second = m_BF_ArchitectForm;

    _actionList[tr("(PM)BF_TextEditorOpen")] = m_TextEditorOpen;

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new architectSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void architectPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *architectPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon architectPlugin::settingIcon() {
    return QIcon(":/architectplugin/img/plugin.png");
}

void architectPlugin::createActions()
{
    m_BF_ArchitectForm   = new QAction(QIcon(":/architectplugin/img/plugin.png"),
                                       tr("&Структура системы"), this);

    m_TextEditorOpen = new QAction();
}

void architectPlugin::createConnectors()
{
    connect(_widgetActionList[tr("(PM)BF_ArchitectForm")].first,
            SIGNAL(openTexteditor()), m_TextEditorOpen, SIGNAL(triggered()));
}




