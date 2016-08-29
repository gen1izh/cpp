#include "testsequencetestsviewer.h"
#include "ui_testsequencetestsviewer.h"

using namespace Library::LoggerApi;

TestsequenceTestsViewer::TestsequenceTestsViewer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TestsequenceTestsViewer)
{
  ui->setupUi(this);

  setObjectName("Просмотрщик тестовых последовательностей");

  //Установка свойства открытия контекстного меню при щелчке на listview и treeview
  ui->testsList->setContextMenuPolicy(Qt::CustomContextMenu);
  ui->scriptsTree->setContextMenuPolicy(Qt::CustomContextMenu);

  initializeScriptsTree();
  createActions();
  createConnectors();

  // Обновить список тестовых последовательностей
  // При первой инициализации виджета, должна произойти инициализация
  // контейнера для скриптов(treeview) и списка(listview) для тестовых последовательностей
  emit updateTestsList();

  AppSetupApi appsetup;

  // хотелка Стерхова
  QString testsequenceNavigationEdit = appsetup.getApplicationParam(QString("Testsequence"),
                                                                QString("/testsequenceNavigationEdit"));

  QString scriptNavigationEdit = appsetup.getApplicationParam(QString("Testsequence"),
                                                                QString("/scriptNavigationEdit"));

  ui->tabWidget->setTabText(0, testsequenceNavigationEdit);
  ui->tabWidget->setTabText(1, scriptNavigationEdit);

}


TestsequenceTestsViewer::~TestsequenceTestsViewer()
{
  delete ui;
}

/*
 * Открытие теста
 */
void TestsequenceTestsViewer::openTest()
{
  _testExternalName = ui->testsList->currentItem()->text();

  if (_testExternalName.isEmpty()) {
    messageLibrary msg;
    msg.createAboutMessage(tr("Информация"), tr("Не могу открыть тестовую последовательность, возможно она не выбрана.\n"\
                                                "Выделите тестовую последовательность, которую собираетесь открыть и \n"\
                                                "дважды щелкните по ней левой кнопкой мыши."));
    return;
  }

  emit openTestsequenceForExecutingSignal(_testExternalName);
}

/*
 * Создание теста
 */
void TestsequenceTestsViewer::createTest()
{
  emit openTestsequenceForEditingSignal(QString("CREATE_TEST"));
}

/*
 * Функция операций, которые выполняются после завершения тестовой последователльности
 */
void TestsequenceTestsViewer::finishedTestsequence()
{
  ui->testsList->setEnabled(true);
  ui->scriptsTree->setEnabled(true);
}

/*
 * Функция операций, которые выполняются после запуска тестовой последователльности
 */
void TestsequenceTestsViewer::startedTestsequence()
{
  ui->testsList->setEnabled(false);
  ui->scriptsTree->setEnabled(false);
}

/*
 * Создание действий
 */
void TestsequenceTestsViewer::createActions() {

  // Создание тестовой последовательности
  _createTestsequenceAction = new QAction(QIcon(":/testsequence/img/newtestscript.png"),
                                                  tr("&Создать"),
                                                  this );

  // Открытие тестовой последовательности
  _openTestsequenceAction = new QAction(QIcon(":/testsequence/img/opentestscript.png"),
                                                tr("&Открыть"),
                                                this );

  // Удаление тестовой последовательности
  _deleteTestsequenceAction = new QAction(QIcon(":/testsequence/img/deltest.png"),
                    tr("&Удаление"),
                    this );

  // Переименование тестовой последовательности
  _renameTestsequenceAction = new QAction(QIcon(":/testsequence/img/renametest.png"),
                    tr("&Переименовать"),
                    this );

  // Создание дампа тестовых последовательностей
  _dumpCreatorTestsequenceAction = new QAction(QIcon(":/testsequence/img/dumptest.png"),
                    tr("&Создать дамп БД"),
                    this );

  // Развертывание тестовых последовательностей
  _uploadTestsequenceAction = new QAction(QIcon(":/testsequence/img/uploadtest.png"),
                    tr("&Развернуть тестовые последовательности"),
                    this );

  // Редактирование тестовой последовательности
  _editTestsequenceAction = new QAction(QIcon(":/testsequence/img/edittest.png"),
                        tr("&Редактировать"),
                        this );

  // Отладка скрипта
  _debugScriptAction = new QAction(QIcon(":/testsequence/img/debugscript.png"),
                                   tr("&Отладка"),
                                   this );

  // Создание скрипта
  _createScriptAction = new QAction(QIcon(":/testsequence/img/newtestscript.png"),
                                                  tr("&Создать"),
                                                  this );

  // Открытие скрипта
  _openScriptAction = new QAction(QIcon(":/testsequence/img/opentestscript.png"),
                                                tr("&Открыть"),
                                                this );

  // Удаление скрипта
  _deleteScriptAction = new QAction(QIcon(":/testsequence/img/deltest.png"),
                                                tr("&Удалить"),
                                                this );

  // Переименование скрипта
  _renameScriptAction = new QAction(QIcon(":/testsequence/img/renametest.png"),
                                                tr("&Переименовать"),
                                                this );

}

