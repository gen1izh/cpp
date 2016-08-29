#include "testsequenceeditortreemodel.h"
#include <frameWork/cveManager.h>


using namespace Library::LoggerApi;

#include <QMessageBox>

// Вспомогательная переменная для проставки индексов для узлов
// дерева тестовой последовательности
static int autoincrement = 0;


/*
 * Возвращает элемент по индексу
 */
TestSequencesEditorTreeModel::TestSequencesEditorTreeModel(QObject *parent)
{

  Q_UNUSED(parent)

  _rootItem         = NULL;
  _cutItem          = NULL;

  createConnectors();

}

void TestSequencesEditorTreeModel::createConnectors()
{
  connect(this, SIGNAL(loaded()), this, SLOT(testsequenceLoaded()));
}


/**********************************************************************************************
 *                         Функции загрузки тестовой последовательности
 **********************************************************************************************/


/*
 * Загрузка дерева тестовой последовательности в модель
 */
void TestSequencesEditorTreeModel::load() {

//  _testName = name;
  clearModel();
  _rootItem = new TestSequencesEditorTreeItem();

  _process.setDialog("Загрузка тестовой последовательности...");
  _process.start();

  /* Запуск потока загрузки файла */
  QFuture<void> future;
  future = QtConcurrent::run(this,
                             &TestSequencesEditorTreeModel::loadInConcurrent,
                             _rootItem);



}

/*
 * Слот финиша загрузки тестовой последовательности
 */
void TestSequencesEditorTreeModel::testsequenceLoaded() {
  _process.finish();
}

/*
 * Загрузка тестовой последовательности
 */
void TestSequencesEditorTreeModel::loadInConcurrent(
  TestSequencesEditorTreeItem *testcase
) {
  QString tableName = getTestsequenceStructureName();
  testcase->clearParam();
  readTestsequenceStructure(testcase, tableName);

  emit loaded();
}

/*
 * Возвращает внутреннее имя тест
 */
QString TestSequencesEditorTreeModel::getTestsequenceStructureName() {

//  QSqlQuery *q = NULL;

  // Проход по таблице testcases и поиск нужной нам таблицы
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_gui", "testcases", "structurename")) {
    logWarning(this,QString("Не удалось загрузить тестовую последовательность в потоке!"));
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),tr("Не удалось загрузить тестовую последовательность в потоке!"));

  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["structurename"]->record();
    int testcaseExternalsName = rec.indexOf("Testcase_gui_name");
    int testcaseInternalName = rec.indexOf("Testcase_table_name");
    while (MySQLDataBaseApi::instance().query()["structurename"]->next()) {
      if (MySQLDataBaseApi::instance().query()["structurename"]->value(testcaseExternalsName).toString()==*_testExternalName) {
        *_testInternalName = MySQLDataBaseApi::instance().query()["structurename"]->value(testcaseInternalName).toString();
        return QString("testcase_structure_%1").arg(MySQLDataBaseApi::instance().query()["structurename"]->value(testcaseInternalName).toString());
      }
    }
  }

  return QString("");
}


/*
 * Чтение структуры тестовой последовательности
 */
