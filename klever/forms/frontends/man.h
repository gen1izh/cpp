#ifndef MAN
#define MAN
#include <QAction>
#include <QString>
#include <QWidget>
#include <frameWork/cveManager.h>


namespace man {
  /*!
   * \brief Возвращает действие из списка пар (виджет,действие)
   * \param[in] managerName - имя менеджера
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает действие
   */
  QAction *getManagerAction_FromWAPair(QString managerName, QString waName);

  /*!
   * \brief Возвращает виджет из списка пар (виджет,действие)
   * \param[in] managerName - имя менеджера
   * \param[in] waName - имя пары (виджет,действие)
   * \return Возвращает виджет
   */
  QWidget *getManagerWidget_FromWAPair(QString managerName, QString waName);

  /*!
   * \brief Возвращает дествие из списка действий менеджера
   * \param[in] managerName - имя менеджера
   * \param[in] actionName - имя действия
   * \return Возвращает действие
   */
  QAction *getManagerAction_FromActionsList(QString managerName, QString actionName);

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
   * \brief Возвращает дествие из списка действий менеджера
   * \param[in] actionName - имя действия
   * \return Возвращает действие
   */
  QAction *getLoggerAction_FromActionsList(QString waName);
}
#endif // MAN

