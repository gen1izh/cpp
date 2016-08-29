#ifndef TESTSEQUENCE_EDITOR_H
#define TESTSEQUENCE_EDITOR_H

#include <QWidget>

#include "delegate/richtextdelegate.h"
#include "delegate/richtextlineedit.h"

#include <frameWork/cve.h>

#include <managers/sessions/sessionmanager.h>

#include "testsequenceeditortreeitem.h"
#include "testsequenceeditortreemodel.h"
#include "testcaseeditordialog.h"
#include "testsequencesavedialog.h"


namespace Ui {
class TestsequenceEditor;
}

class TestsequenceEditor : public QWidget
{
  Q_OBJECT


  void createConnectors();
  void createActions();
  void createToolbar();

  /*!
   * \brief Обновить состояния кнопок
   * \param[in] state - состояние
   */
  void updateControls(int state);

  /*!
   * Состояния тестовой последовательности
   * \details состояния кнопок управления согласно тому состоянию в котором находится
   * тестовая последовательность
   */
  enum {
    TEST_LOADED,
    TEST_CREATED,
    TEST_CHANGED,
    TEST_SAVED
  };

  /*!
   * \brief Делегат для первой колонки тестовой последовательности
   * Чтобы можно было редактировать название тест-кейса привычным способом
   */
  RichTextDelegate *_rtDelegate;

  /*!
   * \brief Создание новой тестовой последовательности
   */
  QAction *_fileNewAction;

  /*!
   * \brief Создание новой тестовой последовательности
   */
  QAction *_fileOpenAction;

  /*!
   * \brief Сохранение тестовой последовательности
   */
  QAction *_fileSaveAction;

  /*!
   * \brief Добавление тест-кейса в тестовую последовательность
   */
  QAction *_editAddAction;

  /*!
   * \brief Редактирование тест-кейса в тестовой последовательности
   */
  QAction *_editAction;

  /*!
   * \brief Удаление тест-кейса из тестовой последовательности
   */
  QAction *_editDeleteAction;

  /*!
   * \brief Вырезать тест-кейс из тестовой последовательности
   */
  QAction *_editCutAction;

  /*!
   * \brief Вставить тест-кейс в тестовую последовательность
   */
  QAction *_editPasteAction;

  /*!
   * \brief Поднять вверх тест-кейс по тестовой последовательности
   */
  QAction *_editMoveUpAction;

  /*!
   * \brief Опустить вниз тест-кейс по тестовой последовательности
   */
  QAction *_editMoveDownAction;

  /*!
   * \brief Продвинуть тест-кейс по тестовой последовательности
   */
  QAction *_editPromoteAction;

  /*!
   * \brief Понизить тест-кейс по тестовой последовательности
   */
  QAction *_editDemoteAction;

  /*!
   * \brief Развернуть тестовую последовательность
   */
  QAction *_expandAllAction;

  /*!
   * \brief Свернуть тестовую последовательность
   */
  QAction *_collapseAllAction;

  /*!
   * \brief Признак того что модель поменялась
   */
  bool  _isModelWasModify;

  /*!
   * \brief Проверка наличия БД и таблиц
   */
  void checkDatabaseAndTables();

  /*!
   * \brief Модель дерева тестовых последовательностей
   */
  TestSequencesEditorTreeModel   *_model;

  /*!
   * \brief Диалоговое окно редактирование тест-кейса
   */
  TestcaseEditorDialog           *_testcaseEditorDialog;

  /*!
   * \brief Диалоговое окно сохранения тестовой последовательности
   */
  TestsequenceSaveDialog         *_testsequenceSaveDialog;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внешнее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString _testExternalName;

  /*!
   * \brief Название тестовой последовательности открытой для редактирования(внутреннее представление)
   * Если создаем тест, то первоначально это поле будет пустым
   */
  QString _testInternalName;

  /*!
   * \brief Текущий модельный индекс
   */
  QModelIndex _currentModelIndex;

  public:
    explicit TestsequenceEditor(QWidget *parent = 0);
    ~TestsequenceEditor();

    /*!
     * \brief Установка модели
     * \param[in] model - модель тестовой последовательности
     */
    void setModel(TestSequencesEditorTreeModel *model) { _model = model; }

