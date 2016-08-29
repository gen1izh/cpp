#include "sessionstable.h"
#include <library/message/messagelibrary.h>

// Подключение библиотек ядра
#include <library/utilsLibrary/utilslibrary.h>

#include <QtSql>
#include <QSqlDatabase>
#include <QTableView>
#include <QSqlTableModel>

using namespace SessionViewNamespace;

/*!
 * \brief Заголовок таблицы
 */
QHash<int,QString> tableHeader;

void SessionViewNamespace::fillTableHeaderHash()
{
  tableHeader[SESSION_NAME]  = "Название сессии";
  tableHeader[PRODUCT_TYPE]  = "Тип изделия";
  tableHeader[RIGHTS]        = "Права";
  tableHeader[SERIAL_NUMBER] = "Серийный номер";
  tableHeader[OTHER]         = "Доп. информация";
}


SessionsTable::SessionsTable(QDialog *parent) : QDialog(parent)
{
  _sessionManagerGridLayout = new QGridLayout;

  _model = NULL;

  _sessionManagerTable.setSelectionBehavior(QAbstractItemView::SelectRows);
  _sessionManagerGridLayout->addWidget(&_sessionManagerTable, 0, 0, 2, 2);

  _passwordEdit  = new QLineEdit();
  _passwordLabel = new QLabel();

  _passwordLabel->setText("Пароль:");

  // Создание элментов управления
  _addSession       = new QPushButton("Добавить");
  _addSession->setIcon(QIcon(":/sessionmanager/img/add.png"));
  _addSession->setFixedHeight(30);

  _deleteSession    = new QPushButton("Удалить");
  _deleteSession->setIcon(QIcon(":/sessionmanager/img/del.png"));
  _deleteSession->setFixedHeight(30);

  _infoSession    = new QPushButton("Информация");
//  _infoSession->setIcon(QIcon(":/sessionmanager/img/del.png"));
  _infoSession->setFixedHeight(30);

  _connectToSession = new QPushButton("Соединиться");
  _connectToSession->setIcon(QIcon(":/sessionmanager/img/connect.png"));
  _connectToSession->setFixedHeight(30);


  _sessionManagerTable.setFixedSize(605,400);
  _sessionManagerTable.setColumnWidth(0,150);
  _sessionManagerTable.setColumnWidth(1,150);
  _sessionManagerTable.setColumnWidth(2,150);
  _sessionManagerTable.setColumnWidth(3,150);

  _sessionManagerTable.setSelectionMode(QAbstractItemView::SingleSelection);

  createConnectors();

  // Установка элементов управления
  _sessionManagerControlsVBoxLayout = new QVBoxLayout();
  _sessionManagerControlsGroupBox   = new QGroupBox();

  _sessionManagerControlsVBoxLayout->setAlignment(Qt::AlignTop);
  _sessionManagerControlsVBoxLayout->addWidget(_connectToSession);
  _sessionManagerControlsVBoxLayout->addWidget(_addSession);
  _sessionManagerControlsVBoxLayout->addWidget(_deleteSession);
  _sessionManagerControlsVBoxLayout->addWidget(_infoSession);


   _passwordEdit->setEchoMode(QLineEdit::Password);
  _sessionManagerControlsVBoxLayout->addWidget(_passwordLabel);
  _sessionManagerControlsVBoxLayout->addWidget(_passwordEdit);

  _sessionManagerControlsGroupBox->setLayout( _sessionManagerControlsVBoxLayout );
  _sessionManagerControlsGroupBox->setAlignment( Qt::AlignTop );
  _sessionManagerGridLayout->addWidget( _sessionManagerControlsGroupBox, 0, 2 );

  setLayout( _sessionManagerGridLayout );

  setWindowFlags(Qt::Dialog);
  setWindowTitle("Выберите сессию работы ...");
  setWindowIcon(QIcon(":/sessionmanager/img/sessionmanager.png"));

}


/*
 * Создание коннекторов
 */
void SessionsTable::createConnectors()
{
  connect( _addSession, SIGNAL(clicked()),
            this, SLOT(addSession()) );

  connect( _deleteSession, SIGNAL(clicked()),
            this, SLOT(deleteSession()) );

  connect( _infoSession, SIGNAL(clicked()),
            this, SLOT(infoSession()) );

  connect( _connectToSession, SIGNAL(clicked()),
           this, SLOT(accept()) );

  connect(&_dlg, SIGNAL(insertNewSession(QString,QString,QString,QString)),
          this, SLOT(insertNewSession(QString,QString,QString,QString)));

  connect( _passwordEdit, SIGNAL(textChanged(const QString &)),
           this, SLOT(passwordInputSlot(const QString &)) );
}

/*
 * Деструктор
 */
SessionsTable::~SessionsTable() {
//   if (_sessionManagerGridLayout!=NULL) {
//     delete _sessionManagerGridLayout;
//   }
//   if (_sessionManagerControlsVBoxLayout!=NULL) {
//     delete _sessionManagerControlsVBoxLayout;
//   }
//   if (_sessionManagerControlsGroupBox!=NULL) {
//     delete _sessionManagerControlsGroupBox;
//   }
 }


/*
 * Обработчик удаления сессии
 */
