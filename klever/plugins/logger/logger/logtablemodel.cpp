#include "logtablemodel.h"
#include <frameWork/base.h>
/*******************************************************************************
 *                          Реализация модели данных
 *******************************************************************************/

/*
 * Конструктор модули данных
 */
LogTableModel::LogTableModel( QObject *parent ) :
    QAbstractTableModel(parent) {

  // Инициализация внутренних переменных
  _filterFlags          = NO_MESSAGE_FILTRING;
  _isOnDataTimeFilterFlag  = false;
  _isParamChanged          = false;
  _messagesCount           = 0;
  _openReportState         = false;
  _filtrReportState        = false;

  // Создание действий
  createActions();
  // Создание соединений
  createConnections();
}


/*
 * Создание соединений
 */
void LogTableModel::createConnections() {

  QObject::connect( _openReportAct, SIGNAL( triggered() ),
                    this, SLOT( openReport() ) );

  QObject::connect( _deleteAllMessageAct, SIGNAL( triggered() ),
                    this, SLOT( clearReport() ) );

// TODO: Проверить на факт необходимости данных соединений
//  QObject::connect( _infoMessageFilterAct, SIGNAL( triggered() ),
//                    this, SLOT( filterByInfoMsg() ) );

//  QObject::connect( _warnMessageFilterAct, SIGNAL( triggered() ),
//                    this, SLOT( filterByWarnMsg() ) );

//  QObject::connect( _errMessageFilterAct, SIGNAL(triggered()),
//                    this, SLOT( filterByErrorMsg() ) );

//  QObject::connect( _allMessageFilterAct, SIGNAL( triggered() ),
//                    this, SLOT( filterByAllMsg() ) );

  QObject::connect( _sourceMessageFilterAct, SIGNAL( triggered() ),
                    this, SLOT( filtrReport() ) );
}

/*
 * Создание действий
 */
void LogTableModel::createActions() {
  // Открытие журнала
  _openReportAct = new QAction( tr( "Открыть журнал" ), this );
  // Очистка модели
  _deleteAllMessageAct = new QAction( tr("Очистить протокол"), this );

// TODO: Проверить на факт необходимости данных действий
//  // Разграничитель
//  QAction *separatorAct1 = new QAction( tr( "" ), this);
//  separatorAct1->setSeparator( true );
//  // Фильтрация по информационным сообщениям
//  _infoMessageFilterAct = new QAction( tr( "Оставить только информационные сообщения" ),
//                                               this );
//  // Фильтрация по сообщениям предупреждений
//  _warnMessageFilterAct = new QAction( tr( "Оставить только сообщения предупреждений " ),
//                                               this );
//  // Фильтрация по ошибочным сообщениям
//  _errMessageFilterAct = new QAction( tr( "Оставить только сообщения об ошибках" ),
//                                              this );
//  // Вывод всех типов сообщений
//  _allMessageFilterAct = new QAction( tr( "Оставить все типы сообщений" ),
//                                              this );
//  // Разграничитель
//  QAction *separatorAct0 = new QAction( tr( "" ), this);
//  separatorAct0->setSeparator( true );

  // Фильтрация по источнику
  _sourceMessageFilterAct = new QAction( tr( "Фильтровать по источнику" ),
                                                this );

  // Создание списка действий ( будущее PopMenu )
  msgTypeFilterActionsList.append( _openReportAct );
  msgTypeFilterActionsList.append( _deleteAllMessageAct );
//  msgTypeFilterActionsList.append( separatorAct0 );
//  msgTypeFilterActionsList.append( _infoMessageFilterAct );
//  msgTypeFilterActionsList.append( _warnMessageFilterAct );
//  msgTypeFilterActionsList.append( _errMessageFilterAct );
//  msgTypeFilterActionsList.append( _allMessageFilterAct );
//  msgTypeFilterActionsList.append( separatorAct1 );
  msgTypeFilterActionsList.append( _sourceMessageFilterAct );

  _sourceMessageFilterAct->setEnabled( false );
}

/*
 * Возвращает данные из хранилища
 */