    /*!
     * \brief Возвращает модель тестовой последовательности
     * \return
     */
    TestSequencesEditorTreeModel* model() { return _model; }

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *fileNewAction()    { return _fileNewAction; }

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *fileOpenAction()   { return _fileOpenAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *fileSaveAction()   { return _fileSaveAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editAddAction()    { return _editAddAction; }

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editAction()       { return _editAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editDeleteAction() { return _editDeleteAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editCutAction()    { return _editCutAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editPasteAction()  { return _editPasteAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editMoveUpAction() { return _editMoveUpAction;}

    /*!
     * \brief Возвращает действие
     * \return
     */
    QAction *editMoveDownAction() { return _editMoveDownAction;}

    /*!
     * \brief Возвращает действие продвижения тест-кейса по дереву
     * \return
     */
    QAction *editPromoteAction()  { return _editPromoteAction;}

    /*!
     * \brief Возвращает действие понижения тест-кейса по дереву
     * \return
     */
    QAction *editDemoteAction()   { return _editDemoteAction;}

  private:
    Ui::TestsequenceEditor *ui;

  public slots:

    /*!
     * \brief Установка текущего модельного индекса
     * \param[in] index - модельный индекс
     */
    void setCurrentIndex(const QModelIndex &index) {
      // TODO: При нажатии на пустое пространство тривью хочу чтобы
      // _currentModelIndex = _currentModelIndex = QModelIndex();
      // но такой вариант не пашет, не знаю как это сделать
      if (index.isValid()) {
        _currentModelIndex = index;
      } else {
        _currentModelIndex = QModelIndex();
      }
    }

    /*!
     * \brief Открытие тестовой последовательности
     * \param[in] name - имя тестовой последовательности для редактирования
     */
    void openTestsequenceForEditing(QString name);

    /*!
     * Обработчик загрузки дерева проверок
     */
    void onLoaded();

    /*!
     * \brief Обработчик изменения дерева проверок
     */
    void onChanged();

//    /*!
//     * \brief Установить текущий индекс
//     * \param index
//     */
//    void setCurrentIndex(const QModelIndex &index);

//    /*!
//     * \brief Сворачивание и разворачивание всей тестовой последовательности
//     */
//    void refreshView();

//    /*!
//     * \brief Установка среднего времени на исполнение скрипта
//     */
//    void setAvarageTime();

//    /*!
//     * \brief Изменение признака изменения окна
//     * \param dirty
//     */
//    void setDirty( bool dirty = true ) {
//      setWindowModified( dirty );
//    }

    /*!
     * \brief Установка признака изменения модели isModelWasModify
     * \param[in] flag - значение
     */
    void setIsModelWasModify(bool flag) { _isModelWasModify = flag; }

    /*!
     * \brief Открытие скрипта при нажатии на тест-кейс тестовой
     * последовательности
     * \param[in] index - модельный индекс
     * \details Испускает сигнал, этот сигнал в creator закреплен
     * за редактором скриптов (за слотом открытия файла скрипта)
     */
    void openScript(QModelIndex index);

    /*!
     * \brief Открытие редактора скрипта
     * \param[in] scriptPath - путь до скрипта
     */
    void startEditor(QString scriptPath);


    /*!
     * \brief Открытие тестовой последовательности
     */
    void fileOpen();

    /*!
     * \brief Создание тестовой последовательности
     */
    void fileNew();

    /*!
     * \brief Сохранение тестовой последовательности
     */
    void editSave();

    /*!
     * \brief Редактировать тест-кейс
     */
    void edit();

    /*!
     * \brief Добавить тест-кейс в тестовую последовательность
     */
    void editAdd();

    /*!
     * \brief Удалить тест-кейс из тестовой последовательности
     */
    void editDelete();

    /*!
     * \brief Вырезать тест-кейс из тестовой последовательности
     */
    void editCut();

    /*!
     * \brief Вставить  тест-кейс в тестовую последовательность
     */
    void editPaste();

    /*!
     * \brief Перенести наверх тест-кейс в тестовой последовательности
     */
    void editMoveUp();

    /*!
     * \brief Перенести вниз тест-кейс в тестовой последовательности
     */
    void editMoveDown();

    /*!
     * \brief Продвижение тест-кейса вперед тестовой последовательности
     */
    void editPromote();

    /*!
     * \brief Понижение тест-кейса в тестовой последовательности
     */
    void editDemote();

    /*!
     * \brief Верифицировать представление дерева проверок
     */
    bool editVerify();

    /*!
     * \brief Развернуть тестовую последовательность
     */
    void collapse();

    /*!
     * \brief Свернуть тестовую последовательность
     */
    void expand();

  signals:

    /*!
     * \brief Сигнал обновления списка тестов
     */
    void updateTestsList();
};



#endif // TESTSEQUENCE_EDITOR_H
