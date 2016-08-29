#include "testsequenceeditor.h"
#include "ui_testsequenceeditor.h"

TestsequenceEditor::TestsequenceEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TestsequenceEditor)
{
  ui->setupUi(this);

  setObjectName("Редактор тестовой последовательности");

  // Сбрасываем флаг изменения модели
  _isModelWasModify = false;

  // Создания представления тестовой последовательности
  setModel(new TestSequencesEditorTreeModel(this));
  _model->setTestsequenceExternalName(&_testExternalName);
  _model->setTestsequenceInternalName(&_testInternalName);

  _testcaseEditorDialog = new TestcaseEditorDialog(this);
  _testcaseEditorDialog->setModel(_model);
  _testcaseEditorDialog->setTestsequenceExternalName(&_testExternalName);
  _testcaseEditorDialog->setTestsequenceInternalName(&_testInternalName);

  _testsequenceSaveDialog = new TestsequenceSaveDialog(this);
  _testsequenceSaveDialog->setModel(_model);
  _testsequenceSaveDialog->setTestsequenceExternalName(&_testExternalName);
  _testsequenceSaveDialog->setTestsequenceInternalName(&_testInternalName);

  _rtDelegate = new RichTextDelegate();

  ui->testView->setItemDelegateForColumn(0, _rtDelegate);
  ui->testView->setModel(_model);
  ui->testView->setContextMenuPolicy(Qt::CustomContextMenu);

  ui->testView->setColumnWidth(0, 400); // Установили ширину первой колонки (Название)
  ui->testView->setColumnWidth(1, 400); // Установили ширину второй колонки (Путь до скрипта)

  createActions();
  createConnectors();
  createToolbar();

  setWindowIcon(QIcon(":/testsequence/img/testsequence.png"));

  checkDatabaseAndTables();
}

TestsequenceEditor::~TestsequenceEditor()
{
  delete ui;
}

/*
 * Создание коннекторов
 */
void TestsequenceEditor::createConnectors()
{

  // Сигнал открытия скрипта при двойном щелчке на тест в дереве
  // тестовой последовательности
  connect(ui->testView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openScript(QModelIndex)));

  // Сигнал выборки тест-кейса
  connect(ui->testView, SIGNAL(pressed(QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));

  connect(_testsequenceSaveDialog, SIGNAL(updateTestsList()), this, SIGNAL(updateTestsList()));

  // Сигнал изменения модели
  connect(_model, SIGNAL(change()), this, SLOT(onChanged()));

  // Сигнал загрузки модели
  connect(_model, SIGNAL(loaded()), this, SLOT(onLoaded()));

  // Редактирование тест-кейса
  connect(_editAction, SIGNAL(triggered()), this, SLOT(edit()));

  // Работа с тестовой последовательностью
  //----------------------------------------------------------------------------

  // Создание нового дерева тестовой последовательности
  connect(_fileNewAction, SIGNAL(triggered()), this, SLOT(fileNew()));

  // Открытие нового дерева тестовой последовательности
  connect(_fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpen()));

  // Сохранения дерева тестовой последовательности
  connect(_fileSaveAction, SIGNAL(triggered()), this, SLOT(editSave()));

  // Редактирование дерева тестовой последовательности
  connect(_editAddAction, SIGNAL(triggered()), this, SLOT(editAdd()));

  // Удаление дерева тестовой последовательности
  connect(_editDeleteAction, SIGNAL(triggered()), this, SLOT(editDelete()));

  // Вырезать тест из дерева тестовой последовательности
  connect(_editCutAction, SIGNAL(triggered()), this, SLOT(editCut()));

  // Вставить тест в дерево тестовой последовательности
  connect(_editPasteAction, SIGNAL(triggered()), this, SLOT(editPaste()));

  // Поднять вверх тест в дереве тестовой последовательности
  connect(_editMoveUpAction, SIGNAL(triggered()), this, SLOT(editMoveUp()));

  // Опустить вниз тест в дереве тестовой последовательности
  connect(_editMoveDownAction, SIGNAL(triggered()), this, SLOT(editMoveDown()));

  // Продвинуть вперед тест в дереве тестовой последовательности
  connect(_editPromoteAction, SIGNAL(triggered()), this, SLOT(editPromote()));

  // Продвинуть назад тест в дереве тестовой последовательности
  connect(_editDemoteAction, SIGNAL(triggered()), this, SLOT(editDemote()));

  // Свернуть тестовую последовательность
  connect(_collapseAllAction, SIGNAL(triggered()), this, SLOT(collapse()));

  // Развернуть тестовую последовательность
  connect(_expandAllAction, SIGNAL(triggered()), this, SLOT(expand()));

}