void TestSequencesEditorTreeModel::readTestsequenceStructure(TestSequencesEditorTreeItem *testcase, QString name) {

//  QSqlQuery *q = NULL;

  _level.clear();
  _level.append(0);

  // Проход по таблице дерева тестовой последовательности
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_gui", name, "loadteststructure")) {
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"),tr("Не удалось подключиться к БД!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["loadteststructure"]->record();

    while (MySQLDataBaseApi::instance().query()["loadteststructure"]->next()) {
      bool ok;
      int idVar                 = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("id")).toInt(&ok);
      int ParentIdVar           = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("Parent_id")).toInt(&ok);
      QString nameNodeVar       = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("Name_node")).toString();
      QString scriptFilenameVar = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("Script_filename")).toString();
      QString descriptionVar    = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("Description")).toString();
      QString execFlagVar       = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("Exec_flag")).toString();
      QString avrtimeVar        = MySQLDataBaseApi::instance().query()["loadteststructure"]->value(rec.indexOf("Avrtime")).toString();

      int level;
      if (_level.size()>=ParentIdVar) {
        level = _level.at(ParentIdVar) + 1;
      }
      else {
        logError(this, "Выход за пределы списка при чтении структуры тестовой последовательности");
        return;
      }
      _level.append(level);

      TestSequencesEditorTreeItem *item;
      item = testcase;

      if (_level.at(idVar-1) == _level.at(idVar)) {
        item = item->parent();
      }
      else
        for (int i = 0; i <= _level.at(idVar-1) - _level.at(idVar); i++ ) {
          // TODO: Необходимо исследовать случаи возниконовения item=NULL
          if (item!=NULL) {
            item = item->parent();
          }
        }

      testcase = new TestSequencesEditorTreeItem(nameNodeVar, execFlagVar, avrtimeVar,
                                                 descriptionVar, scriptFilenameVar,
                                                 false, item );


      testcase->setId(idVar);

      addParams(testcase,idVar);

    }
  }
}

/*
 * Добавить параметры
 */
void TestSequencesEditorTreeModel::addParams(TestSequencesEditorTreeItem *item, int idnode) {

  bool ok;

//  QSqlQuery *q = NULL;

  QString paramsTable = QString("testcase_param_%1").arg(*_testInternalName);

  // Проход по таблице testcases и поиск нужной нам таблицы
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_gui", paramsTable, "loadteststructureparams")) {
    logWarning(this, QString("Не удалось добавить параметры в тест-кейс!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["loadteststructureparams"]->record();
    int id = rec.indexOf("id");
    int Name = rec.indexOf("Name");
    int Value = rec.indexOf("Value");
    while (MySQLDataBaseApi::instance().query()["loadteststructureparams"]->next()) {
      if (MySQLDataBaseApi::instance().query()["loadteststructureparams"]->value(id).toInt(&ok)==idnode) {

        QPair<QString,QString> pair;
        pair.first  = MySQLDataBaseApi::instance().query()["loadteststructureparams"]->value(Name).toString();
        pair.second = MySQLDataBaseApi::instance().query()["loadteststructureparams"]->value(Value).toString();
        item->addParam(pair);
      }
    }
  }
}


/**********************************************************************************************
 *                         Функции сохранения тестовой последовательности
 **********************************************************************************************/


/*
 * Сохранение дерева тестовой последовательности в базе данных
 */
void TestSequencesEditorTreeModel::save() {

  if (_testInternalName->isEmpty()) {
    logError(this, tr("Тестовая последовательность не выбрана!"));
    return;
  }

  // Проверка существования таблицы сессий
  if (!MySQLDataBaseApi::instance().isTableInDatabaseExisting("cve_testsequence", "testsequence_gui",
                                                              QString("testcase_structure_%1").arg(*_testInternalName),
                                                              "savestructuretest")) {

    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui",
                                              QString("testcase_structure_%1").arg(*_testInternalName),
                                                      "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, Name_node TEXT,"\
                                                      "Parent_id INT, Script_filename TEXT, Description TEXT, "\
                                                      "Exec_flag TEXT, Status TEXT,"\
                                                      "Avrtime TEXT)", "savestructuretest");

    MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui",
                                              QString("testcase_param_%1").arg(*_testInternalName),
                                                      "(id INT, Testcase_name TEXT,"
                                                      "Name TEXT, Value TEXT)", "savestructuretest");
  }
  else {

    messageLibrary msg;
    int result = msg.createWarnDialog(tr("Такая тестовая последовательность уже существует!"),
                                      tr("Вы хотите перезаписать тестовую последовательность?"));

    switch (result) {
      case QMessageBox::Yes:
      // Удалили таблицу структуры тестовой последовательсти
        MySQLDataBaseApi::instance().dropTable("cve_testsequence", "testsequence_gui",
                                               QString("testcase_structure_%1").arg(*_testInternalName), "savestructuretest");

      // Создали таблицу структуры тестовой последовательсти
        MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui",
                                                 QString("testcase_structure_%1").arg(*_testInternalName),
                                                         "(id INT NOT NULL PRIMARY KEY AUTO_INCREMENT, Name_node TEXT,"\
                                                         "Parent_id INT, Script_filename TEXT, Description TEXT, Exec_flag TEXT,"\
                                                         "Status TEXT, Avrtime TEXT)", "savestructuretest");

      // Удалили таблицу параметров
        MySQLDataBaseApi::instance().dropTable("cve_testsequence", "testsequence_gui",
                                               QString("testcase_param_%1").arg(*_testInternalName), "savestructuretest");

      // Создали таблицу параметров
        MySQLDataBaseApi::instance().createTable("cve_testsequence", "testsequence_gui",
                                                  QString("testcase_param_%1").arg(*_testInternalName),
                                                          "(id INT, Testcase_name TEXT,"
                                                          "Name TEXT, Value TEXT)", "savestructuretest");

        break;
      case QMessageBox::Cancel:
          // Cancel was clicked
        break;
      default:
          // should never be reached
        break;
    }
  }

  // Перезаписать идентификаторы узлов
  rewriteTestcaseTreeNodesIds(_rootItem);
  autoincrement = 0;

  // Записать дерево тестовых проверок в базу данных
  writeTestcaseTreeToDatabase(0, _rootItem);


}

