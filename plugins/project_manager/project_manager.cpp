#include "project_manager.h"

#include "../_shared/db/models/architectelement.h"
#include "../_shared/db/models/architectlinks.h"
#include "../_shared/db/models/architecttypealias.h"
#include "../_shared/db/models/comment.h"
#include "../_shared/db/models/docelement.h"
#include "../_shared/db/models/glossaryelement.h"
#include "../_shared/db/models/imageselement.h"
#include "../_shared/db/models/requirementelement.h"
#include "../_shared/db/models/termselement.h"

ProjectManager::ProjectManager() {
    setName("ProjectManager");         // Установка имени плагина (внутреннее)
    setTextName("Менеджер проектов");  // Установка имени плагина (внешнее)
    m_settings = NULL;
    createActions();
    createWidgets();
}

void ProjectManager::prepare() {
    QDjango::setDatabase(*Core::Base::instance().sessionDatabase());
    QDjango::registerModel<RequirementElement>();
    QDjango::registerModel<ArchitectElement>();
    QDjango::registerModel<ArchitectLinks>();
    QDjango::registerModel<ArchitectTypeAlias>();
    QDjango::registerModel<Comment>();
    QDjango::registerModel<DocElement>();
    QDjango::registerModel<GlossaryElement>();
    QDjango::registerModel<ImagesElement>();
    QDjango::registerModel<TermsElement>();

    QDjango::createTables();
}

/*
 * Создание виджетов модуля
 */
void ProjectManager::createWidgets() {
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
}

QString ProjectManager::information()
{
    QString msg = "project_manager";
    return msg;
}