QVariant LogTableModel::data(const QModelIndex &index, int role) const {

  if ( !index.isValid() ) {
    return QVariant();
  }

  if ( !( ( role == Qt::DisplayRole ) ||
          ( role == Qt::DecorationRole ) ||
          ( role == Qt::BackgroundRole ) ) ) {
    return QVariant();
  }

  if ( ( index.row() < 0 ) ||
       ( index.row() >= _filtredMessageBuffer.count() ) ) {
    return QVariant();
  }

  messageStructure log_msg = _filtredMessageBuffer.at( index.row() );

  if ( ( role == Qt::DecorationRole ) && ( index.column() == 1 ) ) {
    QString icon_file;
    switch ( log_msg.type ) {
      case INFORMATION_MESSAGES:
        icon_file = ":/logger/img/info.png";
        break;

      case WARNING_MESSAGES:
        icon_file = ":/logger/img/warn.png";
        break;

      case ERROR_MESSAGES:
        icon_file = ":/logger/img/error.png";
        break;

      default:
        icon_file = ":/logger/img/info.png";
    }
    return QIcon( icon_file );
  }

  if ( role == Qt::DisplayRole ) {
    switch ( index.column() ) {
      case 0:
        return QString::number( index.row() + 1 );
        break;
      case 2:
        return log_msg.dtime.toString( "dd.MM.yyyy hh:mm:ss.zzz" );
        break;
      case 3:
        return log_msg.sourceName;
        break;
      case 4:
        return log_msg.text;
        break;
      default:
        return QVariant();
    }
  }

  if ( role == Qt::BackgroundRole ) {
    switch ( log_msg.type ) {
      case INFORMATION_MESSAGES:
        return QBrush( Qt::white );
      case WARNING_MESSAGES:
        return QBrush( Qt::yellow );
      case ERROR_MESSAGES:
        return QBrush( Qt::red );
      default:
        return QBrush( Qt::gray );
    }
  }

   return QVariant();
}

/*
 * Sets the role data for the item at index to value.
 * \note Проверить на необходимость
 */
bool LogTableModel::setData( const QModelIndex &index,
                             const QVariant &value,
                                   int role ) {

  Q_UNUSED(index);
  Q_UNUSED(value);
  Q_UNUSED(role);

  return false;
}

/*
 * Формирование заголовка таблицы
 */
QVariant LogTableModel::headerData( int section,
                                    Qt::Orientation orientation,
                                    int role) const {
  if ( role != Qt::DisplayRole ) {
    return QVariant();
  }

  if ( orientation == Qt::Horizontal ) {
    QString sectionNames[5] = { tr("№"), tr("Тип"),
                                tr("Время"), tr("Источник"),
                                tr("Текст сообщения") };
    if ( ( section >= 0 ) && ( section < 5 ) ) {
      return sectionNames[ section ];
    }
  }

  return QVariant();
}

/*
 * Получить количество столбцов
 */
int LogTableModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 5; /* TODO: magic number */
}

/*
 * Получить количество строк
 */
int LogTableModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) {
    return 0;
  }
  else {
    return _filtredMessageBuffer.count();
  }
}

/*
 * Возвращает флаги элемента
 */
Qt::ItemFlags LogTableModel::flags( const QModelIndex &index ) const {
  Qt::ItemFlags flags = QAbstractTableModel::flags(index);

  return index.isValid() ? (flags | Qt::ItemIsSelectable):flags;
}

/*
 *
 */
//MESSAGE_TYPES_FILTR_FLAGS LogTableModel::filter_flags() {
//  return _filterFlags;
//}

/*
 * Очистка таблицы
 */
void LogTableModel::clearTable() {
//  if ( _filtredMessageBuffer.count() != 0 ) {
//    beginRemoveRows( QModelIndex(), 0, PAGE_SIZE );
//    _filtredMessageBuffer.clear();
//    endRemoveRows();

    for (; _filtredMessageBuffer.size() > 0;) {
      beginRemoveRows( QModelIndex(), 0, 0 );
      _filtredMessageBuffer.pop_front();
      endRemoveRows();
    }
// }
}

/*
 * Устанавливает флаги фильтра
 */