/*
 * Создание коннекторов
 */
void TestsequenceTestsViewer::createConnectors() {

  // Коннектор для соединения сигнала обновления списка тестов
  // и слота  заполнения списка тестов
  connect(this, SIGNAL(updateTestsList()), this, SLOT(fillTestsList()));

  connect(ui->scriptsTree,SIGNAL(doubleClicked(QModelIndex)),this,
          SLOT(scriptsTreeView_doubleClicked(QModelIndex)));

  connect(ui->scriptsTree,SIGNAL(clicked(QModelIndex)),this,
          SLOT(scriptsTreeView_clicked(QModelIndex)));

  connect(_openScriptAction,SIGNAL(triggered()),this,
          SLOT(openScriptAction()));

  // Контекстное меню для скриптов
  connect(ui->scriptsTree,SIGNAL(customContextMenuRequested(QPoint)),
          this,SLOT(onContextMenuRequestForScript(QPoint)));

  // Контекстное меню для тестовой последовательности
  connect(ui->testsList, SIGNAL(customContextMenuRequested(QPoint)),
          this, SLOT(onContextMenuRequestForTest(QPoint)));

  // Действия с тестами
  connect(_createTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(createTest()));

  connect(_openTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(openTest()));

  connect(_deleteTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(deleteTestsequence()));

  connect(_renameTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(renameTestsequence()));

  connect(_dumpCreatorTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(dumpTestsequenceDatabase()));

  connect(_uploadTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(uploadTestsequenceDatabase()));

  connect(_editTestsequenceAction, SIGNAL(triggered()),
           this, SLOT(editTestsequenceDatabase()));

  // Действия со скриптами

  connect(_createScriptAction, SIGNAL(triggered()),
           this, SLOT(createScript()));

  connect(_openScriptAction, SIGNAL(triggered()),
           this, SLOT(openScriptAction()));

  connect(_deleteScriptAction, SIGNAL(triggered()),
           this, SLOT(deleteScriptAction()));

  connect(_renameScriptAction, SIGNAL(triggered()),
           this, SLOT(renameScriptAction()));

  connect(_debugScriptAction, SIGNAL(triggered()),
           this, SLOT(debugScript()));

  // Соединение события двойного щелчка по списку тестовых последовательностей
  // и обработчика открытия файла тестовой последовательности
  connect(ui->testsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
          this, SLOT(testsequencesView_doubleClicked(QListWidgetItem*)));

  // Коннектор позволяет соединить выбор теста и записать его в внутреннюю переменную
  connect(ui->testsList, SIGNAL(itemClicked(QListWidgetItem*)),
          this, SLOT(testsequencesView_clicked(QListWidgetItem*)));

}


/*
 * Возвращает путь до каталога со скриптами
 */
QString TestsequenceTestsViewer::scriptsPath() {
  SysLibrary::UtilsLibrary utils;

  // Если каталог не существовал, то создаем его...
  if (!utils.checkFolder(QString("%1/%2").arg(QDir::currentPath()).arg("files"))) {
    if (!utils.checkFolder(QString("%1/%2").arg(QDir::currentPath()).arg("files/scripts/"))) {
      return QDir::currentPath();
    }
  }
  return QString("%1/%2").arg(QDir::currentPath()).arg("files/scripts/");
}

/*
 * Инициализация дерева скриптов
 */
