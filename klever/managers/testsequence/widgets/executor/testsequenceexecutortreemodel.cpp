#include "testsequenceexecutortreemodel.h"


using namespace Library::LoggerApi;

/**********************************************************************************************
 *                         Функции загрузки тестовой последовательности
 **********************************************************************************************/

/*
 * Возвращает индекс по путю к тест-кейсу
 */
void TestsequenceExecutorTreeModel::createConnectors()
{
  connect(this, SIGNAL(loaded()), this, SLOT(testsequenceLoaded()));
}

/*
 * Загрузка дерева тестовой последовательности в модель
 */
void TestsequenceExecutorTreeModel::load() {

//  _testName = name;
  clearModel();
  _rootItem = new TestsequenceExecutorTreeItem();

  _process.setDialog("Загрузка тестовой последовательности...");
  _process.start();

  /* Запуск потока загрузки файла */
  QFuture<void> future;
  future = QtConcurrent::run(this,
                             &TestsequenceExecutorTreeModel::loadInConcurrent,
                             _rootItem);



}

/*
 * Слот финиша загрузки тестовой последовательности
 */
void TestsequenceExecutorTreeModel::testsequenceLoaded() {
  _process.finish();
}

/*
 * Загрузка тестовой последовательности
 */
void TestsequenceExecutorTreeModel::loadInConcurrent(
  TestsequenceExecutorTreeItem *testcase
) {

  QString tableName = getTestsequenceStructureName();
  testcase->clearParam();
  readTestsequenceStructure(testcase, tableName);

  emit loaded();
}

/*
 * Возвращает внутреннее имя тест
 */
