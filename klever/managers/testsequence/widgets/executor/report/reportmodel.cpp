#include "reportmodel.h"

#include <library/setupApi/app.h>
#include <frameWork/cveManager.h>
#include <frameWork/gui/cvegui.h>
#include <library/setupApi/sessions.h>

#include <frameWork/cve.h>


/*
 * Устанавливает свойства ячейки, флаги
 */
Qt::ItemFlags ReportModel::flags(const QModelIndex &index) const {
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
 * Прорисовка отчета
 */
QVariant ReportModel::data(const QModelIndex &index, int role) const {

  if (!_rootItem || !index.isValid()
       || index.column() < 0 || index.column() >= ReportColumnCount) {
    return QVariant();
  }

  if (ReportTreeItem *item = itemForIndex(index)) {
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
      switch ( index.column() ) {
        case Name:     return item->name();
        case Status:   return item->status();
        case Duration: return item->execTime();
        case Message:  return item->msg();
        default: Q_ASSERT(false);
      }
    }

    if (role == Qt::TextAlignmentRole) {
//      if (index.column() == Name) {
        return static_cast<int>(Qt::AlignVCenter | Qt::AlignLeft);
//      }
//      return static_cast<int>(Qt::AlignVCenter| Qt::AlignRight);
    }

    if (role == Qt::FontRole) {
      if (index.column() == Status) {
        QFont serifFont("Times", 10, QFont::Bold);
        return serifFont;
      }
      if (index.column() == Duration) {
        QFont serifFont("Times", 10, QFont::Normal);
        serifFont.setItalic(true);
        return serifFont;
      }
      if (index.column() == Name) {
        QFont serifFont("Times", 12, QFont::Normal);
        return serifFont;
      }

    }

    if ((role == Qt::DecorationRole) && (index.column() == Status)) {
      QString iconFile;
      if (item->status() == "Информация") {
        iconFile = ":/testsequence/img/info.png";
      }
      else if (item->status() == "Ошибка") {
        iconFile = ":/testsequence/img/error.png";
      }
      else if (item->status() == "Предупреждение") {
        iconFile = ":/testsequence/img/warn.png";
      }
      return QIcon(iconFile);
    }


  }

  return QVariant();
}

/*
 * Устанавливает заголовок таблицы
 */
QVariant ReportModel::headerData(int section,
        Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section == Name) {
      return tr("Название");
    }
    else if (section == Status) {
      return tr("Тип");
    }
    else if (section == Duration) {
      return tr("Время");
    }
    else if (section == Message) {
      return tr("Сообщение");
    }
  }
  return QVariant();
}

/*
 * Возвращает количество строк
 */
int ReportModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid() && parent.column() != 0) {
    return 0;
  }

  ReportTreeItem *parentItem = itemForIndex(parent);
  return parentItem ? parentItem->childCount() : 0;
}

/*
 * Возвращает количество колонок
 */
int ReportModel::columnCount(const QModelIndex &parent) const {
  return parent.isValid() && parent.column() != 0 ? 0 : ReportColumnCount;
}

/*
 * Возвращает индекс элемента по строке, колонке и модельному индексу родителя.
 */
QModelIndex ReportModel::index(int row, int column,
                             const QModelIndex &parent) const {

  if (!_rootItem || row < 0 || column < 0 || column >= ReportColumnCount
      || ( parent.isValid() && parent.column() != 0)) {
    return QModelIndex();
  }

  ReportTreeItem *parentItem = itemForIndex(parent);
  Q_ASSERT( parentItem );
  if (ReportTreeItem *item = parentItem->childAt(row)) {
    return createIndex(row, column, item);
  }
  return QModelIndex();
}

/*
 * Возвращает элемент по индексу
 */
ReportTreeItem *ReportModel::itemForIndex( const QModelIndex &index ) const {
  if (index.isValid()) {
    if (ReportTreeItem *item = static_cast<ReportTreeItem*>(
         index.internalPointer())) {
      return item;
    }
  }
  return _rootItem;
}

