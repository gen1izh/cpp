#ifndef PLUG
#define PLUG
#include <QAction>
#include <QString>
#include <QWidget>
#include <frameWork/plugins.h>


namespace plug {
  /*!
   * \brief Возвращает действие из списка пар (виджет,действие)
   * \param[in] pluginName - имя плагина
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает действие
   */
  QAction *getManagerAction_FromWAPair(QString pluginName, QString waName);

  /*!
   * \brief Возвращает виджет из списка пар (виджет,действие)
   * \param[in] pluginName - имя плагина
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает виджет
   */
  QWidget *getManagerWidget_FromWAPair(QString pluginName, QString waName);

  /*!
   * \brief Возвращает дествие из списка действий плагина
   * \param[in] pluginName - имя плагина
   * \param[in] actionName - имя действия
   * \return Возвращает действие
   */
  QAction *getManagerAction_FromActionsList(QString pluginName, QString actionName);

  /*!
   * \brief Возвращает действие из списка пар (виджет,действие)
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает действие
   */
  QAction *getLoggerAction_FromWAPair(QString waName);

  /*!
   * \brief Возвращает виджет из списка пар (виджет,действие)
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает виджет
   */
  QWidget *getLoggerWidget_FromWAPair(QString waName);

  /*!
   * \brief Возвращает дествие из списка действий плагина
   * \param[in] actionName - имя действия
   * \return Возвращает действие
   */
  QAction *getLoggerAction_FromActionsList(QString waName);
}
#endif // PLUG

