#ifndef TEMPLATEPLUGININTERFACE_H
#define TEMPLATEPLUGININTERFACE_H

#include "templatemodule.h"

#include <interfaces/moduleinterface.h>
#include <interfaces/iplugininterface.h>

/******************************************************************************
 *               Класс для подключения модуля к ядру системы
 ******************************************************************************/

class TemplatePluginInterface: public QObject, public IPluginInterface
{
  Q_OBJECT

  Q_PLUGIN_METADATA(IID IPluginInterface_iid FILE
                    "../resources/src/templateModule.json")
  Q_INTERFACES(IPluginInterface)

  public:

    /*!
     * \brief Создание объекта источника питания.
     * \param id идентификатор модуля.
     * \return указатель на интерфейс модуля.
     */
    ModuleInterface* createModule( int id );
};

#endif // TEMPLATEPLUGININTERFACE_H