/*
 * Вовзращает модельного индекса родителя
 */
QModelIndex ReportModel::parent(const QModelIndex &index) const {
  if ( !index.isValid( ) ) {
    return QModelIndex();
  }
  if ( ReportTreeItem *childItem = itemForIndex(index)) {
    if ( ReportTreeItem *parentItem = childItem->parent()) {
      if (parentItem == _rootItem) {
        return QModelIndex();
      }
      if (ReportTreeItem *grandParentItem = parentItem->parent()) {
        int row = grandParentItem->rowOfChild(parentItem);
        return createIndex(row, 0, parentItem);
      }
    }
  }
  return QModelIndex();
}

/*
 * Устанавливает данные в модель
 */
bool ReportModel::setData( const QModelIndex &index,
                                      const QVariant &value, int role ) {
  if (!index.isValid() || index.column() != Name) {
    return false;
  }
  if (ReportTreeItem *item = itemForIndex(index)) {
    if (role == Qt::EditRole) {
      item->setName(value.toString());
    }
//    else if ( role == Qt::CheckStateRole ) {
//      item->setExectableFlag( value.toBool() );
//      QModelIndex checkIndex = index;
//      while ( checkIndex != QModelIndex() ) {
//        emit dataChanged( checkIndex, checkIndex );
//        checkIndex = checkIndex.parent();
//        ReportManagerTreeItem *checkItem = itemForIndex( checkIndex );
//        checkItem->setExectableFlag( true );
//      }
//      treewalkCheckBox( QModelIndex() );
//    }
    else {
      return false;
    }
    emit dataChanged(index, index);
    return true;
  }
  return false;
}

/*
 * Очистка модели
 */
void ReportModel::clear() {
  delete _rootItem;
  _rootItem = 0;
  beginResetModel();
  endResetModel();
}

/*
 * Проверка существовавния элемента по имени
 */
bool ReportModel::isItemByNameExist( QString name ) {
  for (int i = 0; i < _items.size(); i++) {
    if (_items.at(i)->name() == name) {
      return true;
    }
  }
  return false;
}

/*
 * Возвращает путь до элемента по индексу
 */
QStringList ReportModel::pathForIndex(const QModelIndex &index) const {
  QStringList path;
  QModelIndex thisIndex = index;
  while (thisIndex.isValid()) {
    path.prepend(data(thisIndex).toString());
    thisIndex = thisIndex.parent();
  }
  return path;
}

/*
 * Вовзращает индекс по путю к элементу
 */
QModelIndex ReportModel::indexForPath(const QStringList &path) {
  return indexForPath(QModelIndex(), path);
}

/*
 * Возвращает индекс по путю к элементу
 */