QString TestsequenceExecutorTreeModel::getTestsequenceStructureName() {

  // Проход по таблице testcases и поиск нужной нам таблицы
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_thread", "testcases", "structurename")) {
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
void TestsequenceExecutorTreeModel::readTestsequenceStructure(TestsequenceExecutorTreeItem *testcase, QString name) {

  // Формирование дерева теста
  // Проблема такого алгоритма в том что если родитель исполнять не надо, а дочерний элемент надо,
  // то откроется кашей тестовая последовательность. Поэтому в редакторе тестовой последовательности
  // При снятии с исполнения элемента, снимаются все его дочерние элементы.

  _level.clear();
  _level.append(0);
//  int levelPosition = 0;

  // Проход по таблице дерева тестовой последовательности
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_thread", name, "loadteststruct")) {
    logError(this, QString("Не удалось подключиться к БД %1(%2) !")
             .arg("cve_testsequence").arg(MySQLDataBaseApi::instance().getDescriptor("cve_testsequence", "testsequence_thread").lastError().text()));
    messageLibrary msg;
    msg.createWarnMessage(tr("Предупреждение"), tr("Не удалось подключиться к БД!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().records("loadteststruct");
    int size = MySQLDataBaseApi::instance().query()["loadteststruct"]->size();

    for (int i = 0; i < size; i++) {
      MySQLDataBaseApi::instance().query()["loadteststruct"]->seek(i);
      MySQLDataBaseApi::instance().query()["loadteststruct"]->at();

      if (MySQLDataBaseApi::instance().query()["loadteststruct"]->at() == QSql::BeforeFirstRow) {
        qDebug() << "QSql::BeforeFirstRow";
      }
      else if (MySQLDataBaseApi::instance().query()["loadteststruct"]->at() == QSql::AfterLastRow) {
        qDebug() << "QSql::AfterLastRow";
      }
      else {

        bool ok;
        int idVar              = MySQLDataBaseApi::instance().query()["loadteststruct"]->value(rec.indexOf("id")).toInt(&ok);
        int ParentIdVar        = MySQLDataBaseApi::instance().query()["loadteststruct"]->value(rec.indexOf("Parent_id")).toInt(&ok);
        QString nameNodeVar    = MySQLDataBaseApi::instance().query()["loadteststruct"]->value(rec.indexOf("Name_node")).toString();
        QString execFlagVar    = MySQLDataBaseApi::instance().query()["loadteststruct"]->value(rec.indexOf("Exec_flag")).toString();
        QString avrtimeVar     = MySQLDataBaseApi::instance().query()["loadteststruct"]->value(rec.indexOf("Avrtime")).toString();
        QString scriptFilename = MySQLDataBaseApi::instance().query()["loadteststruct"]->value(rec.indexOf("Script_filename")).toString();

        if (_level.size()<=ParentIdVar) {
          logError(this, "Выход за пределы списка(ParentIdVar).Чтение структуры тестовой последовательности");
          logError(this, QString("ParentIdVar = %1 size = %2").arg(ParentIdVar).arg(_level.size()));
          return;
        }

        int level = _level.at(ParentIdVar) + 1;
        _level.append(level);

        if (_level.size()<=idVar) {
          logError(this, "Выход за пределы списка(idVar).Чтение структуры тестовой последовательности");
          logError(this, QString("idVar = %1 size = %2").arg(idVar).arg(_level.size()));
          return;
        }

        TestsequenceExecutorTreeItem *item = testcase;

        if (_level.at(idVar-1) == _level.at(idVar)) {
          if (item!=NULL) {
            item = item->parent();
          }
        }
        else if (_level.at(idVar-1) > _level.at(idVar)) {
          for (int i = 0; i <= _level.at(idVar-1) - _level.at(idVar); i++ ) {
            // TODO: Необходимо исследовать случаи возниконовения item=NULL
            if (item!=NULL) {
              item = item->parent();
            }
          }
        }



//            levelPosition = _level.at(idVar);
          testcase = new TestsequenceExecutorTreeItem(nameNodeVar, avrtimeVar,
                                                      false, item);

          testcase->setExectableFlag(true);
          testcase->setPath(scriptFilename);

          if (execFlagVar == "1") {
            testcase->setStatus(getStatusString(TS_LOADED));
          }
          else {
            testcase->setStatus(getStatusString(TS_SKIPED));
          }

          testcase->setId(idVar);

          addParams(testcase,idVar);
      }

    }

  }
}

/*
 * Добавить параметры
 */
void TestsequenceExecutorTreeModel::addParams(TestsequenceExecutorTreeItem *item, int idnode) {

  bool ok;

  QString paramsTable = QString("testcase_param_%1").arg(*_testInternalName);

  // Проход по таблице testcases и поиск нужной нам таблицы
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_thread", paramsTable, "loadteststructparams")) {
    logWarning(this, QString("Не удалось добавить параметры в тест-кейс!"));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().records("loadteststructparams");
    int id = rec.indexOf("id");
    int Name = rec.indexOf("Name");
    int Value = rec.indexOf("Value");

    for (int i = 0; i < MySQLDataBaseApi::instance().query()["loadteststructparams"]->size(); i++) {
      MySQLDataBaseApi::instance().query()["loadteststructparams"]->seek(i);
      MySQLDataBaseApi::instance().query()["loadteststructparams"]->at();


      if (MySQLDataBaseApi::instance().query()["loadteststructparams"]->at() == QSql::BeforeFirstRow) {
        qDebug() << "QSql::BeforeFirstRow";
      }
      else if (MySQLDataBaseApi::instance().query()["loadteststructparams"]->at() == QSql::AfterLastRow) {
        qDebug() << "QSql::AfterLastRow";
      }
      else {
        if (MySQLDataBaseApi::instance().query()["loadteststructparams"]->value(id).toInt(&ok)==idnode) {
          QPair<QString,QString> pair;
          pair.first  = MySQLDataBaseApi::instance().query()["loadteststructparams"]->value(Name).toString();
          pair.second = MySQLDataBaseApi::instance().query()["loadteststructparams"]->value(Value).toString();
          item->addParam(pair);
        }
      }
    }
  }

}

/*
 * Установка среднего времени на исполнение скрипта рекурсивно
 */
void TestsequenceExecutorTreeModel::treewalkSetAvarageTimeTestSequence(const QModelIndex &in) {
  static QString tableName = "";
  QModelIndex i;

  if (tableName=="") {
    tableName = getTestsequenceStructureName();
  }

  for (int row = 0; row < rowCount(in); ++row) {
    i = index(row, 0, in);
    TestsequenceExecutorTreeItem *item = itemForIndex(i);
    if (!item->execTime().isEmpty()) {
      item->setAvarageTime(item->execTime());
      // Обновление полей среднего времени по ID
      QString query;
      query = QString(tr("UPDATE %1 SET Avrtime = '%2' WHERE id = %3;"))
                      .arg(tableName).arg(item->avarageTime()).arg(item->id());

      if (tableName!="")
      MySQLDataBaseApi::instance().sqlquery("cve_testsequence",
                                            "treewalkSetAvarageTimeTestSequence",
                                            query,
                                            "treewalkSetAvarageTimeTestSequence");
      emit dataChanged(i, i);
    }
    treewalkSetAvarageTimeTestSequence(i);
  }
}

/*
 * Верификация дерева тестовой последовательности
 */
QString TestsequenceExecutorTreeModel::treewalkVerify(const QModelIndex &in) {

  QModelIndex i;
  QString     st = "";

  if (in == QModelIndex()) {
    st.clear();
  }

  for (int row = 0; row < rowCount( in ); ++row) {
    i = index(row, 0, in);
    TestsequenceExecutorTreeItem *item = itemForIndex(i);
    if (!item->path().isEmpty()) {
      QString scriptPath;
      scriptPath = QString("%1/files/scripts%2").arg(QDir::currentPath()).arg(item->path());
      QFile file(scriptPath);
      if (!file.open( QIODevice::ReadOnly | QIODevice::Text) ) {
        st += QString(" - Скрипт {%1} не существует \n")
                      .arg( item->path() );
        item->setPath("");
      }
      file.close();
    }
    st += treewalkVerify(i);
    dataChanged(i, i);
  }

  return st;
}


/*
 * Устанавливает свойства ячейки, флаги
 */
Qt::ItemFlags TestsequenceExecutorTreeModel::flags(const QModelIndex &index) const {
  Qt::ItemFlags theFlags = QAbstractItemModel::flags(index);
  if (index.isValid()) {
    theFlags |= Qt::ItemIsSelectable|Qt::ItemIsEnabled;
    if (index.column() == Name) {
      theFlags |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable/* |
                  Qt::ItemIsDragEnabled   | Qt::ItemIsDropEnabled*/;
    }
    if (index.column() == DebugBreak){
        theFlags = Qt::NoItemFlags;
    }
  }
  return theFlags;
}

/*
 * Прорисовка тестовой последовательности
 */
QVariant TestsequenceExecutorTreeModel::data(const QModelIndex &index, int role) const {

  if (!_rootItem || !index.isValid() || index.column() < 0 ||
      index.column() >= TestSequencesTableColumnsCount /*+ 1*/) {
    return QVariant();
  }

  if ( TestsequenceExecutorTreeItem *item = itemForIndex(index)) {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      switch (index.column()) {
        case DebugBreak:      return QVariant();
        case Name:            return item->name();
        case Status:          return item->status();
        case ExecTime:        return item->execTime();
        case AvarageTime:     return item->avarageTime();
        default: Q_ASSERT(false);
      }
    }

    if (role == DebugRole && index.column() == DebugBreak){
      return item->debugBreak();
    }

    if (role == Qt::TextAlignmentRole) {
        if (index.column() == Name) {
            return static_cast<int>(Qt::AlignVCenter|
                                    Qt::AlignLeft);
        }
        return static_cast<int>( Qt::AlignVCenter| Qt::AlignRight);
    }

    if (role == Qt::DecorationRole && index.column() == ExecTime && !item->icon().isNull()) {
      return (QIcon) (item->icon());
    }

    if ((role == Qt::DecorationRole) && (index.column() == Status)) {

      QString iconFile;

      if (item->status() == getStatusString(TS_EXEC_SUCCESS)) {
        iconFile = ":/testsequence/img/confirm.ico";
      }
      else if (item->status() ==
                this->getStatusString(TS_EXEC_FAIL)) {
        iconFile = ":/testsequence/img/fail.ico";
      }
      else if (item->status() ==
                this->getStatusString(TS_EXECUTING)) {
        iconFile = ":/testsequence/img/process.ico";
      }
      else if (item->status() ==
                this->getStatusString(TS_PAUSED)) {
        iconFile = ":/testsequence/img/paused.ico";
      }
      else if (item->status() ==
                this->getStatusString(TS_EXECUTED_EARLY)) {
        iconFile = ":/testsequence/img/confirm.ico";
      }
      else if (item->status() ==
                this->getStatusString(TS_ABORTING)) {
        iconFile = ":/testsequence/img/aborted.ico";
      }
      else if (item->status() ==
                this->getStatusString(TS_LOADED)) {
        iconFile = ":/testsequence/img/ready.ico";
      }
      return QIcon(iconFile);
    }

    if ( role == Qt::BackgroundRole ) {

      if ( item->status() ==
           getStatusString(TS_EXEC_SUCCESS) ) {
        return QBrush( Qt::white );
      }
      else if ( item->status() ==
                getStatusString(TS_EXEC_FAIL) ) {
        return QBrush( Qt::red );
      }
      else if ( item->status() ==
                getStatusString(TS_EXECUTING) ) {
        return QBrush( Qt::yellow );
      }
      else if ( item->status() ==
                getStatusString(TS_PAUSED) ) {
        return QBrush( Qt::green );
      }
      else if ( item->status() ==
                getStatusString(TS_EXECUTED_EARLY) ) {
        return QBrush( Qt::white );
      }
      else if ( item->status() ==
                getStatusString(TS_ABORTING) ) {
        return QBrush( Qt::gray );
      }
      else if ( item->status() ==
                getStatusString(TS_SKIPED) ) {
        return QBrush( Qt::lightGray );
      }
      else if ( item->status() ==
                getStatusString(TS_LOADED) ) {
        return QBrush( Qt::white );
      }
      return QBrush( Qt::white );
    }
  }

  return QVariant();
}

