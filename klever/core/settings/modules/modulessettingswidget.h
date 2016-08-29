#ifndef MODULESSETTINGSWIDGET_H
#define MODULESSETTINGSWIDGET_H

/*!
 * \brief   Виджет настроек менеджера модулей.
 * \details
 * \date    2015
 */

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QToolBox>
#include <QListView>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>

#include "moduleslistmodel.h"

#include <library/setupApi/app.h>

/*!
 * \brief Класс виджета настроек менеджера модулей
 */
class ModulesSettingsWidget : public QWidget
{
  Q_OBJECT

  /*!
   * \brief Создание соединений
   */
  void createConnections();

  /*!
   * \brief Лейбл на список модулей
   */
  QLabel  *_modulesListLabel;

  /*!
   * \brief Список модулей
   */
  QListView  *_modulesList;

  /*!
   * \brief Модель списка модулей
   */
  ModulesListModel *_modulesListModel;

  /*!
   * \brief Лейбл на всплывающий список имен виджетов модулей
   */
  QLabel        *_modulesWidgetsNamesLabel;

  /*!
   * \brief Список имен виджетов модулей
   */
  QComboBox     *_modulesWidgetsNamesBox;


public:
  explicit ModulesSettingsWidget(QWidget *parent = 0);
  ~ModulesSettingsWidget(){}

  /*!
   * \brief Функция установки списка имен виджетов
   * \param[in] lst список имен виджетов
   * \details  эта функция используется в ModulesManager класса
   * так как список модулей доступен только в ней. Поэтому эта функция public.
   */
  void setWidgetsNamesItems(QStringList lst);

  public slots:

    /*!
     * \brief Изменение количества устройств на модуле
     * \param[in] index модульный индес модуля в списке модулей
     */
    void moduleCountChanged(const QModelIndex &index);

    /*!
     * \brief appendBugModuleName
     * \param st
     */
    void appendBugModuleName(QString st) {
      _modulesListModel->bugModules.append(st);
    }
};

#endif // MODULESSETTINGSWIDGET_H