/*
 * Проставить идентификаторы узлов
 */
void TestSequencesEditorTreeModel::rewriteTestcaseTreeNodesIds(
  TestSequencesEditorTreeItem *testcase
) {

  if (testcase!=_rootItem) {
    testcase->setId(autoincrement);
  }
  else {
    testcase->setId(0);
  }

  // Если головной элемент rootItem, то выбираем у него дочерний элемент
  // и рекурсивно проходим все дерево
  foreach (TestSequencesEditorTreeItem *child, testcase->children()) {
    autoincrement++;
    rewriteTestcaseTreeNodesIds(child);
  }
}

/*
 * Запись всех узлов дерева проверок в базу данных
 */
void TestSequencesEditorTreeModel::writeTestcaseTreeToDatabase(
  int id,
  TestSequencesEditorTreeItem *testcase
) /*const*/ {

  if (testcase!=_rootItem) {

    if (!MySQLDataBaseApi::instance().insertIntoTable(
          "cve_testsequence", "testsequence_gui",
          QString("testcase_structure_%1").arg(*_testInternalName),
          QString("(NULL,'%1',%2,'%3','%4','%5','%6','%7')")
               .arg(testcase->name())
               .arg(id)
               .arg(testcase->path())
               .arg(testcase->description())
               .arg(testcase->isExectable())
               .arg(QString(""))
               .arg(QString("")), "savestructuretestwrite") ) {
      logWarning(this, QString("Не удалось записать структуру тестовой последовательности!"));
    }

    int lid;

    if (!MySQLDataBaseApi::instance().lastId(
          "cve_testsequence", "testsequence_gui",
          QString("testcase_structure_%1").arg(*_testInternalName),
          lid, "savestructuretestwrite")) {

      logWarning(this, QString("Не удалось получить id последней записи!"));
    }

    // Запись параметров тест-кейса
    QListIterator<
            QPair<QString, QString> > i( testcase->params() );
    while (i.hasNext()) {
      const QPair<QString, QString> &param = i.next();
        if (!MySQLDataBaseApi::instance().insertIntoTable(
             "cve_testsequence", "testsequence_gui",
             QString("testcase_param_%1").arg(*_testInternalName),
             QString("(%1,'%2','%3','%4')")
                   .arg(lid)
                   .arg(*_testInternalName)
                   .arg(param.first)
                   .arg(param.second), "savestructuretestwrite" )) {
          logWarning(this, QString("Не удалось записать параметры!"));
        }
    }
  }

  // Если головной элемент rootItem, то выбираем у него дочерний элемент
  // и рекурсивно проходим все дерево
  foreach (TestSequencesEditorTreeItem *child, testcase->children()) {
    writeTestcaseTreeToDatabase(child->parent()->id(),child);
  }

}