void LogTableModel::setFilterFlags(MESSAGE_TYPES_FILTR_FLAGS a_filter_flags ) {
  if ( _filterFlags != a_filter_flags ) {
    _filterFlags = a_filter_flags;
  }
}

/*
 * Деструктор модели журнала
 */
LogTableModel::~LogTableModel() {
}

/*
 * Добавить строку сообщения.
 * TODO: _messagesCount - Счетчик сообщений. Добавли для того чтобы модель
 * не перегружалась.
 * Если добавление в обычные журналы происходит без фильтрации, то можно
 * не переписывать буфер в буфер... Надо переделать эту функцию и алгоритм записи.
 */
void LogTableModel::insertRow( messageStructure msg ) {

//  _filtredMessageBuffer.append( msg );

  if ( _messagesCount > PAGE_SIZE ) {
    if ( !_filtredMessageBuffer.isEmpty() ) {
      beginRemoveRows( QModelIndex(), 0, 0 );
      _filtredMessageBuffer.takeFirst();
      endRemoveRows();
      _messagesCount--;
    }
    else {
      qDebug().noquote()  << "[error] logger.cpp in insertRow function!";
    }
  }


  beginInsertRows( QModelIndex(), _filtredMessageBuffer.count(),
                   _filtredMessageBuffer.count() );
  _filtredMessageBuffer.append( msg );
  endInsertRows();

  _messagesCount++;

}

/*
 * Добавление записив список отфильтрованных сообщений
 */
void LogTableModel::insertRowForWatcher( messageStructure msg ) {
  _fullFiltredMessageBuffer.append( msg );
}

/*
 * Начало добавления записи в модель
 * TODO: Не вижу смысла в выделении этого в отдельную функцию.
 * Надо избавится от нее.
 */
void LogTableModel::lock()
{
  beginInsertRows( QModelIndex(), _filtredMessageBuffer.count(),
                   _filtredMessageBuffer.count() );
}

/*
 * Завершение добавления записи в модель
 * TODO: Не вижу смысла в выделении этого в отдельную функцию.
 * Надо избавится от нее.
 */
void LogTableModel::unlock()
{
  endInsertRows();
}

/*
 * Фильтрация по источнику
 */
void LogTableModel::filterBySource( messageStructure msg, bool isWatcher ) {
  /* Если фильтр не содержит имени источника сообщения */
  if ( !_mapSources.contains( msg.sourceName ) ) {
    /* Добавляем его в фильтр и фильтруем сообщение по типу */
    _mapSources.insert( msg.sourceName, true );
    filterByMsgType( msg, isWatcher );
  }
  else {
     /* Иначе если фильтр содержит имя источника  и  смотрим на "чекбокс" */
     /* то есть в зависимости от того true  там или  false (фильтровать или нет) */
    if ( _mapSources.value( msg.sourceName ) ) {
      /* Фильтруем сообщение по типу */
      filterByMsgType( msg, isWatcher  );
    }
  }
}

/*
 * Выдача сигнала изменения данных
 */
//void LogTableModel::dataChangedSignal() {
//  emit dataChanged( QModelIndex(), QModelIndex() );
//}

/*
 * Фильтрация по типу сообщения
 */
void LogTableModel::filterByMsgType( messageStructure msg, bool isWatcher ) {
  if ( _filterFlags.testFlag( NO_MESSAGE_FILTRING ) ) {
    if ( isMsgInFiltredTimeAndDateRange( msg ) ) {
      if (!isWatcher) {
        insertRow( msg );
      }
      else {
        insertRowForWatcher( msg );
      }
    }
  }
  else {
    if ( _filterFlags.testFlag( INFO_MESSAGE_FILTRING ) ) {
      if ( msg.type == INFORMATION_MESSAGES ) {
        if ( isMsgInFiltredTimeAndDateRange( msg ) ) {
          if (!isWatcher) {
            insertRow( msg );
          }
          else {
            insertRowForWatcher( msg );
          }
        }
      }
    }
    if ( _filterFlags.testFlag( WARN_MESSAGE_FILTRING ) ) {
      if ( msg.type == WARNING_MESSAGES ) {
        if ( isMsgInFiltredTimeAndDateRange( msg ) ) {
          if (!isWatcher) {
            insertRow( msg );
          }
          else {
            insertRowForWatcher( msg );
          }
        }
      }
    }
    if ( _filterFlags.testFlag( ERR_MESSAGE_FILTRING ) ) {
      if ( msg.type == ERROR_MESSAGES ) {
        if ( isMsgInFiltredTimeAndDateRange( msg ) ) {
          if (!isWatcher) {
            insertRow( msg );
          }
          else {
            insertRowForWatcher( msg );
          }
        }
      }
    }
  }
}