/*
 * Создание панели быстрого запуска для основных функций работы
 * с тестовой последовательностью
 */
void TestsequenceEditor::createToolbar() {

  ui->editMenu->setIconSize(QSize(50,50));

  ui->editMenu->addAction(_fileSaveAction);
  ui->editMenu->addSeparator();
  ui->editMenu->addAction(_editAction);
  ui->editMenu->addSeparator();
  ui->editMenu->addAction(_editAddAction);
  ui->editMenu->addAction(_editDeleteAction);
  ui->editMenu->addAction(_editCutAction);
  ui->editMenu->addAction(_editPasteAction);
  ui->editMenu->addSeparator();
  ui->editMenu->addAction(_editMoveUpAction);
  ui->editMenu->addAction(_editMoveDownAction);
  ui->editMenu->addAction(_editPromoteAction);
  ui->editMenu->addAction(_editDemoteAction);
  ui->editMenu->addSeparator();
  ui->editMenu->addAction(_collapseAllAction);
  ui->editMenu->addAction(_expandAllAction);
}


/*
 * Создание действий
 */
void TestsequenceEditor::createActions()
{
  // Создание тестовой последовательности скриптов
  // -------------------------------------------------
  _fileNewAction = new QAction(QIcon(":/testsequence/img/new.png"),
                               tr("&Создать..."), NULL);
  _fileNewAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_N));
  _fileNewAction->setStatusTip(tr("Создание тестовой последовательности"));
  // -------------------------------------------------

  // Открытие тестовой последовательности скриптов
  // -------------------------------------------------
  _fileOpenAction = new QAction(QIcon(":/testsequence/img/open.png"),tr("&Открыть..."),NULL);
  _fileOpenAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
  _fileOpenAction->setStatusTip(tr("Открытие тестовой последовательности"));
  // -------------------------------------------------


  // Сохранение тестовой последовательности скриптов
  // -------------------------------------------------
  _fileSaveAction = new QAction(QIcon(":/testsequence/img/save.png"),tr("&Сохранить..."),NULL);
  _fileSaveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
  _fileSaveAction->setStatusTip(tr("Cохранение тестовой последовательности"));
  // -------------------------------------------------

  // Добавление элемента в тестовую последовательность
  // -------------------------------------------------
  _editAddAction = new QAction(QIcon(":/testsequence/img/add.png"),tr("&Добавить элемент..."),NULL);
  _editAddAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_A));
  _editAddAction->setStatusTip(tr("Добавление элемента в тестовую последовательность"));
  // -------------------------------------------------

  // Удалить элемент из тестовой последовательности
  // -------------------------------------------------
  _editDeleteAction = new QAction(QIcon(":/testsequence/img/delete.png"),tr("&Удалить элемент..."), NULL);
  _editDeleteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Delete));
  _editDeleteAction->setStatusTip(tr("Удаление элемента из тестовой последовательности"));
  // -------------------------------------------------

  // Вырезание элемента в тестовой последовательности
  // -------------------------------------------------
  _editCutAction = new QAction(QIcon(":/testsequence/img/cut.png"),tr("&Вырезать элемент..."),NULL);
  _editCutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_C));
  _editCutAction->setStatusTip(tr("Вырезание элемента из тестовой последовательности"));
  // -------------------------------------------------

  // Вставка элемента в тестовую последовательность
  // -------------------------------------------------
  _editPasteAction = new QAction(QIcon(":/testsequence/img/paste.png"), tr("&Вставить элемент..."), NULL);
  _editPasteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_V));
  _editPasteAction->setStatusTip(tr(" Вставка элемента в тестовую последовательность"));
  // -------------------------------------------------

  // Переместить вверх элемент в тестовой последовательности
  // -------------------------------------------------
  _editMoveUpAction = new QAction(QIcon(":/testsequence/img/up.png"),tr("&Переместить вверх элемент..."),NULL);
  _editMoveUpAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Up));
  _editMoveUpAction->setStatusTip(tr("Переместить вверх элемент в тестовой последовательности"));
  // -------------------------------------------------

  // Переместить вниз элемент в тестовой последовательности
  // -------------------------------------------------
  _editMoveDownAction = new QAction(QIcon(":/testsequence/img/down.png"),tr("&Переместить вниз элемент..."),NULL);
  _editMoveDownAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Down));
  _editMoveDownAction->setStatusTip(tr("Переместить вниз элемент в тестовой последовательности"));
  // -------------------------------------------------

  // Продвижение элемента в тестовой последовательности
  // -------------------------------------------------
  _editPromoteAction = new QAction(QIcon(":/testsequence/img/promote.png"),tr("&Продвинуть элемент..."),NULL);
  _editPromoteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right));
  _editPromoteAction->setStatusTip(tr("Продвижение элемента в тестовой последовательности"));
  // -------------------------------------------------

  // Понижение элемента в тестовой последовательности
  // -------------------------------------------------
  _editDemoteAction = new QAction(QIcon(":/testsequence/img/demote.png"),tr("&Понизить элемент..."),NULL);
  _editDemoteAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left));
  _editDemoteAction->setStatusTip(tr("Понижение элемента в тестовой последовательности"));
  // -------------------------------------------------

  // Редактирование тестовой последовательности
  // -------------------------------------------------
  _editAction = new QAction(QIcon(":/testsequence/img/edit.png"),tr("&Редактировать проверку..."),NULL);
  _editAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
  _editAction->setStatusTip(tr("Редактирование тестовой последовательности"));
  // -------------------------------------------------

  // Развернуть тестовую последовательность
  // -------------------------------------------------
  _expandAllAction = new QAction(QIcon(":/testsequence/img/expandall.png"),tr("&Развернуть тестовую последовательность"),NULL);
  _expandAllAction->setStatusTip(tr("Развернуть тестовую последовательность"));
  // -------------------------------------------------

  // Свернуть тестовую последовательность
  // -------------------------------------------------
  _collapseAllAction = new QAction(QIcon(":/testsequence/img/collapseall.png"),tr("&Свернуть тестовую последовательность"),NULL);
  _collapseAllAction->setStatusTip(tr("Свернуть тестовую последовательность"));
  // -------------------------------------------------
}