/*
 * Устанавливает Header таблицы
 */
QVariant TestsequenceExecutorTreeModel::headerData(int section,
        Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {

    if (section == DebugBreak) {
      return tr("Brk");
    }

    if (section == Name) {
      return tr(" Название ");
    }
    else if (section == Status) {
      return tr(" Статус ");
    }
    else if (section == ExecTime) {
      return tr(" Время исполнения ");
    }
    else if (section == AvarageTime) {
      return tr(" Среднее необходимое время ");
    }

  }
  return QVariant();
}

/*
 * Возвращает количество строк
 */
int TestsequenceExecutorTreeModel::rowCount(const QModelIndex &parent) const {
  if ( parent.isValid() && parent.column() != 0 ) {
    return 0;
  }

  TestsequenceExecutorTreeItem *parentItem = itemForIndex( parent );
  return parentItem ? parentItem->childCount() : 0;
}

/*
 * Возвращает количество колонок
 */
int TestsequenceExecutorTreeModel::columnCount(const QModelIndex &parent) const {
  return parent.isValid() && parent.column() != 0 ? 0 : (TestSequencesTableColumnsCount/*+1*/);
}

/*
 * Returns the index of the item in the model specified by the given row,
 * column and parent index.
 */
QModelIndex TestsequenceExecutorTreeModel::index(int row, int column,
                             const QModelIndex &parent) const {

  if ( !_rootItem || row < 0 || column < 0 || column >= (TestSequencesTableColumnsCount/*+1*/)
      || ( parent.isValid() && parent.column() != 0 ) ) {
    return QModelIndex();
  }

  TestsequenceExecutorTreeItem *parentItem = itemForIndex( parent );
  Q_ASSERT( parentItem );
  if ( TestsequenceExecutorTreeItem *item = parentItem->childAt( row ) ) {
    return createIndex( row, column, item );
  }
  return QModelIndex();
}