/*
 * Признак того что сообщение находится в нужном временном диапазоне.
 * Необходим для фильтрации по времени и дате соответственно.
 */
bool LogTableModel::isMsgInFiltredTimeAndDateRange( messageStructure msg ) {
  if ( _isOnDataTimeFilterFlag ) {
    QDateTime dtime = msg.dtime;
    if ( ( dtime <= _dtimeStop) && (dtime >= _dtimeStart) ) {
      return true;
    }
    return false;
  }
    else {
    return true;
  }
}

/*
 * Открытие диалогового окна фильтрации данных
 */
void LogTableModel::filtrReport() {

  CustomFilterDialog dlgSrcFilter;
  QPushButton  cancelButton;
  QLabel       loadingProcessLabel;
  QGridLayout  openReportDialogLayout;
  QProgressBar loadingProcessBar;

  _filtrReportProcessDialog = new QDialog();

  if ( _isParamChanged ) {
    dlgSrcFilter.startDatePointLineEdit->setDateTime( _dtimeStart );
    dlgSrcFilter.stopDatePointLineEdit->setDateTime( _dtimeStop );
    dlgSrcFilter.msgTypeComboBox->setCurrentIndex( _msgType );
    dlgSrcFilter.byDateFilterEnableCheckBox->setChecked( _isOnDataTimeFilterFlag );

    _isParamChanged = false;
  }

  QObject::connect( dlgSrcFilter.msgTypeComboBox,
                    SIGNAL( currentIndexChanged(QString) ),
                    this,
                    SLOT( onChanged_msgTypeComboBox(QString) ) );

  /* Если нажал на кнопку Ок (то есть фильтровать) */
  if ( dlgSrcFilter.setSourcesMap( &_mapSources ) ) {
    clearTable();

    if ( !_isParamChanged ) {
      _dtimeStart = dlgSrcFilter.startDatePointLineEdit->dateTime();
      _dtimeStop  = dlgSrcFilter.stopDatePointLineEdit->dateTime();

      if ( dlgSrcFilter.msgTypeComboBox->currentText() == "[info]" ) {
        _msgType = INFORMATION_MESSAGES;
      }
      else if ( dlgSrcFilter.msgTypeComboBox->currentText() == "[error]" ) {
        _msgType = ERROR_MESSAGES;
      }
      else if ( dlgSrcFilter.msgTypeComboBox->currentText() == "[warning]" ) {
        _msgType = WARNING_MESSAGES;
      }
      else {
        _msgType = ALL_MESSAGES;
      }
      _isParamChanged = true;

      _isOnDataTimeFilterFlag = dlgSrcFilter.byDateFilterEnableCheckBox->isChecked();
    }

    cancelButton.setText( "Отмена" );
    loadingProcessLabel.setText( "Процесс фильтрации журнала:" );

    loadingProcessBar.setValue(1);
    loadingProcessBar.setMaximum(0);


    _filtrReportState = true;
    /* Установка флагов для диалогового окна */
    _filtrReportProcessDialog->setWindowFlags( Qt::Window
                        | Qt::MSWindowsFixedSizeDialogHint
                        | Qt::WindowCloseButtonHint);

    _filtrReportProcessDialog->setWindowTitle( tr( "Фильтрация сообщений журнала..." ) );

    QObject::connect( &cancelButton, SIGNAL( clicked() ),
                      _filtrReportProcessDialog, SLOT( reject() ) );

    QObject::connect( this, SIGNAL( filtrReportByQtConcurrentFinished() ),
                      _filtrReportProcessDialog, SLOT( accept() ) );

    openReportDialogLayout.addWidget( &loadingProcessLabel );
    openReportDialogLayout.addWidget( &loadingProcessBar );
    openReportDialogLayout.addWidget( &cancelButton );

    _filtrReportProcessDialog->setLayout( &openReportDialogLayout );

    /* Запуск потока загрузки файла */
    QFuture<void> future;
    future = QtConcurrent::run( this,
                                &LogTableModel::filtrReportByQtConcurrent );

    int res = _filtrReportProcessDialog->exec();
    if ( res == QDialog::Rejected ) {
      _filtrReportState = false;
    }
    else if ( res == QDialog::Accepted ) {
    }
  }
}