/*
 *  Обновление кнопок управления
 */
void TestsequenceEditor::updateControls(int state) {

  _editAddAction->setEnabled(true);
  _editAction->setEnabled(true);
  _editDeleteAction->setEnabled(true);
  _editCutAction->setEnabled(true);
  _editPasteAction->setEnabled(true);
  _editMoveUpAction->setEnabled(true);
  _editMoveDownAction->setEnabled(true);
  _editPromoteAction->setEnabled(true);
  _editDemoteAction->setEnabled(true);
  _expandAllAction->setEnabled(true);
  _collapseAllAction->setEnabled(true);

  switch (state) {
    case TEST_SAVED:
    case TEST_LOADED:
      _fileSaveAction->setIcon(QIcon(":/testsequence/img/save.png"));
      _fileSaveAction->setEnabled(false);
      break;
    case TEST_CREATED:
      break;
    case TEST_CHANGED:
      _fileSaveAction->setIcon(QIcon(":/testsequence/img/nsave.png"));
      _fileSaveAction->setEnabled(true);
      break;
    default:
      break;
  }
}

/*
 * Сигнал загрузки тестовой последовательности
 */
void TestsequenceEditor::onLoaded() {
  // TODO: костыль
  // Без этой строки тествьювер будет пустым, после загрузки
  // данных в модель, ресайз - обновляет  тест вью
  // Возможно нужно использовать надо как-то
  // _model->dataChanged(QModelIndex(),QModelIndex());
  ui->testView->resizeColumnToContents(2);
  _isModelWasModify = true;

  ui->testView->setCurrentIndex(QModelIndex());
  _currentModelIndex = QModelIndex();

  updateControls(TEST_LOADED);
}

/*
 * Обработчик изменения дерева проверок
 */
void TestsequenceEditor::onChanged() {

  // TODO: костыль
  // Без этой строки тествьювер будет пустым, после загрузки
  // данных в модель, ресайз - обновляет  тест вью
  // Возможно нужно использовать надо как-то
  // _model->dataChanged(QModelIndex(),QModelIndex());
  ui->testView->resizeColumnToContents(2);
  _isModelWasModify = true;

  updateControls(TEST_CHANGED);

}

/*
 * Открытие тестовой последовательности для редактирования
 */
void TestsequenceEditor::openTestsequenceForEditing(QString name) {
  if (name == "CREATE_TEST") {
    _testExternalName = "";
    _testInternalName = "";
    _model->clearModel();
    // Признак того что тестовая последовательность загружена
    // На самом деле она не загружается, но вызвать этот
    // сигнал надо чтобы открыть окно редактора
    emit _model->loaded();
  }
  else {
    _testExternalName = name;
    // Загрузили в модель дерево теста
    _model->load();
  }
}