/*
 * Возвращает элемент по индексу
 */
TestsequenceExecutorTreeModel::TestsequenceExecutorTreeModel(QObject *parent)
{
  Q_UNUSED(parent)

  _rootItem = NULL;
  currentExecItem = NULL;

  // Инициализация хеша статусов состояний исполнения теста
  _statusHash[TS_EXEC_SUCCESS]   = tr("Успешно");        // Тест успешно выполнен
  _statusHash[TS_EXEC_FAIL]      = tr("Ошибка");         // При исполнении теста произошла ошибка
                                                         // Ошибка может быть инициалирована сообщением
                                                         // test.error("error"); из скрипта, так и потоком исполнения скрипта
                                                         // в тот момент, когда скрипт не удалось выполнить.
  _statusHash[TS_EXECUTING]      = tr("Выполняется");    // Тест выполняется в данный момент...
  _statusHash[TS_PAUSED]         = tr("Приостановлен");  // TODO: Deprecated
                                                         // Необходимости в этом сильной нет, в будущем удалю
  _statusHash[TS_EXECUTED_EARLY] = tr("Выполнен ранее"); // Если тест был приостановлен, затем тест запустили повторно
                                                         // то предыдущии тест-кейсы будут помечены как выполненные ранее
  _statusHash[TS_ABORTING]       = tr("Прерван");        // Прерванный тест. Может быть по нажатию на Стоп или при ошибке
  _statusHash[TS_SKIPED]         = tr("Пропущен");       // TODO: Deprecated
                                                         // Ранее когда флажки исполнения не стояли, то тест-кейс не исполнялся,
                                                         // теперь же при разделении на 2 формы(исполнитель и редактор) в этом
                                                         // этом нет необхаодимости
  _statusHash[TS_LOADED]         = tr("Готов");          // Тест загружен
  _statusHash[TS_DEBUG]          = tr("Отладка");        // TODO:???

  createConnectors();

}