/**********************************************************************************************
 *                              Проход по тестовой последовательности
 **********************************************************************************************/

/*
 * Верификация дерева тестовой последовательности
 */
QString TestSequencesEditorTreeModel::treewalkVerify(const QModelIndex &_index) {

  QModelIndex i;
  QString     st;

  if (_index == QModelIndex()) {
    st.clear();
  }

  for (int row = 0; row < rowCount(_index); ++row) {
    i = index(row, 0, _index);
    TestSequencesEditorTreeItem *item = itemForIndex(i);

    if (!item->path().isEmpty()) {
      QString scriptPath;
      scriptPath = QString("%1/files/scripts%2").arg(QDir::currentPath()).arg(item->path());
      QFile file(scriptPath);
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        st += QString(" - Скрипт {%1} не существует \n")
                      .arg( item->path() );
        item->setPath("");
        item->setExectableFlag( false );
      }
      file.close();
    }
    st +=treewalkVerify( i );
    dataChanged( i, i );
  }

  return st;
}


/*
 * Устанавливает свойства ячейки, флаги
 */
Qt::ItemFlags TestSequencesEditorTreeModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
  if (index.isValid()) {
    theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    if (index.column() == Name) {
      theFlags |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable/* |
                  Qt::ItemIsDragEnabled   | Qt::ItemIsDropEnabled*/;
    }
  }
  return theFlags;
}

/*
 * Прорисовка тестовой последовательности
 */
QVariant TestSequencesEditorTreeModel::data(const QModelIndex &index, int role) const {

  if ( !_rootItem || !index.isValid() || index.column() < 0 ||
      index.column() >= TestSequencesTableColumnsCount /*+ 1*/ ) {
    return QVariant();
  }

  if ( TestSequencesEditorTreeItem *item = itemForIndex(index)) {
    if ( role == Qt::DisplayRole || role == Qt::EditRole ) {
      switch ( index.column() ) {
        case Name:            return item->name();
        case Path:            return item->path();
        case Description:     return item->description();
        default: Q_ASSERT(false);
      }
    }

    bool ok;

    if ( role == Qt::CheckStateRole && index.column() == Name )
      return static_cast<int>(((bool)item->isExectable().toInt(&ok, 10)) ? Qt::Checked
                                                      : Qt::Unchecked);

    if ( role == Qt::TextAlignmentRole ) {
      if ( index.column() == Name ) {
          return static_cast<int>( Qt::AlignVCenter|
                                   Qt::AlignLeft );
      }
      return static_cast<int>( Qt::AlignVCenter| Qt::AlignRight );
    }

    if (role == Qt::DecorationRole && !item->icon().isNull()) {
      return ( QIcon ) (item->icon());
    }

  }

  return QVariant();
}

/*
 * Устанавливает Header таблицы
 */
QVariant TestSequencesEditorTreeModel::headerData(int section,
        Qt::Orientation orientation, int role) const {
  if ( orientation == Qt::Horizontal && role == Qt::DisplayRole ) {
    if ( section == Name ) {
      return tr("Название");
    }
    else if ( section == Path ) {
      return tr("Путь до скрипта");
    }
    else if ( section == Description ) {
      return tr("Описание");
    }
  }
  return QVariant();
}

/*
 * Возвращает количество строк
 */
int TestSequencesEditorTreeModel::rowCount(const QModelIndex &parent) const {
  if ( parent.isValid() && parent.column() != 0 ) {
    return 0;
  }

  TestSequencesEditorTreeItem *parentItem = itemForIndex( parent );
  return parentItem ? parentItem->childCount() : 0;
}

/*
 * Возвращает количество колонок
 */
int TestSequencesEditorTreeModel::columnCount(const QModelIndex &parent) const {
  return parent.isValid() && parent.column() != 0 ? 0 : (TestSequencesTableColumnsCount/*+1*/);
}

