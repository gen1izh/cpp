#include "analysisplugin.h"

analysisPlugin::analysisPlugin() {
    setName("analysis");
    setTextName("analysis");
    createActions();
    createWidgets();
    createConnectors();
}

void analysisPlugin::prepare() {
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
}

void analysisPlugin::createWidgets() {

    _widgetActionList[tr("(PM)BF_AnalizeForm")].first  = new BF_AnalizeForm();
    _widgetActionList[tr("(PM)BF_AnalizeForm")].second = m_BF_AnalizeForm;

    _actionList[tr("(PM)BF_TextEditorOpen")] = m_TextEditorOpen;


    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new analysisSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void analysisPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *analysisPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon analysisPlugin::settingIcon() {
    return QIcon(":/analysisplugin/img/plugin.png");
}

void analysisPlugin::createActions()
{
    m_BF_AnalizeForm = new QAction(QIcon(":/analysisplugin/img/plugin.png"),
                                   tr("&Анализ требований"), this);

    m_TextEditorOpen = new QAction();
}

void analysisPlugin::createConnectors()
{
    connect(_widgetActionList[tr("(PM)BF_AnalizeForm")].first,
            SIGNAL(openTexteditor()), m_TextEditorOpen, SIGNAL(triggered()));
}