/*
 * Открытие скрипта по двойному щелчку на тест-кейс
 */
void TestsequenceEditor::openScript(QModelIndex index)
{
  QFuture<void> future;
  TestSequencesEditorTreeItem *item = _model->itemForIndex(index);
  QString scriptPath;
  scriptPath = QString("%1/files/scripts%2").arg(QDir::currentPath()).arg(item->path());

  QFile f(scriptPath);

  if (!f.exists()) {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),tr("Такого файла не существует!"));
    return;
  }

  future = QtConcurrent::run(this,
                             &TestsequenceEditor::startEditor,
                             scriptPath);
}

/*
 * Открытие редактора скрипта
 */
void TestsequenceEditor::startEditor(QString scriptPath) {
  AppSetupApi setting;
  setting.checkApplicationParam( QString("Testsequence"),
                                 QString("/path"),
                                 QString("") );
  QString editorPath = setting.getApplicationParam(QString("Testsequence"),
                                        QString("/path") );

  QFile file(editorPath);

   if ((!file.open(QIODevice::ReadOnly | QIODevice::Text))||(editorPath.isEmpty())
       ||(!file.exists())) {
     messageLibrary msg;
     msg.createWarnMessage(tr("Предупреждение"),tr("Такого редактора не существует, "
                                                   "либо он не установлен в настройках !"));
    return;
  }

  QProcess *process = new QProcess(NULL);
  QString cmd = QString("%1 '%2'").arg(editorPath).arg(scriptPath);
  process->start(cmd.toStdString().c_str());
  process->closeWriteChannel();
  process->waitForFinished(-1);
  process->close();
}

/*
 * Проверка существования БД и таблицы с тестовыми последовательностями и
 * таблицы с параметрами
 */
void TestsequenceEditor::checkDatabaseAndTables() {

//  // Проверка существования БД
//  if (!MySQLDataBaseApi::instance().isDatabaseExisting("cve_testsequence", "testsequence_gui", "testsequencelist")) {
//    MySQLDataBaseApi::instance().createDatabase("cve_testsequence", "testsequence_gui", "testsequencelist");
//  }

  QString query = "SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = 'cve_testsequence'";

  MySQLDataBaseApi::instance().sqlquery("mysql", "testsequence_manager_create_cve_testsequence",
                                         query, "testsequences");

  if (MySQLDataBaseApi::instance().query()["testsequences"]->size() == 0) {
    MySQLDataBaseApi::instance().createDatabase("cve_testsequence", "testsequence_manager", "testsequences");
  }

  // Проверка существования таблицы тестовых последовательностей
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence", "testsequence_gui", "reports", "testsequencelist")) {
    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui",
                                             "reports",
                "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, "
                "Testcase_table_name TEXT, Testcase_gui_name TEXT,"
                "Time_and_date TEXT)", "testsequencelist");
  }

  // Проверка существования таблицы тестовых последовательностей
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence", "testsequence_gui", "testcases", "testsequencelist")) {
    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui","testcases",
                "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, "
                "Testcase_table_name TEXT, Testcase_gui_name TEXT)", "testsequencelist");
  }

}


/*
 * Редактирование элемента тестовой последовательности
 */
void TestsequenceEditor::edit() {
  QModelIndex index = ui->testView->currentIndex();
  TestSequencesEditorTreeItem *item;
  if (!index.isValid()) {
    item = _model->getRootItem();
  }
  else {
    item = static_cast<TestSequencesEditorTreeItem*>(index.internalPointer());
  }
  if (!item) {
    return;
  }
  _testcaseEditorDialog->testSequenceEditorDialog(item);
}

/*
 * Создание новой тестовой последовательности
 */
void TestsequenceEditor::fileNew() {
  _model->clearModel();
  _model->load();
}

/*
 * Сохранение тестовой последовательности
 */
void TestsequenceEditor::editSave() {
  _testsequenceSaveDialog->saveTestsequenceStructure();
  updateControls(TEST_SAVED);
}


/*
 * Открыть файл тестовой последовательности
 */
void TestsequenceEditor::fileOpen() {
//  if (!okToClearData()) {
//    return;
//  }
//  QString filename = _model->filename();
//  QString dir( filename.isEmpty() ? QString(".")
//               : QFileInfo(filename).canonicalPath());

//  filename =
//    QFileDialog::getOpenFileName(this,
//      tr("%1 - Open").arg(QApplication::applicationName()),
//      dir,
//      tr("Тестовая последовательность (*.tst)"));

//  if ( !filename.isEmpty() ) {
//    load(filename);
//  }
}