/*
 * Returns the index of the item in the model specified by the given row,
 * column and parent index.
 */
QModelIndex TestSequencesEditorTreeModel::index(int row, int column,
                             const QModelIndex &parent) const {

  if ( !_rootItem || row < 0 || column < 0 || column >= (TestSequencesTableColumnsCount/*+1*/)
      || ( parent.isValid() && parent.column() != 0 ) ) {
    return QModelIndex();
  }

  TestSequencesEditorTreeItem *parentItem = itemForIndex( parent );
  Q_ASSERT( parentItem );
  if ( TestSequencesEditorTreeItem *item = parentItem->childAt( row ) ) {
    return createIndex( row, column, item );
  }
  return QModelIndex();
}


/*
 *
 */
TestSequencesEditorTreeItem *TestSequencesEditorTreeModel::itemForIndex( const QModelIndex &index ) const {
  if (index.isValid()) {
    if ( TestSequencesEditorTreeItem *item = static_cast<TestSequencesEditorTreeItem*>(
         index.internalPointer()) ) {
      return item;
    }
  }
  return _rootItem;
}

/*
 * Вовзращает модельного индекса родителя
 */
QModelIndex TestSequencesEditorTreeModel::parent(const QModelIndex &index) const {
  if ( !index.isValid( ) ) {
    return QModelIndex();
  }
  if ( TestSequencesEditorTreeItem *childItem = itemForIndex( index ) ) {
    if ( TestSequencesEditorTreeItem *parentItem = childItem->parent() ) {
      if ( parentItem == _rootItem ) {
        return QModelIndex();
      }
      if ( TestSequencesEditorTreeItem *grandParentItem = parentItem->parent() ) {
        int row = grandParentItem->rowOfChild( parentItem );
        return createIndex( row, 0, parentItem );
      }
    }
  }
  return QModelIndex();
}

/*
 * Обход всего дерева на наличие установленных флажков.
 */
bool TestSequencesEditorTreeModel::treewalkCheckBox(const QModelIndex &in) {
  QModelIndex i;
  bool ok;

  for (int row = 0; row < rowCount(in); ++row) {
    i = index(row, 0, in);
    TestSequencesEditorTreeItem *item = itemForIndex(i);
    if (item->isExectable().toInt(&ok, 10)) {
      return true;
    }
    if (treewalkCheckBox(i)) {
      item->setExectableFlag(true);
      emit dataChanged(i, i);
      return true;
    }
  }
  return false;
}

/*
 * Обход всего дерева. Очистка поля времени исполнения.
 */
void TestSequencesEditorTreeModel::treewalkExecTimeClear( const QModelIndex &in ) {
  QModelIndex i;

  for ( int row = 0; row < rowCount( in ); ++row ) {
    i = index( row, 0, in );
    TestSequencesEditorTreeItem *item = itemForIndex(i);
    item->setIcon( QIcon() );
    emit dataChanged(i, i);
    treewalkExecTimeClear(i);
  }
}

/*
 * Снимает рекурсивно исполнение всех элементов теста
 */
void TestSequencesEditorTreeModel::unsetChilds(TestSequencesEditorTreeItem *item, int &offset) {
  item->setExectableFlag(false);
  offset++;
  for (int i=0; i < item->childCount(); i++) {
    unsetChilds(item->childAt(i), offset);
  }
}

/*
 * Устанавлвает рекурсивно исполнение всех элементов теста
 */
void TestSequencesEditorTreeModel::setChilds(TestSequencesEditorTreeItem *item) {
  item->setExectableFlag(true);
  for (int i=0; i < item->childCount(); i++) {
    setChilds(item->childAt(i));
  }
}

/*
 * Устанавливает данные в модель
 */