void SessionsTable::deleteSession() {
  messageLibrary msg;
  QModelIndex    index, tmpindex;
  QString        name, tmpname;
  SysLibrary::UtilsLibrary utils;

  if (_passwordEdit->text() == password) {

    int ret = msg.createWarnDialog("Удаление сессий...",
                         "Вы действительно хотите удалить сессию?");

    switch (ret) {
      case (QMessageBox::Yes):

      // Получение модельного индекса первой ячейки строки с выделенной ячейкой
      tmpindex = _model->index(
            _sessionManagerTable.currentIndex().row(), SESSION_NAME /* Колонка с именем сессии */
           );

       name = tmpindex.data().toString();

       tmpname = QString("%1/%2/%3").arg(QDir::currentPath()).arg("sessions").arg(name);

      // Если каталог не существовал, то удаляем его...
      if (!utils.deleteFolder(tmpname)) {
        qDebug() << "err: boot: can not delete session folder!";
      }

         index = _sessionManagerTable.currentIndex();
        _model->removeRow(index.row());
        if (!_model->submitAll()) {
          qDebug() << "err: boot: delete error " << _model->lastError();
        }

        break;
      case (QMessageBox::Cancel):
          // Отмена
        break;
      default:
          // Что-то другое
        break;
    }
  }
  else {
    messageLibrary msg;
    msg.createWarnMessage("Предупреждение","Пароль задан неверно!");
  }
}


/*
 *  Обработчик подключения к сессии
 */
bool SessionsTable::connectToSession() {

  SysLibrary::UtilsLibrary utils;
  QString      name, right;
  QModelIndex  index;

  // Получение модельного индекса первой ячейки строки с выделенной ячейкой
  index = _model->index(
        _sessionManagerTable.currentIndex().row(), RIGHTS /* Колонка с правами */
       );

  right = index.data().toString();

  if (((_passwordEdit->text() == password)&&(right==Developer))||((right==Operator))) {

    // Получение модельного индекса первой ячейки строки с выделенной ячейкой
     index = _model->index(
          _sessionManagerTable.currentIndex().row(), SESSION_NAME /* Колонка с именем сессии */
         );

     name = index.data().toString();

    // Если каталог не существовал, то создаем его...
    if ( !utils.checkFolder(
           QString("%1\\%2\\%3")
           .arg(QDir::currentPath() )
           .arg("sessions")
           .arg(name)) ) {
      // Ничего не делаем
    }

   return true;
  }
  else {
    messageLibrary msg;
    msg.createWarnMessage("Предупреждение","Пароль задан неверно! "
                                           "Не достаточно прав на открытие сессии.");

    return false;
  }

  return false;
}


/*
 *  Обработчик добавления сессии
 */
void SessionsTable::addSession()
{
  if (_passwordEdit->text() == password) {
    _dlg.execute();
  }
  else {
    messageLibrary msg;
    msg.createWarnMessage("Предупреждение","Пароль задан неверно!");
  }
}

/*
 *  Обработчик получения информации о сессии
 */
void SessionsTable::infoSession()
{
  // Получение модельного индекса выделенной ячейки
  int row = table().currentIndex().row();
  _infoDialog.setInformation(model()->index(row, OTHER).data().toString());
  _infoDialog.exec();
}

/*
 * Установка модели в представление таблицы сессий
 */
void SessionsTable::setModelToView() {
  fillTableHeaderHash();

  QSqlDatabase &db = MySQLDataBaseApi::instance().getDescriptor("cve_base", "session_manager");
  db.close();
  db.setDatabaseName("cve_base");
  db.open();

  _model = new QSqlTableModel(this, db);

  _model->setTable("sessions");

//  _model->removeColumn(0);
  _model->select();

  // Установка заголовка
  _model->setHeaderData(SESSION_NAME,  Qt::Horizontal,  tableHeader[SESSION_NAME]);
  _model->setHeaderData(PRODUCT_TYPE,  Qt::Horizontal,  tableHeader[PRODUCT_TYPE]);
  _model->setHeaderData(RIGHTS,        Qt::Horizontal,  tableHeader[RIGHTS]);
  _model->setHeaderData(SERIAL_NUMBER, Qt::Horizontal,  tableHeader[SERIAL_NUMBER]);

  // Установка модели в представление
  _sessionManagerTable.setModel(_model);
  // Переопределение размера согласно контенту  таблицы
  _sessionManagerTable.resizeColumnsToContents();
  // Установка триггеров
  _sessionManagerTable.setEditTriggers(QAbstractItemView::DoubleClicked |
                                       QAbstractItemView::EditKeyPressed);


  // Пожелание Оли, скрыть первую колонку
  _sessionManagerTable.setColumnHidden(SESSION_ID, true);

  // Скрываем доп. инфу
  _sessionManagerTable.setColumnHidden(OTHER, true);

  // Пожелание Влада и Евгения, сделать выделенной первую строку
  _sessionManagerTable.selectRow(0);
}

/*
 * Добавление новой сессии
 */
void SessionsTable::insertNewSession(QString name, QString product, QString right, QString serial)
{
  if (_passwordEdit->text() == password) {
    _model->insertRows(0,1);
    _model->setData(_model->index(0,SESSION_NAME),  name);
    _model->setData(_model->index(0,PRODUCT_TYPE),  product);
    _model->setData(_model->index(0,RIGHTS),        right);
    _model->setData(_model->index(0,SERIAL_NUMBER), serial);

    if (!_model->submitAll()) {
      qDebug() << "err: boot: insertion error " << _model->lastError();
    }
  }
  else {
    messageLibrary msg;
    msg.createWarnMessage("Предупреждение","Пароль задан неверно!");
  }
}

/*
 * Ввод пароля
 */
void SessionsTable::passwordInputSlot(const QString &)
{
  if (_passwordEdit->text() == password) {
    _model->setEditStrategy(QSqlTableModel::OnFieldChange);
  }
  else {
    if (_model != NULL) {
      _model->setEditStrategy(QSqlTableModel::OnManualSubmit);
      _model->revertAll();
    }
  }
}