/*
 *  Фильтрация журнала в потоке
 */
void LogTableModel::filtrReportByQtConcurrent(){

  _fullFiltredMessageBuffer.clear();
  beginRemoveRows(QModelIndex(),0,_filtredMessageBuffer.count());
  _filtredMessageBuffer.clear();
  endRemoveRows();


  /* TODO цикл перенести в отдельный поток*/
    for ( int i = 0; i < _noFiltredMessageBuffer.count(); i++ ) {
      //lock();
      /* Непосредственная фильтрация */
      filterBySource( _noFiltredMessageBuffer.at(i), true );

      if (!_filtrReportState) {
        return;
      }
      //unlock();
    }

  int pages;
  openOnePageOfReport( 1, &pages );
  emit setPageCountsAndCurrentPageSignal(1, pages);
  emit filtrReportByQtConcurrentFinished();
}

/*
 * Обработчик нажатия на вспылающий список типов сообщений
 */
void LogTableModel::onChanged_msgTypeComboBox( QString type ) {
  if ( type == "все" ) {
    setFilterFlags( NO_MESSAGE_FILTRING );
  }
  else if ( type == "[info]" ) {
    setFilterFlags( INFO_MESSAGE_FILTRING );
  }
  else if ( type == "[warning]" ) {
    setFilterFlags( WARN_MESSAGE_FILTRING );
  }
  else if ( type == "[error]" ) {
    setFilterFlags( ERR_MESSAGE_FILTRING );
  }
  else {
    qDebug().noquote() << "Error: Unknown message type";
  }
}

/*
 * Добавление записи в журнал
 * TODO: Зачем эта функция? Почему сразу не использовать добавление?
 */
void LogTableModel::addMessage( messageStructure msg ) {
  _noFiltredMessageBuffer.append( msg );
}

/*
 * Очистка журнала из памяти и представления
 */
