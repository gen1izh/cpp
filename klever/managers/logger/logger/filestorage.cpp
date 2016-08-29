#include "filestorage.h"

/**************************************************************************
 *                 Реализация файлового хранилища данных
 **************************************************************************/

/*
 * Открытие сессии работы с файлом
 */
uint FileStorage::openSession( QString fileName ) {
  // Формирование строки текущей даты и времени
  QString dateTimeString =
                 QDateTime::currentDateTime().toString( "yyyy_MM_dd_hh_mm_ss" );

  // Формирование полного имени до файла журнала
  QString logFileName = fileName + "/log_" + dateTimeString + ".log";

  // Файловый дескриптор
  _logFd = new QFile( logFileName );

  // Проверка на корректность открытия файла
  uint state = 0;
  if ( !_logFd->open( QIODevice::WriteOnly | QIODevice::Text ) ) {
    _logFd->close();
    _logFd = NULL;
    QMessageBox::critical( NULL,
                           QObject::tr(" Внимание "),
                          QObject::tr(" Не удалось создать файл протоколирования ") );
    state = FILE_OPEN_ERROR;
  }
  else {
    state = SUCCESSFUL;
  }

  return state;
}

/*
 * Помещение сообщения в хранилище сообщений
 */
uint FileStorage::push( messageStructure msg ) {
  /* Добавление сообщения в конец протокола */
  if ( _logFd ) {
    QTextStream logOutStream( _logFd );
    QString logMsgStr = messageStructureToString( msg );
    logOutStream << logMsgStr + "\n";
    return SUCCESSFUL;
  }
  else {
    return FILE_DESCRIPTOR_ERROR;
  }
}

/*
 * Вытаскиваем сообщение из хранилища сообщений
 */
messageStructure FileStorage::pop() {
  messageStructure msg;

  /*
   * Нет реализации, так как не нужна в данной версии лога
   * То есть вытаскивать сообщения из csv-файл не требуется
   */
  return msg;
}

/*
 * Преобразование logMsgStructure структуру в CSV формат
 */
QString FileStorage::messageStructureToString( messageStructure st ) {
  QString tmp = "'" + st.dtime.toString("dd.MM.yyyy hh:mm:ss.zzz") + "';";
  QString msgType;

  switch ( st.type ) {
    case INFORMATION_MESSAGES:
      msgType = "'[Information]';";
      break;
    case WARNING_MESSAGES:
      msgType = "'[Warning]';";
      break;
    case ERROR_MESSAGES:
      msgType = "'[Error]';";
      break;
    default:
      msgType = "'[Unknow_msg_type]';";
      break;
  }

  tmp = tmp + msgType + "'" + st.sourceName + "';'" + st.text+ "';";

  return tmp;
}

/*
 * Закрытие сессии работы с хранилищем
 */
uint FileStorage::closeSession() {
  if ( _logFd ) {
    _logFd->close();
    return SUCCESSFUL;
  }
  else {
    return FILE_CLOSE_ERROR;
  }
}

