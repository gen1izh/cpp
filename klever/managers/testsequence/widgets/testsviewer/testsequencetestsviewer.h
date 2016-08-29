#ifndef TESTSEQUENCE_TESTS_VIEWER_H
#define TESTSEQUENCE_TESTS_VIEWER_H

#include <QScriptEngineDebugger>
#include <QScriptValue>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QWidget>

#include <library/loggerapi/loggerapi.h>
#include <library/message/messagelibrary.h>
#include <frameWork/cve.h>

#include "filesystemscriptstreemodel.h"
#include "renametestdialog.h"

namespace Ui {
class TestsequenceTestsViewer;
}

class TestsequenceTestsViewer : public QWidget
{
  Q_OBJECT

  void createConnectors();
  void createActions();

  /*!
   * \brief Возвращает путь до каталога со скриптамив
   * \return
   */
  QString scriptsPath();

  /*!
   * \brief Инициализация дерева скриптов
   */
  void initializeScriptsTree();

  /*!
   * \brief Открытие редактора скрипта
   * \param
   */
  void startEditor(QString scriptPath);

  /*!
   * \brief Название теста(пользователькое представление)
   */
  QString  _testExternalName;

  /*!
   * \brief Название теста(внутреннее представление)
   */
  QString  _testInternalName;

  /*!
   * \brief Путь до файла скрипта
   */
  QString _scriptPath;

  /*!
   * \brief Индекс до выбранного скрипта
   */
  QModelIndex _scriptIndex;

  QAction *_createTestsequenceAction;      // Создание тестовой последовательности
  QAction *_openTestsequenceAction;        // Открытие тестовой последовательности
  QAction *_deleteTestsequenceAction;      // Удаление тестовой последовательности
  QAction *_renameTestsequenceAction;      // Переименование тестовой последовательности
  QAction *_editTestsequenceAction;        // Открытие редактора тестовой последовательности
  QAction *_dumpCreatorTestsequenceAction; // Сделать дамп тестовой последовательности
  QAction *_uploadTestsequenceAction;      // Развернуть тестовую последовательность

  QAction *_createScriptAction;      // Создание скрипта
  QAction *_openScriptAction;        // Открытие скрипта
  QAction *_debugScriptAction;       // Начать отладку скрипта
  QAction *_deleteScriptAction;      // Удаление скрипта
  QAction *_renameScriptAction;      // Переименование скрипта

  /*!
   * \brief Модель файиловой системы для каталога со скриптами
   */
  FileSystemScriptsTreeModel  *_dirmod;

  public:
    explicit TestsequenceTestsViewer(QWidget *parent = 0);
    ~TestsequenceTestsViewer();

public slots:

    void openTest();

    void createTest();

    /*!
     * \brief Функция операций, которые выполняются после запуска тестовой последователльности
     */
    void startedTestsequence();

    /*!
     * \brief Функция операций, которые выполняются после завершения тестовой последователльности
     */
    void finishedTestsequence();

    /*!
     * \brief Обработчик двойного нажатия кнопкой мыши
     *  на список тестовых последовательностей
     * \param[in] index - модельный индекс элмента дерева
     */
    void testsequencesView_doubleClicked(QListWidgetItem *item);

    /*!
     * \brief Нажатие на тест в списке - присваивает его название переменной _testName
     * \param item
     */
    void testsequencesView_clicked(QListWidgetItem *item);

    /*!
     * \brief Обработка двойного нажатия кнопкой мыши на дерево
     * \param[in] index модельный индекс в списке скриптов
     */
    void scriptsTreeView_doubleClicked( const QModelIndex &index );

    /*!
     * \brief scriptsTreeView_clicked
     * \param index
     */
    void scriptsTreeView_clicked(const QModelIndex &index);

    /*!
     * \brief Выдает сигнал открытия редактора тестовой последовательности
     */
    void editTestsequenceDatabase();

    /*!
     * \brief Открытие контекстного меню для скрипта
     * \param point
     */
    void onContextMenuRequestForScript(QPoint paint);

    /*!
     * \brief Открытие контекстного меню для управления тестовой последовательностью
     * \param point
     */
    void onContextMenuRequestForTest(QPoint point);

    /*!
     * \brief Открытие редактора
     */
    void openEditor();

    /*!
     * \brief Создание скрипта
     */
    void createScript();

    /*!
     * \brief Открытие скрипта
     */
    void openScriptAction();

    /*!
     * \brief Удаление скрипта
     */
    void deleteScriptAction();

    /*!
     * \brief Переименование скрипта
     */
    void renameScriptAction();

  private slots:
    /*!
     * \brief Отобразить тестовые последовательности
     */
    void fillTestsList();

    /*!
     * \brief Переименовать тестовую последовательность
     */
    void renameTestsequence();

    /*!
     * \brief Удаление тестовой последовательности
     */
    void deleteTestsequence();

    /*!
     * \brief Очистка таблицы с параметрами узлов тестовой последовательности
     */
    void testcaseNodesParamClean();

    /*!
     * \brief Удаление структуры тестовой последовательности
     */
    void deleteTestcaseStructure();

    /*!
     * \brief Удаление таблицыц параметров для тест-кейсов тестовой последовательности
     */
    void deleteTestcaseParams();

    /*!
     * \brief Удаление отчетов тестовой последовательности
     */
    void deleteReport();

    /*!
     * \brief Создать дамп тестовых последовательностей
     */
    void dumpTestsequenceDatabase();

    /*!
     * \brief Развернуть тестовые последовательности из БД
     */
    void uploadTestsequenceDatabase();

    /*!
     * \brief Отладка скрипта
     */
    void debugScript();

  signals:
    /*!
     * \brief Обновление списка тестов
     */
    void updateTestsList();

    /*!
     * \brief Сигнал открытия редактора тестовой последовательности
     * \param name
     */
    void openTestsequenceForEditingSignal(QString name);

    /*!
     * \brief Сигнал открытия тестовой последовательности для исполнения
     * \param name
     */
    void openTestsequenceForExecutingSignal(QString name);

  private:
    Ui::TestsequenceTestsViewer *ui;


};



#endif // TESTSEQUENCE_TESTS_VIEWER_H
