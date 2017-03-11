#include "texteditorplugin.h"

texteditorPlugin::texteditorPlugin() {
    setName("texteditor");
    setTextName("texteditor");
    createActions();
    createWidgets();
}

void texteditorPlugin::createWidgets() {

    _widgetActionList[tr("(PM)TextEditor")].first  = new EditorForm();
    _widgetActionList[tr("(PM)TextEditor")].second = m_TextEditor;

    // Создание виджета настроек
    if (m_settings==NULL) {
        m_settings = new texteditorSettings(NULL);
    }

    // Необходимо добавить остальные виджеты

}

/*
 * Деинициализация элементов
 */
void texteditorPlugin::finalize() {

}


/*
 * Возвращает виджет настроек
 */
QWidget *texteditorPlugin::settingPage() {
    return static_cast<QWidget *>(m_settings);
}

/*
 *  Возвращает иконку для настроек
 */
QIcon texteditorPlugin::settingIcon() {
    return QIcon(":/texteditorplugin/img/plugin.png");
}

void texteditorPlugin::createActions()
{
    m_TextEditor = new QAction(QIcon(":/texteditorplugin/img/plugin.png"),
                                   tr("&Текстовый редактор"), this);
}


