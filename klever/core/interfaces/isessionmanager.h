#ifndef ISESSIONPLUGIN_H
#define ISESSIONPLUGIN_H

#include "managerinterface.h"

/*!
 * \brief Интерфейс плагина сессий
 */
class ISessionPlugin : public PluginInterface {
  public:
    ISessionPlugin(){}
    virtual ~ISessionPlugin(){}

    /*!
     * \brief Запуск кода сессий
     * \return возвращает результат true - все успешно
     */
    virtual bool execute() = 0;

};


#define ISessionPlugin_iid "ru.home.klever.ISessionPlugin"
// Use the Q_DECLARE_INTERFACE() macro to tell Qt's meta-object system about the interface.
Q_DECLARE_INTERFACE(ISessionPlugin, ISessionPlugin_iid)

#endif // ISESSIONPLUGIN_H

