#ifndef IPLUGININTERFACE_H
#define IPLUGININTERFACE_H

#include <QtPlugin>

class ModuleInterface;

/*!
 *  \brief Интерфейс создания модуля.
 */
class IPluginInterface
{
  public:
    virtual ~IPluginInterface();
    /*!
     * \brief Функция создания объекта модуля по идентификатору
     * \param[in] id - идентификатор
     * \return
     */
    virtual ModuleInterface* createModule(int id) = 0;
};

#define IPluginInterface_iid "ru.irz.cve_software.IPluginInterface"

Q_DECLARE_INTERFACE(IPluginInterface, IPluginInterface_iid)

#endif // IPLUGININTERFACE_H