bool TestSequencesEditorTreeModel::setData( const QModelIndex &index,
                                      const QVariant &value, int role ) {

  // Если индекс не валидный, то возвращаем false
  if (!index.isValid()) {
    return false;
  }

  // Если индекс валидный, то получаем item элемента по индексу
  if (TestSequencesEditorTreeItem *item = itemForIndex(index)) {

    if (role == Qt::EditRole) {
      if (index.column() == Name) {
        item->setName(value.toString());
        emit change();
      }
    } else if (role == Qt::CheckStateRole) { // Если изменяется признак исполнения узла
        // Если нажали на первую колонку с именем узла
        if (index.column() == Name) {
          // Установка значения флага
          item->setExectableFlag(value.toBool());
          // Если установили флажок, то делаем ...
          if (value.toBool() == true) {

            // Устанавливаем дочерние флажки у этого
            setChilds(item);
            QModelIndex checkIndex = index;
            emit dataChanged(checkIndex, checkIndex);

            // ... проход по дереву до корня для того чтобы проставить флажки
            // на родительских узлах.
            // Это необходимо для того, чтобы поток исполнения знал какие узлы исполнять,
            // а какие пропустить.

            while (checkIndex != QModelIndex()) {
              checkIndex = checkIndex.parent();
              TestSequencesEditorTreeItem *checkItem = itemForIndex(checkIndex);
              if (checkItem->isExectable() != "1") {
                checkItem->setExectableFlag(true);
              }
            }
          }
          else {
            // ... проход по дереву по всем дочерним элементам для того чтобы снять флажки
            // с дочерних узлов.
            // Это необходимо для того, чтобы исполнитель правильно открыл тестовую последовательность
            QModelIndex checkIndex = index;
            TestSequencesEditorTreeItem *checkItem = itemForIndex(checkIndex);
            int offset = 0;
            unsetChilds(checkItem, offset);
            emit dataChanged(checkIndex, checkIndex.child(offset, 1));
          }
          emit change();
        }
    } else {
      return false;
    }
    emit dataChanged(index, index);
    return true;
  }

  return false;
}


/*
 * Вставка тест-кейса в модель
 */
bool TestSequencesEditorTreeModel::insertRows( int row, int count,
                                         const QModelIndex &parent ) {
  if ( !_rootItem ) {
    _rootItem = new TestSequencesEditorTreeItem;
  }
  TestSequencesEditorTreeItem *parentItem = parent.isValid() ? itemForIndex(parent)
                                          : _rootItem;
  beginInsertRows( parent, row, row + count - 1 );
  for ( int i = 0; i < count; ++i ) {
    // Без загрузки скрипта, состояние тоже не загружается
    TestSequencesEditorTreeItem *item =
        new TestSequencesEditorTreeItem( tr( "Новый тест-кейс... " ),
                                   tr( "" ),
                                   tr( "" ),
                                   tr( "" ),
                                   tr( "" ) );



    parentItem->insertChild( row, item );
  }

  endInsertRows();
  return true;
}

/*
 * Удаляет тест-кейсы из модели
 */
bool TestSequencesEditorTreeModel::removeRows(int row, int count,
                           const QModelIndex &parent) {
  if ( !_rootItem ) {
    return false;
  }
  TestSequencesEditorTreeItem *item = parent.isValid() ? itemForIndex(parent)
                                    : _rootItem;
  beginRemoveRows( parent, row, row + count - 1 );
  for ( int i = 0; i < count; ++i ) {
    delete item->takeChild(row);
  }
  endRemoveRows();
  return true;
}


/*
 * Проверяется выделенный элемент или нет
 */
bool TestSequencesEditorTreeModel::isChecked(const QModelIndex &index) const {
  if (!index.isValid()) {
    return false;
  }
  return data(index, Qt::CheckStateRole).toInt() == Qt::Checked;
}

/*
 * Перемещение тест-кейса вверх
 */
QModelIndex TestSequencesEditorTreeModel::moveUp(const QModelIndex &index) {
    if (!index.isValid() || index.row() <= 0)
        return index;
    TestSequencesEditorTreeItem *item = itemForIndex(index);
    Q_ASSERT(item);
    TestSequencesEditorTreeItem *parent = item->parent();
    Q_ASSERT(parent);
    return moveItem(parent, index.row(), index.row() - 1);
}