QModelIndex ReportModel::indexForPath(const QModelIndex &parent,
                                    const QStringList &path)  {
  if ( path.isEmpty() ) {
    return QModelIndex();
  }
  for ( int row = 0; row < rowCount( parent ); ++row ) {
    QModelIndex thisIndex = index( row, 0, parent );
    if (path.size()>=1) {
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
    else {
      logError(this, "Путь пустой при возвращении индекса к элементу");
      return QModelIndex();
    }
  }
  return QModelIndex();
}

/*
 * Установка состояний вверх по дереву
 */
void ReportModel::setStateUp(int id, QString state) {

  // Формирование названия таблицы отчета
  QString table = QString("report_%1_%2")
      .arg(Cve::instance().getParameterValue(QString("reportTimeDate"), QString("NOTIME")))
      .arg(*_testInternalName);

  // Проход по таблице дерева тестовой последовательности
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "setStates_select", table, "setStateUp")) {
    logWarning(this,
               QString("Не удалось подгрузить отчет из БД(%1)!")
               .arg(MySQLDataBaseApi::instance().getDescriptor("cve_testsequence", "setStates_select").lastError().text()));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["setStateUp"]->record();

    if (MySQLDataBaseApi::instance().query()["setStateUp"]->size() > 0) {
      while (MySQLDataBaseApi::instance().query()["setStateUp"]->next()) {

        bool ok;
        int idVar         = MySQLDataBaseApi::instance().query()["setStateUp"]->value(rec.indexOf("id")).toInt(&ok);
        int parentIdVar   = MySQLDataBaseApi::instance().query()["setStateUp"]->value(rec.indexOf("Parent_id")).toInt(&ok);
        QString statusVar = MySQLDataBaseApi::instance().query()["setStateUp"]->value(rec.indexOf("Status")).toString();


        // Нашли запись с идентификатором заданным вторым параметров функции
        if (idVar == id) {

          QString status;
          status.clear(); // Если это значение останется пустым, значит все хорошо и update выполнять не стоит уже повторно

          // Вычисляем состояние записи
          if ((state=="Ошибка")&&(statusVar!="Ошибка")) {
            // Если переданное состояние Ошибка, а в поле состояния записи либо пусто, либо Информация, либо Предупреждение.
            status = state;
          }
          else if ((state=="Предупреждение")&&(statusVar!="Предупреждение")&&(statusVar!="Ошибка")) {
            // Если переданное состояние Предупреждения, а в поле состояния записи либо пусто, либо Информация, либо Предупреждение.
            // И при этом там не будет Ошибка.
            status = state;
          }
          else if ((state=="Информация")&&(statusVar!="Информация")&&(statusVar!="Предупреждение")&&(statusVar!="Ошибка")) {
            // Если переданное состояние Информация, а в поле состояния записи либо пусто, либо Информация.
            // И при этом там не будет Ошибка или Предупреждение.
            status = state;
          }

          // Обновление записи результатом
          if ((id>0)&&(!status.isEmpty())) {
            QString query;
            query = QString(tr("UPDATE %1 SET Status = '%2' WHERE id = %3;")).arg(table).arg(status).arg(id);
            MySQLDataBaseApi::instance().sqlquery("cve_testsequence", "setStates_update", query, "setStateUp");
          }

          // Рекурсивный подъем до корневого элемента дерева
          if (parentIdVar>0 /*Нулем кодируется корень*/) {
            // До тех пор пока не дошли до корня, рекурсивно входим в эту же функцию, но
            // только в качестве первого аргумента передаем идентификатор родителя
            setStateUp(parentIdVar, status);
            return;
          }
          else {
            // .. если родитель = 0, то не продолжаем цикл, а просто выходим из функции
            return;
          }

        }
      }
    }
  }
}


/*
 * Установка времени исполнения тест-кейсов
 */
