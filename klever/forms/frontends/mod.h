#ifndef MOD_H
#define MOD_H

#include <QAction>
#include <QString>
#include <QWidget>
#include <frameWork/managers.h>
#include <settings/modules/modulesmanager.h>

namespace mod {
  /*!
   * \brief Возвращает действие из списка пар (виджет,действие)
   * \param[in] moduleName - имя модуля
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает действие
   */
  QAction *getModuleAction_FromWAPair(QString moduleName, QString waName, int id);

  /*!
   * \brief Возвращает виджет из списка пар (виджет,действие)
   * \param[in] moduleName - имя модуля
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает виджет
   */
  QWidget *getModuleWidget_FromWAPair(QString moduleName, QString waName, int id);

  /*!
   * \brief Возвращает дествие из списка действий менеджера
   * \param[in] moduleName - имя менеджера
   * \param[in] actionName - имя действия
   * \return Возвращает действие
   */
  QAction *getModuleAction_FromActionsList(QString moduleName, QString actionName, int id);

}

#endif // MOD_H