/*
 * Перемещение тест-кейса
 */
QModelIndex TestSequencesEditorTreeModel::moveItem(TestSequencesEditorTreeItem *parent, int oldRow,
                                int newRow) {
  Q_ASSERT( 0 <= oldRow && oldRow < parent->childCount() &&
            0 <= newRow && newRow < parent->childCount() );
  parent->swapChildren(oldRow, newRow);
  QModelIndex oldIndex = createIndex( oldRow, 0,
                                      parent->childAt(oldRow));
  QModelIndex newIndex = createIndex( newRow, 0,
                                      parent->childAt(newRow));
  emit dataChanged( oldIndex, newIndex );
  return newIndex;
}

/*
 * Переместить вниз тест-кейса
 */
QModelIndex TestSequencesEditorTreeModel::moveDown( const QModelIndex &index ) {
  if ( !index.isValid() ) {
    return index;
  }
  TestSequencesEditorTreeItem *item = itemForIndex(index);
  Q_ASSERT(item);
  TestSequencesEditorTreeItem *parent = item->parent();
  int newRow = index.row() + 1;
  if ( !parent || parent->childCount() <= newRow ) {
    return index;
  }
  return moveItem( parent, index.row(), newRow );
}

/*
 * Вырезать тест-кейс из тестовой последовательности
 */
QModelIndex TestSequencesEditorTreeModel::cut( const QModelIndex &index ) {
  if ( !index.isValid() ) {
    return index;
  }
  delete _cutItem;
  _cutItem = itemForIndex(index);
  Q_ASSERT(_cutItem);
  TestSequencesEditorTreeItem *parent = _cutItem->parent();
  Q_ASSERT(parent);
  int row = parent->rowOfChild(_cutItem);
  Q_ASSERT(row == index.row());
  beginRemoveRows(index.parent(), row, row);
  TestSequencesEditorTreeItem *child = parent->takeChild(row);
  endRemoveRows();
  Q_ASSERT(child == _cutItem);
  child = 0; // Silence compiler unused variable warning

  if (row > 0) {
    --row;
    return createIndex( row, 0, parent->childAt( row ) );
  }
  if ( parent != _rootItem ) {
    TestSequencesEditorTreeItem *grandParent = parent->parent();
    Q_ASSERT( grandParent );
    return createIndex( grandParent->rowOfChild( parent ), 0, parent );
  }
  return QModelIndex();
}

/*
 * Вставить тесткейс в тестовую последовательность
 */
QModelIndex TestSequencesEditorTreeModel::paste(const QModelIndex &index) {
  if ( !index.isValid() || !_cutItem ) {
    return index;
  }
  TestSequencesEditorTreeItem *sibling = itemForIndex(index);
  Q_ASSERT( sibling );
  TestSequencesEditorTreeItem *parent = sibling->parent();
  Q_ASSERT( parent );
  int row = parent->rowOfChild( sibling ) + 1;
  beginInsertRows( index.parent(), row, row );
  parent->insertChild( row, _cutItem );
  TestSequencesEditorTreeItem *child = _cutItem;
  _cutItem = 0;
  endInsertRows();
  return createIndex( row, 0, child );
}

/*
 * Продвижение элемента. То есть он становится дочерним для "деда".
 */
QModelIndex TestSequencesEditorTreeModel::promote( const QModelIndex &index ) {
  if ( !index.isValid() ) {
    return index;
  }
  TestSequencesEditorTreeItem *item = itemForIndex( index );
  Q_ASSERT( item );
  TestSequencesEditorTreeItem *parent = item->parent();
  Q_ASSERT( parent );
  if ( parent == _rootItem ) {
    return index; // Already a top-level item
  }
  int row = parent->rowOfChild( item );

  QModelIndex parentIndex = this->parent( index );

  beginRemoveRows( parentIndex, row, row );
  TestSequencesEditorTreeItem *child = parent->takeChild( row );
  Q_ASSERT( child == item );
  endRemoveRows();

  TestSequencesEditorTreeItem *grandParent = parent->parent();
  Q_ASSERT( grandParent );
  row = grandParent->rowOfChild( parent ) + 1;
  beginInsertRows( this->parent( parentIndex ), row, row );
  grandParent->insertChild( row, child );
  endInsertRows();
  QModelIndex newIndex = createIndex( row, 0, child );
  emit dataChanged( newIndex, newIndex );
  return newIndex;
}

