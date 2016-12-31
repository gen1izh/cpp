#include "logger.h"

/* Глобальные данные */
#include <library/setupApi/app.h>

/*******************************************************************************
 *                Реализация основного класса журналирования
 *******************************************************************************/

/*
 * Конструктор класса
 */
Logger::Logger( QObject         *parent,
                ILoggerStorage  *dataStorage,
                QString logPath,
                bool hasFilter,
                bool isEditable,
                bool isLoggerEnabled ) :
  QObject(parent) {

  // Включение журнала
  _isLoggerEnabled = isLoggerEnabled;

  // Признак необходимости фильтрации сообщений, до записи в буфер сообщений.
  _hasFilterFlag = hasFilter;

  // Флаг включения возможности фильтрации
  _isEditableFlag = isEditable;

  // Получение источника
  ds = dataStorage;

  // Открытие файла
  if ( ( ds != NULL ) && ( _isLoggerEnabled ) ) {
    ds->openSession( logPath );
  }

  // Инициализация представления данных журнала
  logViewer = new QTableView();
  // Инициализация модели данных журнала
  logTableModel = new LogTableModel( this );
  // Включение сортировки данных
  logViewer->setSortingEnabled( true );
  logViewer->sortByColumn(1, Qt::AscendingOrder);
  // Установка источника модели для представления данных
  logViewer->setModel( logTableModel );
  // Установка дополнительных параметров представления
  logViewer->verticalHeader()->setDefaultSectionSize( 16 );
  logViewer->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
  logViewer->horizontalHeader()->setStretchLastSection( true );
  logViewer->setContextMenuPolicy( Qt::CustomContextMenu );
  logViewer->setWindowIcon( QIcon( ":/logger/img/logwatcher.png" ) );

  QObject::connect( logViewer,
                    SIGNAL( customContextMenuRequested( QPoint ) ),
                    this,
                    SLOT( onContextMenuRequest( QPoint ) ) );

  // Установка связи сигнала изменения данных в модели и слота onDataChanged
  QObject::connect( logTableModel,
                    SIGNAL( dataChanged( QModelIndex, QModelIndex ) ),
                    this,
                    SLOT( onDataChanged( QModelIndex, QModelIndex ) ) );
}

/*
 * Деструктор класса
 */
Logger::~Logger() {
  // Открытие файла
  if ( ds != NULL ) {
    ds->closeSession();
    delete ds;
  }
}

/*
 * Открытие контекстного меню
 */
void Logger::onContextMenuRequest( QPoint point ) {
  if ( _isEditableFlag ) {
    QMenu menu;
    menu.exec( logTableModel->msgTypeFilterActionsList, logViewer->mapToGlobal( point ) );
  }
}

/*
 * Прокрутка журнал до последнего вниз сообщения при добавлении сообщения
 */
void Logger::onDataChanged( QModelIndex , QModelIndex ) {
  // logViewer->scrollToBottom();
  //  logViewer->scrollToBottom();
//  QMetaObject::invokeMethod(logViewer, "scrollToBottom", Qt::QueuedConnection );
}

/*
 * Добавление сообщения в журнал
 */
void Logger::logMessage( QObject *sender, QString text, MESSAGE_TYPES type ) {

  if ( _isLoggerEnabled ) {
    messageStructure logMsgStructureItem;

    /* Заблокировать доступ по записи в хранилище сообщений */
    _putIntoStorageOperationMutex.lock();
//    logTableModel->lock();

    /* TODO: чем модуль сценариев от других отличается? */
    if ( sender ) {
      logMsgStructureItem.sourceName = sender->objectName();
    }
    else {
      logMsgStructureItem.sourceName = "Модуль сценариев";
    }

    logMsgStructureItem.dtime = QDateTime::currentDateTime();
    logMsgStructureItem.type = type;
    logMsgStructureItem.text = text;

    logTableModel->addMessage( logMsgStructureItem );

    if ( _hasFilterFlag ) {
      logTableModel->filterBySource( logMsgStructureItem, false );
    }
    else {
      logTableModel->insertRow( logMsgStructureItem );
    }
//    _logTableModel->dataChangedSignal();

    // Запись сообщения в хранилище
    if ( ds != NULL ) {
     ds->push( logMsgStructureItem );
    }

	 //  logViewer->scrollToBottom();
//  QMetaObject::invokeMethod(logViewer, "scrollToBottom", Qt::QueuedConnection );

    /* Разблокировать доступ по записи хранилища сообщений */
//    logTableModel->unlock();
    _putIntoStorageOperationMutex.unlock();
  }
}

/*
 * Добавление ошибочного сообщения в журнал
 */
void Logger::errorMessage( QObject *sender, QString text ) {
  logMessage( sender, text, ERROR_MESSAGES );
}

/*
 * Добавление информационного сообщения в журнал
 */
void Logger::infoMessage( QObject *sender, QString text ) {
  logMessage( sender, text, INFORMATION_MESSAGES );
}

/*
 * Добавление сообщения предупреждения в журнал
 */
void Logger::warnMessage( QObject *sender, QString text ) {
  logMessage( sender, text, WARNING_MESSAGES );
}