void LogTableModel::clearReport() {
  if ( !_filtredMessageBuffer.isEmpty() ) {
    QMessageBox msgBox;
    msgBox.setText( "Очистка журнала сообщений" );
    msgBox.setIcon( QMessageBox::Question );
    msgBox.setInformativeText("Вы действиельно хотите очистить журнал сообщений?");
    msgBox.setStandardButtons( QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton( QMessageBox::Cancel );
    int ret = msgBox.exec();

    switch ( ret ) {
      case QMessageBox::Ok:

      _fullFiltredMessageBuffer.clear();
      _noFiltredMessageBuffer.clear();
       clearTable();
       beginResetModel();

//        beginRemoveRows( QModelIndex(), 0 , PAGE_SIZE );
//        _filtredMessageBuffer.clear();
//        endInsertRows();

        _sourceMessageFilterAct->setEnabled( false );

        break;
      case QMessageBox::Cancel:
          // Cancel was clicked
        break;
      default:
          // should never be reached
        break;
    }
  }
  _messagesCount=0;
}

/*
 * Фильтрация по ошибочным сообщениям
 */
//void LogTableModel::filterByErrorMsg() {
//  setFilterFlags( ERR_MESSAGE_FILTRING );
//  clearTable();
//  for ( int i = 0; i < _noFiltredMessageBuffer.count(); i++ ) {
//    filterBySource( _noFiltredMessageBuffer.at(i), true  );
//  }
//}

/*
 * Фильтрация по сообщениям предупреждения
 */
//void LogTableModel::filterByWarnMsg() {
//  setFilterFlags( WARN_MESSAGE_FILTRING );
//  clearTable();
//  for ( int i = 0; i < _noFiltredMessageBuffer.count(); i++ ) {
//    filterBySource( _noFiltredMessageBuffer.at(i), true  );
//  }
//}

/*
 * Фильтрация по информационным сообщениям
 */
//void LogTableModel::filterByInfoMsg() {
//  setFilterFlags( INFO_MESSAGE_FILTRING );
//  clearTable();
//  for ( int i = 0; i < _noFiltredMessageBuffer.count(); i++ ) {
//    filterBySource( _noFiltredMessageBuffer.at(i), true );
//  }
//}

/*
 * Показать все сообщения
 */
//void LogTableModel::filterByAllMsg() {
//  setFilterFlags( NO_MESSAGE_FILTRING );
//  clearTable();
//  for ( int i = 0; i < _noFiltredMessageBuffer.count(); i++ ) {
//    filterBySource( _noFiltredMessageBuffer.at(i), true );
//  }
//}

/*
 * Открытие журнала
 */
void LogTableModel::openReport() {

  QPushButton  cancelButton;
  QLabel       loadingProcessLabel;
  QGridLayout  openReportDialogLayout;
  QProgressBar loadingProcessBar;


//  // Проверяем включен ли модуль. Чтение настроек.
//  MainSetupApi  mainsetup;
//  // Проверка наличия пе
//  mainsetup.checkMainParam(QString("Variables"), QString("/sessionPath"), QString(""));
//  QString sessionPath = mainsetup.getMainParam(QString("Variables"), QString("/sessionPath"));

  QString sessionPath = Core::Base::instance().getParameterValue(QString("/sessionPath"), QString(""));

  _openReportProcessDialog = new QDialog();

  cancelButton.setText( "Отмена" );
  loadingProcessLabel.setText( "Процесс загрузки журнала:" );

  loadingProcessBar.setValue(1);
  loadingProcessBar.setMaximum(0);

  /* Открытие диалогового окна */
  QString fileName;
  fileName.clear();


  fileName = QFileDialog::getOpenFileName( NULL,
                              tr("Open report"),
                              QString( "%1\\%2" )
                              .arg( sessionPath )
                              .arg( "logs" ) ,
                              tr("Log Files (*.log )"),
                              NULL,
                              QFileDialog::DontUseNativeDialog );

  if ( fileName.isNull() ) {
    delete _openReportProcessDialog;
    return;
  }


  /* Запуск потока загрузки файла */
  QFuture<void> future;
  future = QtConcurrent::run( this,
                              &LogTableModel::openReportByQtConcurrent,
                              fileName);

  _openReportState = true;
//  while (!future.isFinished()) {
//    QApplication::processEvents();
//  }

  /* Установка флагов для диалогового окна */
  _openReportProcessDialog->setWindowFlags( Qt::Window
                      | Qt::MSWindowsFixedSizeDialogHint
                      | Qt::WindowCloseButtonHint);

  _openReportProcessDialog->setWindowTitle( tr( "Открытие журнала..." ) );

  QObject::connect( &cancelButton, SIGNAL( clicked() ),
                    _openReportProcessDialog, SLOT( reject() ) );

  QObject::connect( this, SIGNAL( openReportByQtConcurrentFinished() ),
                    _openReportProcessDialog, SLOT( accept() ) );

  openReportDialogLayout.addWidget( &loadingProcessLabel );
  openReportDialogLayout.addWidget( &loadingProcessBar );
  openReportDialogLayout.addWidget( &cancelButton );

  _openReportProcessDialog->setLayout( &openReportDialogLayout );

  int res = _openReportProcessDialog->exec();
  if ( res == QDialog::Rejected ) {
    _openReportState = false;
  }
  else if ( res == QDialog::Accepted ) {
    _sourceMessageFilterAct->setEnabled( true );
  }

  /*
   * FIXME: необъяснимый баг. При вызове этого крешится на строчке
   * QString fileName;
   */
//  delete _openReportProcessDialog;
}

/*
 * Продолжение открытия журнала в потоке
 */
void LogTableModel::openReportByQtConcurrent(QString fileName) {

  messageStructure msg;

  _noFiltredMessageBuffer.clear();

  clearTable();
//  _filtredMessageBuffer.clear();

  _fullFiltredMessageBuffer.clear();

  /* Открытие файла grmon.conf */
  QFile data( fileName );
  if ( !data.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
    return;
  }

  /* Открытие файла grmon.conf как текстового потока */
  QTextStream in( &data );
  QString     dat;
  do {
    dat = in.readLine();
    if  ( ( !dat.isEmpty() ) && ( !dat.isNull() ) ) {
      QStringList datl= dat.split( "';", QString::SkipEmptyParts );

      if (dat.size()>=4) {
        msg.dtime       = QDateTime::fromString(
                          datl.at(0).mid( 1, datl.at(0).size() - 1 ),
                          "dd.MM.yyyy hh:mm:ss.zzz" ); // дата

        if ( datl.at(1).mid( 1, datl.at(1).size() - 1 ) == "[Warning]" ) {
          msg.type = WARNING_MESSAGES; // тип сообщения
        }
        else if ( datl.at(1).mid( 1, datl.at(1).size() - 1 ) == "[Error]" ) {
          msg.type = ERROR_MESSAGES; // тип сообщения
        }
        else if ( datl.at(1).mid( 1, datl.at(1).size() - 1 ) == "[Information]" ) {
          msg.type = INFORMATION_MESSAGES; // тип сообщения
        }

        msg.sourceName  = datl.at(2).mid( 1, datl.at(2).size() - 1 ); // источник сообщения
        msg.text        = datl.at(3).mid( 1, datl.at(3).size() - 1 ); // сообщение

        _noFiltredMessageBuffer.append( msg );

        /*Если отменили загрузку*/
        if (!_openReportState) {
          return;
        }
      }

    }
  } while ( !dat.isNull() );

  data.close();

  for ( int i = 0; i < _noFiltredMessageBuffer.count(); i++ ) {
    /* Непосредственная фильтрация */
    filterBySource( _noFiltredMessageBuffer.at(i), true );
    /*Если отменили загрузку*/
    if (!_openReportState) {
      return;
    }
  }

//  if ( _sourceMessageFilterAct != NULL ) {
//    _sourceMessageFilterAct->metaObject()->invokeMethod(_sourceMessageFilterAct,
//                                                        "setEnabled",
//                                                        Q_ARG( bool, true ));

//    _sourceMessageFilterAct->setEnabled( true );
//  }

  int pages;

  openOnePageOfReport( 1, &pages );

  emit setPageCountsAndCurrentPageSignal(1, pages);
  emit openReportByQtConcurrentFinished();
}

/*
 * Открытие одной страницы журнала и вывод ее в представление просмотрщика
 */
int LogTableModel::openOnePageOfReport( int pageIndex, int *pages ) {

  int pageCounts = 0;

  pageCounts = ( _fullFiltredMessageBuffer.size() / PAGE_SIZE );

  if ( ( _fullFiltredMessageBuffer.size() % PAGE_SIZE ) > 0 ) {
    pageCounts++;
  }

  *pages = pageCounts;

    if ( ( pageIndex > 0 ) && ( pageIndex <= pageCounts ) ) {
      ;;
    }
    else {
      if ( pageIndex > pageCounts ) {
        return pageCounts;
      }
      else {
        /* Самой крайней страницей с начала может быть только 1 */
        return 1;/* TODO magic */
      }
    }

  for (; _filtredMessageBuffer.size() > 0;) {
    beginRemoveRows( QModelIndex(), 0, 0 );
    _filtredMessageBuffer.pop_front();
    endRemoveRows();
  }

//  beginInsertRows( QModelIndex(), 0, PAGE_SIZE );
  for ( int i = pageIndex*PAGE_SIZE-PAGE_SIZE ; i < pageIndex*PAGE_SIZE; i++ ) {
    if ( _fullFiltredMessageBuffer.size() > i ) {
        //lock();
        beginInsertRows( QModelIndex(), i+1, i+1 );
      _filtredMessageBuffer.append( _fullFiltredMessageBuffer.at(i) );
        endInsertRows();
        //unlock();
    }
  }

//  endInsertRows();

  return pageIndex;
}