void ReportModel::setTestcasesTimeUp(int id, QString time) {

  // Формирование названия таблицы отчета
  QString table = QString("report_%1_%2")
      .arg(Cve::instance().getParameterValue(QString("reportTimeDate"), QString("NOTIME")))
      .arg(*_testInternalName);

  // Проход по таблице дерева тестовой последовательности
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "setTestcasesTime_select", table, "setTestcaseTimeUp")) {
    logWarning(this,
               QString("Не удалось подгрузить отчет из БД(%1)!")
               .arg(MySQLDataBaseApi::instance().getDescriptor("cve_testsequence", "setTestcasesTime_select").lastError().text()));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["setTestcaseTimeUp"]->record();

    if (MySQLDataBaseApi::instance().query()["setTestcaseTimeUp"]->size() > 0) {
      while (MySQLDataBaseApi::instance().query()["setTestcaseTimeUp"]->next()) {

        bool ok;
        int idVar           = MySQLDataBaseApi::instance().query()["setTestcaseTimeUp"]->value(rec.indexOf("id")).toInt(&ok);
        int parentIdVar     = MySQLDataBaseApi::instance().query()["setTestcaseTimeUp"]->value(rec.indexOf("Parent_id")).toInt(&ok);
        QString execTimeVar = MySQLDataBaseApi::instance().query()["setTestcaseTimeUp"]->value(rec.indexOf("Exec_time")).toString();

        bool isNeedUpdate = false;

        // Нашли запись с идентификатором заданным вторым параметров функции
        if (idVar == id) {

          if (execTimeVar.isEmpty()) {
            execTimeVar  = time;
            isNeedUpdate = true;
          }
          else {
            execTimeVar = addTime(execTimeVar, time);
            isNeedUpdate = true;
          }

          // Обновление записи результатом
          if (isNeedUpdate) {
            QString query;
            query = QString(tr("UPDATE %1 SET Exec_time = '%2' WHERE id = %3;")).arg(table).arg(execTimeVar).arg(id);
            MySQLDataBaseApi::instance().sqlquery("cve_testsequence", "setTestcasesTime_update", query, "setTestcaseTimeUp");
          }

          // Рекурсивный подъем до корневого элемента дерева
          if (parentIdVar>0 /*Нулем кодируется корень*/) {
            // До тех пор пока не дошли до корня, рекурсивно входим в эту же функцию, но
            // только в качестве первого аргумента передаем идентификатор родителя
            setTestcasesTimeUp(parentIdVar, execTimeVar);
            return;
          }
          else {
            // .. если родитель = 0, то не продолжаем цикл, а просто выходим из функции
            return;
          }

        }
      }
    }
  }
}

/*
 * Сложить два временных интервала
 */
QString ReportModel::addTime(QString t1, QString t2) {

  QTime _t1,_t2;

  _t1 = QTime::fromString(t1, "h:mm:ss:zzz");
  _t2 = QTime::fromString(t2, "h:mm:ss:zzz");

  int t1int = 1000*60*60*_t1.hour() + 1000*60*_t1.minute() + 1000*_t1.second() + _t1.msec();
  int t2int = 1000*60*60*_t2.hour() + 1000*60*_t2.minute() + 1000*_t2.second() + _t2.msec();

  int elapsed = t1int+t2int;

  // Подсчет времени исполнения тестовой последовательности (часы, минуты, секунды)
  int hour = ( ( ( ( elapsed / 1000 ) / 60 ) / 60 ) % 24 );
  int min  = ( ( ( elapsed / 1000 ) / 60 ) ) % 60 ;
  int sec  = ( elapsed / 1000 ) % 60;
  int msec = ( elapsed % 1000 );

  QString sumTime = QString("%1:%2:%3:%4")
                .arg(hour)
                .arg(min,  2, 10, QChar('0'))
                .arg(sec,  2, 10, QChar('0'))
                .arg(msec, 3, 10, QChar('0'));

  return  sumTime;
}



/*
 * Установка времени по идентификатору
 */
void ReportModel::setExecTimeToReportById(int id, QString time)
{
  QString query;

  QString table = QString("report_%1_%2")
      .arg(Cve::instance().getParameterValue(QString("reportTimeDate"), QString("NOTIME")))
      .arg(*_testInternalName);

  // Обновление значения времени по идентификатору
  query = QString(tr("UPDATE %1 SET Exec_time = '%2' WHERE id = %3;")).arg(table).arg(time).arg(id);
  if (MySQLDataBaseApi::instance().sqlquery("cve_testsequence", "testsequence_timer", query, "setExecTimeToReportById")) {}
}


/*
 * Загрузка отчета тестовой последовательности
 */