void TestsequenceTestsViewer::initializeScriptsTree() {
  // Инициализация моделей файловой системы для отображения скриптов
  _dirmod = new FileSystemScriptsTreeModel();
  // Установить корневой путь
  _dirmod->setRootPath(scriptsPath());
  // Настройка фильтров файлов
  _dirmod->setFilter(QDir::Files | QDir::AllDirs | QDir::NoDotAndDotDot);
  QStringList filtrList;
  filtrList << "*.scr" << "*.tst";
  // Настройка модели дерева скриптов
  _dirmod->setNameFilters(filtrList);
  _dirmod->setReadOnly(false);
  _dirmod->setNameFilterDisables(false);
  // Установка модели на дерево скриптов
  ui->scriptsTree->setModel(_dirmod);
  ui->scriptsTree->setRootIndex(_dirmod->index(scriptsPath()));
}

/*
 * Открытие контекстного меню для дерева скриптов
 */
void TestsequenceTestsViewer::onContextMenuRequestForScript(QPoint paint) {
  QMenu menu;
  QList<QAction*> lst;

  lst << _createScriptAction
      << _openScriptAction
      << _deleteScriptAction
      << _renameScriptAction
      << _debugScriptAction;
  menu.exec(lst,ui->scriptsTree->mapToGlobal(paint));
}

/*
 * Отладка скрипта
 */
void TestsequenceTestsViewer::debugScript()
{
  QScriptEngineDebugger scriptDebugger;
  scriptDebugger.attachTo(Cve::instance().scriptEngine());
  scriptDebugger.action(QScriptEngineDebugger::InterruptAction)->trigger();
  QFile f(_scriptPath);

  if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),
                          QString("Такого файла не существует! _scriptPath: %1").arg(_scriptPath));
    return;
  }
  QString txt = f.readAll();
  QScriptValue result = Cve::instance().scriptEngine()->evaluate( txt,
                               QFileInfo(_scriptPath).absoluteFilePath() );
  messageLibrary msg;
  msg.createInfoMessage(tr("Предупреждение"),QString("Результат: %1").arg(result.toString()));
}


/*
 * Обработчик двойного нажатия на treeView
 */
void TestsequenceTestsViewer::scriptsTreeView_doubleClicked(const QModelIndex &index) {

  _scriptPath = _dirmod->fileInfo(index).absoluteFilePath();

  QFile f(_scriptPath);

  if (!f.exists()) {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),tr("Такого файла не существует!"));
    return;
  }

  openEditor();

}

/*
 * Открытие редактора
 */
void TestsequenceTestsViewer::openEditor() {
  QFuture<void> future;

  future = QtConcurrent::run(this,
                             &TestsequenceTestsViewer::startEditor,
                             _scriptPath);
}

/*
 * Создание скрипта
 */
void TestsequenceTestsViewer::createScript()
{
  _scriptPath = _dirmod->fileInfo(_scriptIndex).absolutePath();

  _scriptPath = _scriptPath + "/test.scr";

  QFile f(_scriptPath);

  if (!f.exists()) {

    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) {
      messageLibrary msg;
      msg.createWarnMessage(tr("Предупреждение"),
                            QString("Такого файла не существует! _scriptPath: %1").arg(_scriptPath));
      return;
    }
    QTextStream out(&f);

    QString txt="";

    txt += "//***********************************************\n";
    txt += "//                 Information\n";
    txt += "// Автор - Иванов И.И.\n";
    txt += "// Дата  - 10.10.2015\n";
    txt += "// Описание  - скрипт выполняет проверку питания.\n";
    txt += "//***********************************************/\n";
    txt += "\n";
    txt += "// Основная функция скрипта\n";
    txt += "function run() {\n";
    txt += "  // Пишите здесь код скрипта\n";
    txt += "}\n";
    txt += "\n";
    txt += "// Вызов основной функции  скрипта\n";
    txt += "run();\n";
    txt += "\n";
    txt += "\n";
    txt += "//***********************************************\n";
    txt += "//               Лист изменений\n";
    txt += "// 1. Иванов И.И. 12.12.2012  исправил порядок\n";
    txt += "//     вызова функций настройки МКО\n";
    txt += "//\n";
    txt += "//***********************************************/\n";

    out << txt << "\n";
  }
  else {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),
                          QString("Такой файл уже существует(test.scr)!"));
  }

}

