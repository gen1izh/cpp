#include "cveTestSequences.h"

CveTestSequencesManager::CveTestSequencesManager() {

  Q_INIT_RESOURCE(testsequence_resources);

  setName(QString("/testsequence"));
  setTextName(tr("Тестовые \n последова- \n тельности"));
  checkManagerState(); // Проверка состояния менеджера

  _scripts = new TestsequenceScriptApi();

  // Регистрация этого объекта в движке исполнения
  QScriptValue value = Cve::instance().scriptEngine()->newQObject(_scripts);
  Cve::instance().addToGlobalValueList(value);
  Cve::instance().scriptEngine()->globalObject().setProperty(QString("test"), value);

  _setting = NULL;
  _viewer  = NULL;
  _editor  = NULL;

}

/*
 * Создание действий
 */
void CveTestSequencesManager::createActions() {
  _openEditor = new QAction(QIcon(""), tr("&Открыть редактор..."), NULL);
  _openExecutor = new QAction(QIcon(""), tr("&Открыть исполнитель..."), NULL);
}

/*
 * Создание коннекторов
 */
void CveTestSequencesManager::createConnectors() {

  // Загрузка тестовой последовательности на редактирование в модель
  connect(_viewer, SIGNAL(openTestsequenceForEditingSignal(QString)),
          _editor, SLOT(openTestsequenceForEditing(QString)));

  // Открытие окна редактора тестовой последовательности
  connect(_editor->model(), SIGNAL(loaded()),
          this, SLOT(openEditorTriggered()));


  // Загрузка тестовой последовательности на исполнение
  connect(_viewer, SIGNAL(openTestsequenceForExecutingSignal(QString)),
          _executor, SLOT(openTestsequenceForExecuting(QString)));

  // Открытие окна исполнения тестовой последовательности
  connect(_executor->model(), SIGNAL(loaded()),
          this, SLOT(openExecutorTriggered()));

  // Обновление всего списка тестовых последовательностей
  connect(_editor, SIGNAL(updateTestsList()),
          _viewer, SLOT(fillTestsList()));

  // функция обработки каких-то операций во вьювере тестовых последовательностей
  // и скриптов после запуска теста
  connect(_executor, SIGNAL(startedTestsequenceSignal()),
          _viewer, SLOT(startedTestsequence()));

  // функция обработки каких-то операций во вьювере тестовых последовательностей
  // и скриптов после завершения теста
  connect(_executor, SIGNAL(finishedTestsequenceSignal()),
          _viewer, SLOT(finishedTestsequence()));

  // При изменении тест-кейса - установить флаг модификации тестовой последовательности
//  connect(static_cast<TestsequenceEditor*>(widgetActionList[tr("(TestSequenceManager)TestsequenceEditor")].first),
//         SLOT(onChange()),
//         static_cast<TestsequenceTestsViewer*>(widgetActionList[tr("(TestSequenceManager)TestsequenceTestsViewer")].first),
//         SIGNAL(setIsModelWasModify(bool)));

}

/*
 * Создание виджетов менеджера
 */
void CveTestSequencesManager::createWidgets() {
  _editor   = new TestsequenceEditor(NULL);
  _viewer   = new TestsequenceTestsViewer(NULL);
  _executor = new TestsequenceExecutorWidget(NULL);

  _executor->model()->setScripts(_scripts);

  // Виджет просмотрщика тестов
  widgetActionList[tr("(TestSequenceManager)TestsequenceTestsViewer")].first = _viewer;
  widgetActionList[tr("(TestSequenceManager)TestsequenceTestsViewer")].second = NULL;

  // Виджет редактора тестовой последовательности
  widgetActionList[tr("(TestSequenceManager)TestsequenceEditor")].first = _editor;
  widgetActionList[tr("(TestSequenceManager)TestsequenceEditor")].second = _openEditor;

  // Виджет исполнителя тестовой последовательности
  widgetActionList[tr("(TestSequenceManager)TestsequenceExecutor")].first = _executor;
  widgetActionList[tr("(TestSequenceManager)TestsequenceExecutor")].second = _openExecutor;

  actionList[tr("createAction")]  = _editor->fileNewAction();
  actionList[tr("saveAction")]    = _editor->fileSaveAction();
  actionList[tr("addAction")]     = _editor->editAddAction();
  actionList[tr("deleteAction")]  = _editor->editDeleteAction();
  actionList[tr("cutAction")]     = _editor->editCutAction();
  actionList[tr("pasteAction")]   = _editor->editPasteAction();
  actionList[tr("editAction")]    = _editor->editAction();
  actionList[tr("upAction")]      = _editor->editMoveUpAction();
  actionList[tr("downAction")]    = _editor->editMoveDownAction();
  actionList[tr("promoteAction")] = _editor->editPromoteAction();
  actionList[tr("demoteAction")]  = _editor->editDemoteAction();

  // TODO: Не реализовано
//  actionList[tr("startAction")]  = _executor->startAction();
//  actionList[tr("stopAction")]   = _executor->stopAction();
//  actionList[tr("pauseAction")]  = _executor->pauseAction();
//  actionList[tr("abortAction")]  = _executor->abortAction();
}

/*
 * Возвращает виджет настроек
 */
QWidget *CveTestSequencesManager::getSettingPage() {
  if (_setting==NULL) {
    _setting = new TestsequenceSettingsWidget(NULL);
  }
  return reinterpret_cast<QWidget *>(_setting);
}

/*
 * Сигнал для открытия редактора тестовой последовательности
 */
void CveTestSequencesManager::openEditorTriggered() {
  emit _openEditor->triggered();
}

/*
 * Сигнал для исполения редактора тестовой последовательности
 */
void CveTestSequencesManager::openExecutorTriggered() {
  emit _openExecutor->triggered();
}