/*
 * Возвращает состояние тест-кейса
 */
QString TestsequenceExecutorTreeModel::getStatusString(int state) const
{
  return _statusHash[state];
}

/*
 * Возвращает item по индексу
 */
TestsequenceExecutorTreeItem *TestsequenceExecutorTreeModel::itemForIndex( const QModelIndex &index ) const {
  if (index.isValid()) {
    if ( TestsequenceExecutorTreeItem *item = static_cast<TestsequenceExecutorTreeItem*>(
         index.internalPointer()) ) {
      return item;
    }
  }
  return _rootItem;
}

/*
 * Возвращает модельного индекса родителя
 */
QModelIndex TestsequenceExecutorTreeModel::parent(const QModelIndex &index) const {
  if ( !index.isValid( ) ) {
    return QModelIndex();
  }
  if ( TestsequenceExecutorTreeItem *childItem = itemForIndex( index ) ) {
    if ( TestsequenceExecutorTreeItem *parentItem = childItem->parent() ) {
      if ( parentItem == _rootItem ) {
        return QModelIndex();
      }
      if ( TestsequenceExecutorTreeItem *grandParentItem = parentItem->parent() ) {
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
bool TestsequenceExecutorTreeModel::treewalkCheckBox(const QModelIndex &in) {
  QModelIndex i;
  bool ok;

  for (int row = 0; row < rowCount(in); ++row) {
    i = index(row, 0, in);
    TestsequenceExecutorTreeItem *item = itemForIndex(i);
    if (item->isExectable().toInt(&ok, 10)) {
      return true;
    }
    if (treewalkCheckBox(i)) {
//      item->setExectableFlag(true);
      emit dataChanged(i, i);
      return true;
    }
  }
  return false;
}

/*
 * Обход всего дерева. Очистка поля времени исполнения.
 */
void TestsequenceExecutorTreeModel::treewalkExecTimeClear( const QModelIndex &in ) {
  QModelIndex i;

  for (int row = 0; row < rowCount( in ); ++row) {
    i = index(row, 0, in);
    TestsequenceExecutorTreeItem *item = itemForIndex( i );
    item->setExecTime("");
    if (!item->path().isEmpty()) {
      if (item->status() != getStatusString(TS_SKIPED))
      item->setStatus(getStatusString(TS_LOADED));
    }
    item->setIcon(QIcon());
    emit dataChanged(i, i);
    treewalkExecTimeClear(i);
  }
}

/*
 * Устанавливает данные в модель
 */
bool TestsequenceExecutorTreeModel::setData( const QModelIndex &index,
                                      const QVariant &value, int role ) {
  if (!index.isValid()) {
    return false;
  }

  emit setDataChanged();

  if (TestsequenceExecutorTreeItem *item = itemForIndex(index)) {

    if ( role == DebugRole ){
      if (index.column() == DebugBreak){
          item->setDebugBreak(item->path().isEmpty() ? false : value.toBool());
      }
    } else {
      return false;
    }
    emit dataChanged( index, index );
    return true;
  }

  return false;
}

/*
 * Вставка тест-кейса в модель
 */
bool TestsequenceExecutorTreeModel::insertRows( int row, int count,
                                               const QModelIndex &parent ) {
  if (!_rootItem) {
    _rootItem = new TestsequenceExecutorTreeItem;
  }
  TestsequenceExecutorTreeItem *parentItem = parent.isValid() ? itemForIndex(parent)
                                          : _rootItem;
  beginInsertRows( parent, row, row + count - 1 );
  for ( int i = 0; i < count; ++i ) {
    // Без загрузки скрипта, состояние тоже не загружается
    TestsequenceExecutorTreeItem *item =
        new TestsequenceExecutorTreeItem(tr("Новый тест-кейс..."), tr(""));



    parentItem->insertChild( row, item );
  }

  endInsertRows();
  return true;
}

/*
 * Удаляет тест-кейсы из модели
 */
bool TestsequenceExecutorTreeModel::removeRows(int row, int count,
                           const QModelIndex &parent) {
  if ( !_rootItem ) {
    return false;
  }
  TestsequenceExecutorTreeItem *item = parent.isValid() ? itemForIndex(parent)
                                    : _rootItem;
  beginRemoveRows( parent, row, row + count - 1 );
  for ( int i = 0; i < count; ++i ) {
    delete item->takeChild(row);
  }
  endRemoveRows();
  return true;
}

/*
 * Обновление состояния внешнего вида тест-кейса
 */
void TestsequenceExecutorTreeModel::announceItemChanged( TestsequenceExecutorTreeItem *item ) {
  if ( item == _rootItem ) {
    return;
  }
  TestsequenceExecutorTreeItem *parent = item->parent();
  Q_ASSERT(parent);
  int row = parent->rowOfChild(item);
  QModelIndex startIndex = createIndex( row, static_cast<int>(Name),
                                       item);
  QModelIndex endIndex = createIndex( row, static_cast<int>(ExecTime),
                                     item);
  emit dataChanged( startIndex, endIndex );
  // Update the parent & parent's parent etc too
  announceItemChanged( parent );
}

/*
 * Установка иконки для определенного состояния таймера
 */
void TestsequenceExecutorTreeModel::setIconForTimedItem( const QIcon &icon ) {
  currentExecItem->setIcon( icon );
}

/*
 * Очистка модели
 */
void TestsequenceExecutorTreeModel::clearModel() {
  delete _rootItem;
  _rootItem = 0;
  beginResetModel();
  endResetModel();;
}



/*
 * Возвращает путь до тест-кейса по индексу
 */
QStringList TestsequenceExecutorTreeModel::pathForIndex(const QModelIndex &index) const {
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
QModelIndex TestsequenceExecutorTreeModel::indexForPath(const QStringList &path) const {
  return indexForPath(QModelIndex(), path);
}

QModelIndex TestsequenceExecutorTreeModel::indexForPath(const QModelIndex &parent,
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