/*
 *  Открытие редактора
 */
void TestsequenceTestsViewer::openScriptAction()
{
  openEditor();
}

/*
 *  Удаление скрипта
 */
void TestsequenceTestsViewer::deleteScriptAction()
{
  _scriptPath = _dirmod->fileInfo(_scriptIndex).absoluteFilePath();

  QFile f(_scriptPath);

  if (!f.remove()) {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),
                          QString("Такого файла не существует! _scriptPath: %1").arg(_scriptPath));
    return;
  }
}

/*
 * Переименование скрипта
 */
void TestsequenceTestsViewer::renameScriptAction()
{

}


/*
 * Открытие редактора скрипта
 */
void TestsequenceTestsViewer::startEditor(QString scriptPath) {
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
 * Обработчик двойного нажатия на treeView
 */
void TestsequenceTestsViewer::scriptsTreeView_clicked(const QModelIndex &index) {
  _scriptPath  = _dirmod->fileInfo(index).absoluteFilePath();
  _scriptIndex = index;
}

/*
 * Выделение элемента списка тестов(тестовой последовательности)
 */
void TestsequenceTestsViewer::testsequencesView_clicked(QListWidgetItem *item) {
  _testExternalName = item->text();
}

/*
 * Открытие теста на исполнение
 */
void TestsequenceTestsViewer::testsequencesView_doubleClicked(QListWidgetItem *item) {

  _testExternalName = item->text();

  if (_testExternalName.isEmpty()) {
    messageLibrary msg;
    msg.createAboutMessage(tr("Информация"),tr("Не могу открыть тестовую последовательность, возможно она не выбрана.\n"\
                                               "Выделите тестовую последовательность, которую собираетесь открыть и \n"\
                                               "дважды щелкните по ней левой кнопкой мыши."));
    return;
  }

  emit openTestsequenceForExecutingSignal(_testExternalName);
}



/*
 * Отобразить тестовые последовательности
 */
void TestsequenceTestsViewer::fillTestsList() {
//  QSqlQuery *q = NULL;

  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_gui", "testcases", "testsequencelist")) {
    logWarning(this,QString("Не удалось отобразить все тестовые последовательности!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["testsequencelist"]->record();
    int nameCol = rec.indexOf("Testcase_gui_name");
    ui->testsList->clear();
    while (MySQLDataBaseApi::instance().query()["testsequencelist"]->next()) {
      QListWidgetItem *item = new QListWidgetItem();
      QFont fnt;
      item->setText(MySQLDataBaseApi::instance().query()["testsequencelist"]->value(nameCol).toString());
      item->setIcon(QIcon(":/testsequence/img/testsequencetree.ico"));
      fnt.setBold(true);
      item->setFont(fnt);
      ui->testsList->addItem(item);
      ui->testsList->setCurrentItem(item);
    }
  }

}

/*
 * Открытие контекстного меню для управления тестовой последовательностями
 */
void TestsequenceTestsViewer::onContextMenuRequestForTest(QPoint point) {
  QMenu menu;
  QList<QAction*> lst;

  QAction *separatorAct = new QAction(this);
  separatorAct->setSeparator(true);

  // Если список не пуст
  if (ui->testsList->count()!=0) {
    _testExternalName = ui->testsList->currentItem()->text();

    lst  << _createTestsequenceAction
         << _openTestsequenceAction
         << _editTestsequenceAction
         << _deleteTestsequenceAction
         << _renameTestsequenceAction
         << separatorAct
         << _dumpCreatorTestsequenceAction;
  }
  else {
    lst << _uploadTestsequenceAction;
  }

  menu.exec(lst,ui->testsList->mapToGlobal(point));
}


/*
 * Переименовать тестовую последовательность
 */
void TestsequenceTestsViewer::renameTestsequence() {

  RenameTestDialog _renameTestDialog;

  // Установка флагов для диалогового окна
  _renameTestDialog.setWindowFlags( Qt::Window
                                  | Qt::MSWindowsFixedSizeDialogHint
                                  | Qt::WindowCloseButtonHint);

  // Обработка нажатия на кнопку ok
  if (_renameTestDialog.exec() == QDialog::Accepted) {

    if (!MySQLDataBaseApi::instance().sqlquery("cve_testsequence", "testsequence_gui",
                       QString("update testcases set Testcase_gui_name = '%1' "
                       "where Testcase_gui_name = '%2'").arg(_renameTestDialog.getText())
                       .arg(_testExternalName),"testsequencelist")) {
      logWarning(this, QString("Не удалось переименовать тестовую последовательность!"));
    }

  }

  emit updateTestsList();
}

/*
 * Удаление тестовой последовательности
 */
void TestsequenceTestsViewer::deleteTestsequence() {
  bool ok;
//  QSqlQuery *q = NULL;

  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence",
                                                           "testsequence_gui",
                                                           "testcases", "testsequencelist")) {
    logWarning(this,QString("Не удалось удалить тестовую последовательность!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["testsequencelist"]->record();
    int nameGuiCol = rec.indexOf("Testcase_gui_name");
    int nameTableCol = rec.indexOf("Testcase_table_name");
    int id = rec.indexOf("id");
    while (MySQLDataBaseApi::instance().query()["testsequencelist"]->next()) {
      if (MySQLDataBaseApi::instance().query()["testsequencelist"]->value(nameGuiCol).toString() == _testExternalName) {
        _testInternalName = MySQLDataBaseApi::instance().query()["testsequencelist"]->value(nameTableCol).toString();
        MySQLDataBaseApi::instance().deleteRecordById("cve_testsequence", "testsequence_gui",
                                                      "testcases",
                                                      MySQLDataBaseApi::instance().query()["testsequencelist"]->value(id).toInt(&ok),
                                                      "testsequencelist");
        break;
      }
    }
  }

//  testcaseNodesParamClean();

  QMessageBox msgBox;
  msgBox.setWindowTitle("Продолжить удаление...");
  msgBox.setText("Удалить структуру тестовой последовательности и отчеты? "
                 "Если да, то отчеты будут удалены. "
                 "Если нет, то удалится лишь структура тестовой последовательности.");

  msgBox.setStandardButtons(QMessageBox::Yes |
                            QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::Yes);

  int ret = msgBox.exec();

  switch (ret) {
    case QMessageBox::Yes:
      deleteTestcaseStructure();
      deleteTestcaseParams();
      deleteReport();
      break;
    case QMessageBox::No:
      break;
    default:
      // should never be reached
      break;
  }

  emit updateTestsList();
}




/*
 * Очистка таблицы с параметрами узлов тестовой последовательности
 */
void TestsequenceTestsViewer::testcaseNodesParamClean() {
  bool ok;

  if (!MySQLDataBaseApi::instance().selectAllDataFromTable(
        "cve_testsequence",  "testsequence_thread",
        "testcase_nodes_param",
        "testsequencelist")) {
    logWarning(this,QString("Не удалось очистить таблицу параметров "
                            "узлов тестовой последовательности, возможно тест был "
                            "без параметров."));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["testsequencelist"]->record();
    int nameCol = rec.indexOf("Testcase_name");
    int id = rec.indexOf("id");
    while (MySQLDataBaseApi::instance().query()["testsequencelist"]->next()) {
      if (MySQLDataBaseApi::instance().query()["testsequencelist"]->value(nameCol).toString() == _testInternalName) {
        MySQLDataBaseApi::instance().deleteRecordById(
              "cve_testsequence", "testsequence_thread",
              "testcase_nodes_param",
              MySQLDataBaseApi::instance().query()["testsequencelist"]->value(id).toInt(&ok),
              "testsequencelist");
      }
    }
  }
}

/*
 * Удаление таблицы структуры тестовой последовательности
 */
void TestsequenceTestsViewer::deleteTestcaseStructure() {
  if (!MySQLDataBaseApi::instance().dropTable("cve_testsequence", "testsequence_gui",
        QString("testcase_structure_%1").arg(_testInternalName), "testsequencelist")) {
    logWarning(this,QString("Не удалось удалить структуру тестовой "
                            "последовательности!"));
  }
}

/*
 * Удаление таблицыц параметров для тест-кейсов тестовой последовательности
 */
void TestsequenceTestsViewer::deleteTestcaseParams() {
  if (!MySQLDataBaseApi::instance().dropTable(
        "cve_testsequence", "testsequence_thread",
        QString("testcase_param_%1").arg(_testInternalName), "testsequencelist")) {
    logWarning(this, QString("Не удалось удалить параметры тестовой "
                             "последовательности!"));
  }
}


/*
 * Удаление отчета исполнения тестовой последовательности
 */
void TestsequenceTestsViewer::deleteReport() {
//  QSqlQuery q("",MySQLDataBaseApi::instance().getDescriptor());

  if (!MySQLDataBaseApi::instance().showTables("cve_testsequence", "testsequence_gui", "testsequencelist")) {
    logWarning(this,QString("Не удалось удалить отчет исполнения "
                            "тестовой последовательности!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["testsequencelist"]->record();
    int tables = rec.indexOf("Tables_in_cve_testsequence");
    while (MySQLDataBaseApi::instance().query()["testsequencelist"]->next()) {
      QStringList lst = MySQLDataBaseApi::instance().query()["testsequencelist"]->value(tables).toString().split("_");
//      if (lst.size()>0) {
//        if (lst.at(0) == "report") {
//          if (lst.at(lst.size()) == _testTableName) { // просмотр суффикса
//            if (!_db->dropTable(q.value(tables).toString())) {
//              qDebug() << "Error: Can not show tables!";
//            }
//          }
//        }
//      }
    }
  }
}

/*
 * Редактирование тестовой последоватности
 */
void TestsequenceTestsViewer::editTestsequenceDatabase() {

  emit openTestsequenceForEditingSignal(_testExternalName);

  // Выдает сигнал, этот сигнал должен вызвать триггер действия,
  // закрепленного за виджетом редактора тестовой последовательности
}

/*
 * Создать дамп БД стестовых последовательностей
 */
void TestsequenceTestsViewer::dumpTestsequenceDatabase() {

  SysLibrary::UtilsLibrary pathChecker;
  messageLibrary msg;

  if (!pathChecker.checkFolder(QDir::currentPath()+"/files/testsequences")) {
    logWarning(this,QString("Не удалось создать каталог testsequences"
                            "при попытке создания дампа тестовых последовательностей!"));

    msg.createErrorMessage(tr("Тестовые последовательности не обнаружены"),
                           QString("Не удалось создать каталог testsequences"
                                   "при попытке создания дампа тестовых последовательностей! Путь до каталога:")
                           .arg(QDir::currentPath()+"/files/testsequences"));

    return;
  }

  QProcess *process = new QProcess(this);
  QString cmd = QString("mysqldump -u root -p476 "
                        "cve_testsequence > %1/cve_testsequence.sql\n")
                      .arg(QDir::currentPath()+"/files/testsequences");


  process->start("cmd.exe");
  process->write(cmd.toStdString().c_str());

  process->closeWriteChannel();
  process->waitForFinished();

  process->close();

  logInfo(this,"Дамп БД для тестовых последовательностей успешно создан");
}

/*
 * Развернуть тестовые последовательности из БД
 */
void TestsequenceTestsViewer::uploadTestsequenceDatabase() {

  QString path;
  messageLibrary msg;

  logInfo(this,"Развертывание БД начато...");

  path = QDir::currentPath()+"/files/testsequences/cve_testsequence.sql";

  QFile f(path);

  if (!f.exists()) {
    logWarning(this,QString("Не удалось открыть cve_testsequence.sql"
                            " при попытке развертывания тестовых последовательностей!"));

    logWarning(this,QString("Путь неправильный %1").arg(path));

    msg.createErrorMessage(tr("Тестовые последовательности не обнаружены"),
                           QString("Не удалось открыть cve_testsequence.sql"
                              " при попытке развертывания тестовых последовательностей!"
                              "Возможно файл отсутствует. Полный путь до файла: %1").arg(path));

    return;
  }


  QProcess *process = new QProcess(this);
  QString cmd = QString("mysql -u root -p476 cve_testsequence < %1/cve_testsequence.sql\n")
                      .arg(QDir::currentPath()+"/files/testsequences");

  process->start("cmd.exe");
  process->write(cmd.toStdString().c_str());

  process->closeWriteChannel();
  process->waitForFinished();

  process->close();

  logInfo(this,"Развертывание БД успешно завершено");

  emit updateTestsList();
}


