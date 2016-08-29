#ifndef TESTSEQUENCE_MANAGER_H
#define TESTSEQUENCE_MANAGER_H

/*!
 * \brief   Менеджер тестовых последовательностей
 * \details Происходит подготовка тестовой последовательности к работе,
 *          инициализация всех основных компонентов
 * \date    2015
 */
#include <QListWidget>
#include <QDebug>

#include <interfaces/managerinterface.h>

#include <frameWork/cveManager.h>
#include <frameWork/cve.h>

#include "testsequencescriptapi.h"

#include "widgets/settings/settingswidget.h"
#include "widgets/testsviewer/testsequencetestsviewer.h"
#include "widgets/editor/testsequenceeditor.h"
#include "widgets/executor/testsequenceexecutorwidget.h"

/*!
 * \brief Класс менеджера тестовых последовательностей
 */
class CveTestSequencesManager : public QObject, public ManagerInterface {

  Q_OBJECT
  Q_PLUGIN_METADATA(IID ManagerInterface_iid FILE "testsequence.json")
  Q_INTERFACES(ManagerInterface)

  /*!
   * \brief Скриптовые функции для работы с тестами
   */
  TestsequenceScriptApi  *_scripts;

  /*!
   * \brief Виджет настроек
   */
  TestsequenceSettingsWidget *_setting;

  /*!
   * \brief Виджет просмотрщика тестов и скриптов
   */
  TestsequenceTestsViewer    *_viewer;

  /*!
   * \brief Виджет редактора тестовой последовательности
   */
  TestsequenceEditor         *_editor;

  /*!
   * \brief Указатель на виджет исполнителя тестовой последовательности
   */
  TestsequenceExecutorWidget *_executor;

  /*!
   * \brief Открытие редактора
   * Это действие необходимо для менеджера форм
   */
  QAction  *_openEditor;

  /*!
   * \brief Открытие исполнителя
   * Это действие необходимо для менеджера форм
   */
  QAction  *_openExecutor;

  /*!
   * \brief Создание коннекторов
   */
  void createConnectors();

  /*!
   * \brief Создание действий
   */
  void createActions();

  public:

    CveTestSequencesManager();

    /*!
     * \brief Создание виджетов
     */
    void createWidgets();

    /*!
     * \brief Финализация работы менеджера тестовой последовательности
     */
    void finalize() {
      // TODO:  Финализация
    }

    /*!
     * \brief Возвращает виджет настроек
     * \return
     */
    QWidget *getSettingPage();

    /*!
     * \brief Возвращает иконку для настроек
     * \return
     */
    QIcon settingIcon() {
      return QIcon(":/testsequence/img/settings/testsequence.png");
    }

  public slots:
    /*!
     * \brief Выдает триггер для открытия окна редактора
     */
    void openEditorTriggered();

    /*!
     * \brief Выдает триггер для открытия окна исполнения
     */
    void openExecutorTriggered();
};

#endif // TESTSEQUENCE_MANAGER_H