void ReportModel::readReportTreeFromDatabase(
  ReportTreeItem *testcase
) {

  _level.clear();
  _idStateList.clear();
  _idTimeList.clear();
  _level.append(0);

  QString table = QString("report_%1_%2")
      .arg(Cve::instance().getParameterValue(QString("reportTimeDate"), QString("NOTIME")))
      .arg(*_testInternalName);


  // Проход по таблице дерева тестовой последовательности
  if (!MySQLDataBaseApi::instance().selectAllDataFromTable("cve_testsequence", "testsequence_timer", table, "loadreport")) {
    logWarning(this,
               QString("Не удалось подгрузить отчет из БД(%1)!")
               .arg(MySQLDataBaseApi::instance().getDescriptor("cve_testsequence", "testsequence_timer").lastError().text()));
  }
  else {
    QSqlRecord rec = MySQLDataBaseApi::instance().query()["loadreport"]->record();

    if (MySQLDataBaseApi::instance().query()["loadreport"]->size() > 0) {
      while (MySQLDataBaseApi::instance().query()["loadreport"]->next()) {

        bool ok;

        QSqlQuery *tquery;
        tquery = MySQLDataBaseApi::instance().query()["loadreport"];

        if (tquery==NULL) {
          logError(this, "tquery NULL");
          return;
        }

        int idVar           = tquery->value(rec.indexOf("id")).toInt(&ok);
        QString nameNodeVar = tquery->value(rec.indexOf("Name_node")).toString();
        int parentIdVar     = tquery->value(rec.indexOf("Parent_id")).toInt(&ok);
        QString statusVar   = tquery->value(rec.indexOf("Status")).toString();
        QString msgVar      = tquery->value(rec.indexOf("Msg")).toString();
        QString execTimeVar = tquery->value(rec.indexOf("Exec_time")).toString();

        ReportTreeItem *item;
        item = testcase;

        // Проверка на наличия сообщения
        // Записи с идентификаторами -1 в таблице кодируются как сообщения
        // записи больше нуля - узлы дерева тестов
        if (idVar!=-1) {

          QPair<int, QString> p;
          p.first  = idVar;
          p.second = QString("0:00:00:000");
          _idTimeList.append(p);

          int level;

          if (_level.size()>parentIdVar) {
            level= _level.at(parentIdVar) + 1;
          }
          else {
            logError(this, "Выход за пределы списка(parentIdVar). Загрузка отчета тестовой последовательности.");
            return;
          }

          _level.append(level);

          if (_level.size()<=idVar){
            logError(this, "Выход за пределы списка(idVar). Загрузка отчета тестовой последовательности.");
            logError(this, QString("Длина списка=%1 идентификатор=%2").arg(_level.size()).arg(idVar));
            return;
          }

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

          // Проверяем наличие элемента
          bool isItemExist = false;

          // Ищем такой элемент по идентификатору
          isItemExist = false;
          for (int i = 0; i < item->children().size(); i++) {
            if (item->childAt(i)->id() == idVar) {
              testcase = item->childAt(i);
              isItemExist = true;
              break;
            }
          }

          // Если такой элемент существует, то проверяем у него
          // execTimeVar, statusVar, msgVar - обновляем,
          // иначе добавляем новый элемент
          if (isItemExist) {
            if (statusVar != testcase->status()) {
              testcase->setStatus(statusVar);
            }
            if (execTimeVar != testcase->execTime()) {
              testcase->setExecTime(execTimeVar);
            }
            if (msgVar != testcase->msg()) {
              testcase->setMsg(msgVar);
            }
          }
          else {
            // Создаем новый элемент дерева и передаем в конструктор ему элемент родителя
            // Чтобы помнил.
            testcase = new ReportTreeItem(item); // Ранее item = testcase;
                                                 // то есть item - родительский элемент
            testcase->setId(idVar);
            testcase->setName(nameNodeVar);
            testcase->setStatus(statusVar);
            testcase->setMsg(msgVar);
            testcase->setExecTime(execTimeVar);
          }
        }
        else {

          ReportTreeItem *result = NULL;

          // Корневой элемент дерева, хотел QModelIndex() передать первым параметров
          // в функцию, но компилятор выводит ошибку.
          QModelIndex rootElement = QModelIndex();

          // Функция ищет тесткейс-родителя по идентификатору, чтобы добавить сообщение к этому
          // тесткейсу. Если в этом тесткейсе уже есть такое сообщение, то оно не дублируется.
          result = treewalkFindTestcaseByIDAndSetMessage(rootElement, parentIdVar);

          if (result!=NULL) {

            QPair<int, QString> p;
            p.first  = result->id();
            p.second = statusVar;
            _idStateList.append(p);

            // Проверяем наличие элемента
            bool isItemExist = false;

            // Ищем такой элемент
            for (int i = 0; i < result->children().size(); i++) {
              if ((result->childAt(i)->name() == nameNodeVar)&&
                  (result->childAt(i)->msg() == msgVar)) {
                testcase = result->childAt(i);
                isItemExist = true;
                break;
              }
            }

            if (!isItemExist) {
              // testcase Указывает на сообщение
              testcase = new ReportTreeItem(result); // result - родительский элемент
              testcase->setId(idVar);
              testcase->setName(nameNodeVar);
              testcase->setStatus(statusVar);
              testcase->setMsg(msgVar);
              testcase->setExecTime(execTimeVar);
            }

            testcase = item;
            //emit dataChanged(QModelIndex(), QModelIndex());
          }

        }
      }
    }
  }

}