/*
 * Понижение элемента. То есть он становится дочерним для верхнего смежного элемента.
 */
QModelIndex TestSequencesEditorTreeModel::demote(const QModelIndex &index) {
  if ( !index.isValid() ) {
    return index;
  }
  TestSequencesEditorTreeItem *item = itemForIndex( index );
  Q_ASSERT( item );
  TestSequencesEditorTreeItem *parent = item->parent();
  Q_ASSERT( parent );
  int row = parent->rowOfChild( item );
  if ( row == 0 ) {
    return index; // No preceding sibling to move this under
  }

  QModelIndex parentIndex = this->parent( index );

  beginRemoveRows( parentIndex, row, row );
  TestSequencesEditorTreeItem *child = parent->takeChild( row );
  Q_ASSERT( child == item );
  endRemoveRows();

  TestSequencesEditorTreeItem *sibling = parent->childAt( row - 1 );
  Q_ASSERT( sibling );
//  beginInsertRows( sibling->parent(), row, row);
  sibling->addChild( child );
//  endInsertRows();

  QModelIndex newIndex = createIndex( sibling->childCount() - 1, 0,
                                      child );
  emit dataChanged( newIndex, newIndex );
  return newIndex;
}

/*
 * Обновление состояния внешнего вида тест-кейса
 */
void TestSequencesEditorTreeModel::announceItemChanged( TestSequencesEditorTreeItem *item ) {
  if ( item == _rootItem ) {
    return;
  }
  TestSequencesEditorTreeItem *parent = item->parent();
  Q_ASSERT(parent);
  int row = parent->rowOfChild(item);
  QModelIndex startIndex = createIndex( row, static_cast<int>(Name),
                                       item);
  QModelIndex endIndex = createIndex( row, static_cast<int>(Description),
                                     item);
  emit dataChanged( startIndex, endIndex );
  // Update the parent & parent's parent etc too
  announceItemChanged( parent );
}

/*
 * Очистка модели
 */
void TestSequencesEditorTreeModel::clearModel() {
  delete _rootItem;
  _rootItem = 0;
  delete _cutItem;
  _cutItem = 0;
  beginResetModel();
  endResetModel();;
}

/*
 * Возвращает путь до тест-кейса по индексу
 */
QStringList TestSequencesEditorTreeModel::pathForIndex(const QModelIndex &index) const {
  QStringList path;
  QModelIndex thisIndex = index;
  while (thisIndex.isValid()) {
    path.prepend(data(thisIndex).toString());
    thisIndex = thisIndex.parent();
  }
  return path;
}

/*
 * Вовзращает индекс по путю к тест-кейсу
 */
QModelIndex TestSequencesEditorTreeModel::indexForPath(const QStringList &path) const {
  return indexForPath(QModelIndex(), path);
}

/*
 * Вовзращает индекс по путю к тест-кейсу
 */
QModelIndex TestSequencesEditorTreeModel::indexForPath(const QModelIndex &parent,
                                    const QStringList &path) const {
  if ( path.isEmpty() ) {
    return QModelIndex();
  }
  for ( int row = 0; row < rowCount( parent ); ++row ) {
    QModelIndex thisIndex = index( row, 0, parent );
    if ( data( thisIndex ).toString() == path.at( 0 ) ) {
      if ( path.count() == 1 ) {
        return thisIndex;
      }
      thisIndex = indexForPath( thisIndex, path.mid(1) );
      if ( thisIndex.isValid() ) {
        return thisIndex;
      }
    }
  }
  return QModelIndex();
}