/*
 * Добавление элемента в тестовую последовательность
 */
void TestsequenceEditor::editAdd() {
  QModelIndex index = ui->testView->currentIndex();
  if (_model->insertRow(0, index)) {
    index = _model->index(0, 0, index);
    ui->testView->setCurrentIndex(index);
    ui->testView->edit(index);
//    setDirty();
//    updateUi();
  }
}


/*
 * Удаление тесткейса
 */
void TestsequenceEditor::editDelete() {
  QModelIndex index = ui->testView->currentIndex();
  if ( !index.isValid() ) {
    return;
  }

  QString name = _model->data(index).toString();
  int rows = _model->rowCount(index);

  QString message;
  if ( rows == 0 ) {
    message = tr( "<p>Delete '%1'" ).arg( name );
  }
  else if ( rows == 1 ) {
    message = tr("<p>Delete '%1' and its child (and "
                 "grandchildren etc.)").arg( name );
  }
  else if ( rows > 1 ) {
    message = tr("<p>Delete '%1' and its %2 children (and "
                 "grandchildren etc.)").arg( name ).arg( rows );
  }

  _model->removeRow(index.row(), index.parent());

  onChanged();
}



/*
 * Вырезание тест-кейса
 */
void TestsequenceEditor::editCut() {
  QModelIndex index = ui->testView->currentIndex();
  ui->testView->setCurrentIndex(_model->cut(index));
  _editPasteAction->setEnabled(_model->hasCutItem());
  onChanged();
}

/*
 * Вставить тест-кейс
 */
void TestsequenceEditor::editPaste() {
  ui->testView->setCurrentIndex(_model->paste(ui->testView->currentIndex()));
  onChanged();
}

/*
 * Перенести навверх тест-кейс
 */
void TestsequenceEditor::editMoveUp() {
  ui->testView->setCurrentIndex(_model->moveUp(ui->testView->currentIndex()));
  onChanged();
}

/*
 * Переместить вниз тест-кейс
 */
void TestsequenceEditor::editMoveDown() {
  ui->testView->setCurrentIndex(_model->moveDown(ui->testView->currentIndex()));
  onChanged();
}

/*
 * Продвинуть уровень тест-кейса
 */
void TestsequenceEditor::editPromote() {
  QModelIndex index = ui->testView->currentIndex();
  ui->testView->setCurrentIndex(_model->promote(index));
  onChanged();
}

/*
 * Понизить уровень тест-кейса
 */
void TestsequenceEditor::editDemote() {
  QModelIndex index = ui->testView->currentIndex();
  ui->testView->setCurrentIndex(_model->demote(index));
  onChanged();
}


/*
 * Верифицировать последовательности деревьев проверок
 */
bool TestsequenceEditor::editVerify() {
  QString res;
  res  = "Перечень не валидных путей до скриптов: \n ";
  QString resVerify = _model->treewalkVerify(QModelIndex());
  res += resVerify;
  res += " Не валидные тестовые последовательности были удалены. Сохранить?";
  if ( !resVerify.isEmpty() ) {
    QMessageBox msgBox;
     msgBox.setWindowTitle( "Результат верификации..." );
     msgBox.setText( res );
     msgBox.setStandardButtons( QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel );
     msgBox.setDefaultButton( QMessageBox::Save );
     int ret = msgBox.exec();

    switch ( ret ) {
      case QMessageBox::Save:
//        _model->save( _model->filename() );
        break;
      case QMessageBox::Discard:
        break;
      case QMessageBox::Cancel:
        return false;
        break;
      default:
        // should never be reached
        break;
    }

    return false;
  }

  return true;
}

/*
 * Свернуть тестовую последовательность
 */
void TestsequenceEditor::collapse()
{
  if (_currentModelIndex == QModelIndex()) {
    ui->testView->collapseAll();
  }
  else {
    ui->testView->collapse(_currentModelIndex);
  }

  ui->testView->setCurrentIndex(QModelIndex());
  _currentModelIndex = QModelIndex();
}

/*
 * Развернуть тестовую последовательность
 */
void TestsequenceEditor::expand()
{
  if (_currentModelIndex == QModelIndex()) {
    ui->testView->expandAll();
  }
  else {
    ui->testView->expand(_currentModelIndex);
  }

  ui->testView->setCurrentIndex(QModelIndex());
  _currentModelIndex = QModelIndex();
}