/*
 * Функция ищет тесткейс-родителя по идентификатору
 */
ReportTreeItem *ReportModel::treewalkFindTestcaseByIDAndSetMessage(QModelIndex &in, int parentIdVar) {

  ReportTreeItem *result = NULL;

  for (int row = 0; row < rowCount(in); ++row) {
    QModelIndex i = index(row, 0, in);
    ReportTreeItem *item = itemForIndex(i);

    // Если смогли найти идентификатор родителя в дереве тестов
    if (item->id()==parentIdVar) {
      return item;
    }

    result = treewalkFindTestcaseByIDAndSetMessage(i, parentIdVar);
    if (result!=NULL) {
      return result;
    }
  }

  return NULL;
}

/*
 * Проход по дереву тестовых последовательностей для получания списка основных
 * результатов тестирования
 */
void ReportModel::treewalkGetMainResultsList(const QModelIndex &in,
                                                    int   deep,
                                                    QList<smallReportContentListStruct> &c) {

  QModelIndex i;
  for (int row = 0; row < rowCount(in); ++row) {
    i = index( row, 0, in );
    ReportTreeItem *item = itemForIndex(i);

    //Если первый уровень тестового дерева
    if (deep==1) {
      smallReportContentListStruct content;
      content.testName = item->name();
      content.result   = item->status();
      content.time     = item->execTime();
      c.append(content);
    }

    int level = deep;
    level++;
    treewalkGetMainResultsList(i, level, c);
  }
}

/*
 * Проход по дереву тестовых последовательностей для получания списка всех
 * результатов тестирования
 */
void ReportModel::treewalkGetAllResultsList(const QModelIndex &in,
                                                  int   deep,
                                                  QList<smallReportContentListStruct> &c) {

  QModelIndex i;
  for (int row = 0; row < rowCount(in); ++row) {
    i = index( row, 0, in );
    ReportTreeItem *item = itemForIndex(i);

    // Если первый уровень тестового дерева

    smallReportContentListStruct content;
    content.level    = deep;
    content.testName = item->name();
    content.result   = item->status();
    content.time     = item->execTime();
    content.description     = item->msg();
    c.append(content);

    int level = deep;
    level++;
    treewalkGetAllResultsList(i, level, c);
  }
}

/*
 * Финализация состояний тест-кейсов
 */
void ReportModel::finalizeTestState() {

  for (int i=0; i<_idStateList.size(); i++) {
    setStateUp(_idStateList.at(i).first, _idStateList.at(i).second);
  }
  for (int i=0; i<_idTimeList.size(); i++) {
    setTestcasesTimeUp(_idTimeList.at(i).first, _idTimeList.at(i).second);
  }
}

