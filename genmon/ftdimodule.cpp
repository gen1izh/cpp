//---------------------------------------------------------------------------
#include "ftdimodule.h"
#include "initilizerappdata.h"
#include <QtGui>

/*******************************************************************************
 *                        Работа с FTDI библиотекой
 ******************************************************************************/

/**
 *  TODO: Необходимо отрефакторить код
 */
bool FtdiDevices::reset() {
  FT_STATUS ftStatus;
  ftStatus = FT_ResetDevice(m_ftHandleA);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}


bool FtdiDevices::getDevList(){
  DWORD devIndex = 0; // первое устройство
  char Buffer[64]; // резервируем место в памяти
  FT_STATUS ftStatus;
  do {
      ftStatus =
          FT_ListDevices((PVOID)devIndex,Buffer,FT_LIST_BY_INDEX|FT_OPEN_BY_SERIAL_NUMBER);
      if (ftStatus == FT_OK) {
          // FT_ListDevices OK, серийный номер сохраняем в буфере
          qDebug()<<"Device = "+QString(Buffer);
        }
      else {
        }
      devIndex++;
    }while (devIndex<100);
  return ftStatus;
}


bool FtdiDevices::setSpeed( ULONG baudRate ) {
  FT_STATUS ftStatus;
  ftStatus = FT_SetBaudRate(m_ftHandleA, baudRate);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

bool FtdiDevices::setDataCharacteristics() {
  UCHAR WordLength;
  UCHAR StopBits;
  FT_STATUS ftStatus;
  WordLength = (UCHAR)(FT_INDEX_DATA_BITS_8 + FT_BITS_7);

  switch(FT_INDEX_STOP_BITS_1) {
  default:
    StopBits = FT_STOP_BITS_1;
    break;
  case 1:
    StopBits = FT_STOP_BITS_2;
    break;
  }

  ftStatus = FT_SetDataCharacteristics(m_ftHandleA, WordLength, StopBits,
    (UCHAR)FT_INDEX_PARITY_NONE);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

bool FtdiDevices::getModemStatus() {
  FT_STATUS ftStatus;
  ULONG Status;
  ftStatus = FT_GetModemStatus(m_ftHandleA, &Status);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

bool FtdiDevices::setFlowControl() {
  USHORT FlowControl;
  UCHAR XonChar;
  UCHAR XoffChar;
  FT_STATUS ftStatus;
  FlowControl = FT_FLOW_NONE;
  XonChar = 0;
  XoffChar = 0;
  switch(FT_INDEX_FLOW_NONE) {
  case 0: // NONE
  default:
    break;
  case 1: // RTS
    FlowControl = FT_FLOW_RTS_CTS;
    break;
  case 2: // DTR
    FlowControl = FT_FLOW_DTR_DSR;
    break;
  case 3: // XON/XOFF
    FlowControl = FT_FLOW_XON_XOFF;
    XonChar = 0x11;
    XoffChar = 0x13;
    break;
  }

  ftStatus = FT_SetFlowControl(m_ftHandleA, FlowControl, XonChar, XoffChar);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

bool FtdiDevices::setChars() {
  FT_STATUS ftStatus;
  ftStatus = FT_SetChars(m_ftHandleA, 0, false ? (UCHAR)1 : (UCHAR)0, 0,
    false ? (UCHAR)1 : (UCHAR)0);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

void FtdiDevices::setEventNotification() {
  FT_SetEventNotification(m_ftHandleA, 0, NULL);
}

 void FtdiDevices::setDtrRts() {
//	 if (true) {
                 FT_SetDtr(m_ftHandleA);
//	 }
//	 else {
//		 FT_ClrDtr(dev.ftHandle);
//	 }

//	 if (true) {
                 FT_SetRts(m_ftHandleA);
//	 }
//	 else {
//		 FT_ClrRts(dev.ftHandle);
//	 }
 }

//void FtdiDevices::SetTimeouts() {
//  FT_SetTimeouts(Handle, FT_DEFAULT_RX_TIMEOUT, FT_DEFAULT_TX_TIMEOUT);
//}

void FtdiDevices::purge() {
  FT_Purge(m_ftHandleA, FT_PURGE_TX | FT_PURGE_RX);
}

/**
 * Открытие устройства
 */
int FtdiDevices::openDSUSession() {
  ftStatus = FT_Open( 0 /* Порт A */, &m_ftHandleA );
  if ( ftStatus != FT_OK ) {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция открытия порта не выполнена! ", appLogger.SYSTEM_LOGGER );
    return false;
  }
  else {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция открытия порта выполнена! ", appLogger.SYSTEM_LOGGER );
    return true;
  }
  return true;
}

/*
 * Установка таймаута
 */
int FtdiDevices::setTimeouts(int rxTimeout, int txTimeout ) {
  FT_STATUS ftStatus;
  ftStatus = FT_SetTimeouts(m_ftHandleA, rxTimeout, txTimeout);
  if (!FT_SUCCESS(ftStatus)) {
      return false;
    }
  return true;
}

/**
 * Закрытие устройства
 */
int FtdiDevices::closeDSUSession() {

  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Закрытие устройства ", appLogger.SYSTEM_LOGGER );

  ftStatus = FT_Close( m_ftHandleA );

  if ( ftStatus != FT_OK ) {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция закрытия порта не выполнена! ", appLogger.SYSTEM_LOGGER );
    return false;
  }
  else {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция закрытия порта выполнена! ", appLogger.SYSTEM_LOGGER );
    return true;
  }
}

/**
 *  Запись данных в устройства
 */
int FtdiDevices::writeData( char *data, DWORD size ) {
  FT_STATUS ftStatus;
  DWORD     BytesTransmited;

  QString msg = QString(" Исполнение операции записи (WRITE)."\
                        " Дескриптор устройства = %1"\
                        " Размер = %2").arg( ( int )m_ftHandleA ).arg( size );

  /* Запись в лог сообщения */
  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, msg, appLogger.SYSTEM_LOGGER );

  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, "Дамп команды: ", appLogger.PROTOCOL_LOGGER );
  QString dump = "";
  for ( unsigned int i = 0; i < size; i++ ) {
    dump += QString(" 0x%1 ").arg( (unsigned char)data[i], 0, 16 );
  }
  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, dump, appLogger.PROTOCOL_LOGGER );

  ftStatus = FT_Write( m_ftHandleA, data, size, &BytesTransmited );
  if ( ftStatus == FT_OK ) {
    if (BytesTransmited == size) {
      /* Запись в лог сообщения */
        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString(" Все данные записаны успешно! "), appLogger.SYSTEM_LOGGER );
      }
    else {
      /* Запись в лог сообщения */
        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString(" Не все данные записаны успешно! "), appLogger.SYSTEM_LOGGER );
        return FT_ERROR;
      }
  }
  else {
    /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString(" Write выполнился с ошибкой! "), appLogger.SYSTEM_LOGGER );
      return FT_ERROR;
  }

  return FT_SUCCESSFUL;
}

/**
 * Обзор всех портов микросхемы ftdi
 */
QString FtdiDevices::showPorts( int i, DWORD *numDevs, QString *serialNum ) {

  /* Запись в лог сообщения */
  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString(" Создание списка устройств "), appLogger.SYSTEM_LOGGER );

  ftStatus = FT_CreateDeviceInfoList( numDevs );

  if ( ftStatus != FT_OK ) {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция создания списка не прошла! ", appLogger.SYSTEM_LOGGER );;
    return "";
  }

  QString msg = QString(" Количество ftdi = %1 ").arg( *numDevs );

  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, msg, appLogger.SYSTEM_LOGGER );

  if ( numDevs > 0 ) {
    devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc( sizeof(FT_DEVICE_LIST_INFO_NODE) * (*numDevs) );
    ftStatus = FT_GetDeviceInfoList( devInfo, numDevs );
    if ( ftStatus == FT_OK ) {
//      for ( DWORD i = 0; i < numDevs; i++ ) {
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," =========================== " );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("Device number \t%1").arg( i,0,10 ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("Flags    \t= 0x%1").arg( (int)devInfo[i].Flags, 0, 16 ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("Type     \t= 0x%1").arg( (int)devInfo[i].Type, 0, 16 ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("ID       \t= 0x%1").arg( (int)devInfo[i].ID, 0, 16 ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("LocId    \t= 0x%1").arg( (int)devInfo[i].LocId, 0, 16 ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("SerialNumber \t=  %1").arg(  devInfo[i].SerialNumber ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("Description  \t=  %1").arg(  devInfo[i].Description ) );
//        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString("ftHandle     \t= 0x%1").arg( (int)devInfo[i].ftHandle, 0, 16 ) );

//      }
    }
  }


  QString deviceInfo;

  deviceInfo = "<table><tr><td> "+ QString("Device number \t%1").arg( i,0,10 )  + " </td></tr>"\
  "<tr><td>" + QString("Flags    \t= 0x%1").arg( (int)devInfo[i].Flags, 0, 16 ) + "</td></tr>"\
  "<tr><td>" + QString("Type     \t= 0x%1").arg( (int)devInfo[i].Type, 0, 16 )  + "</td></tr>"\
  "<tr><td>" + QString("ID       \t= 0x%1").arg( (int)devInfo[i].ID, 0, 16 )    + "</td></tr>"\
  "<tr><td>" + QString("LocId    \t= 0x%1").arg( (int)devInfo[i].LocId, 0, 16 ) + "</td></tr>"\
  "<tr><td>" + QString("SerialNumber \t=  %1").arg(  devInfo[i].SerialNumber)   + "</td></tr>"\
  "<tr><td>" + QString("Description  \t=  %1").arg(  devInfo[i].Description )   + "</td></tr>"\
  "<tr><td>" + QString("ftHandle     \t= 0x%1").arg( (int)devInfo[i].ftHandle, 0, 16 ) + "</td></tr>"\
  "</table>";

  *serialNum = QString("SerialNumber \t=  %1").arg(  devInfo[i].SerialNumber );

  free( devInfo );
  return deviceInfo;
}

/**
 * Запись в порт Б микросхемы ftdi
 */
void FtdiDevices::writeToPortB( char  data ){
  DWORD BytesWritten;

  /* Запись в лог сообщения */
  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, " Исполнение операции записи (WRITE_PORTB) ", appLogger.SYSTEM_LOGGER );

  if ( listPorts.size() > -1 ) {

    ftStatus = FT_Open( 1 /* Порт Б */, &m_ftHandleB );
    if ( ftStatus != FT_OK ) {
      /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция открытия порта не выполнена! ", appLogger.SYSTEM_LOGGER );
    }
    else {
      /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция открытия порта выполнена! ", appLogger.SYSTEM_LOGGER );
    }

    ftStatus = FT_SetBitMode( m_ftHandleB, 0xFE, 0x01 );
    if ( ftStatus == FT_OK ) {
      /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция установки bitbang порта выполнена! ", appLogger.SYSTEM_LOGGER );
    } else {
      /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция установки bitbang порта не выполнена! ", appLogger.SYSTEM_LOGGER );
    }

    ftStatus = FT_Write( m_ftHandleB, &data, 1, &BytesWritten );

    if ( ftStatus != FT_OK ) {
      /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция записи в порт не выполнена! ", appLogger.SYSTEM_LOGGER );;
    }
    else {
      /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция записи в порт выполнена! ", appLogger.SYSTEM_LOGGER );
    }

     FT_Close( m_ftHandleB );
     if ( ftStatus != FT_OK ) {
       /* Запись в лог сообщения */
       appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция закрытия порта не выполнена! ", appLogger.SYSTEM_LOGGER );
     }
     else {
       /* Запись в лог сообщения */
       appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция закрытия порта выполнена! ", appLogger.SYSTEM_LOGGER );
     }
  }
}

/**
 * Чтение значения порта Б микросхемы ftdi
 */
char FtdiDevices::readFromPortB( bool isNeedLog ){
  DWORD BytesRead;
  char  data = 0;

  /* Запись в лог сообщения */
  if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                               " Исполнение операции чтения (READ_PORTB) ",
                                               appLogger.SYSTEM_LOGGER );

  if ( listPorts.size() > -1 ) {

    ftStatus = FT_Open( 1 /* Порт Б */, &m_ftHandleB );
    if ( ftStatus != FT_OK ) {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                   " Операция открытия порта не выполнена! ",
                                                   appLogger.SYSTEM_LOGGER );
    }
    else {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                   " Операция открытия порта выполнена! ",
                                                   appLogger.SYSTEM_LOGGER );
    }

    ftStatus = FT_SetBitMode( m_ftHandleB, 0xFE, 0x01 );
    if ( ftStatus == FT_OK ) {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE," Операция установки bitbang порта выполнена! ", appLogger.SYSTEM_LOGGER );
    } else {
      /* Запись в лог сообщения */
       if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE," Операция установки bitbang порта не выполнена! ", appLogger.SYSTEM_LOGGER );
    }

    ftStatus = FT_SetTimeouts( m_ftHandleB, 100, 100 );
    if ( ftStatus != FT_OK ) {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                   " Операция установки таймаута не выполнена! ",
                                                   appLogger.SYSTEM_LOGGER );
    }
    else {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                   " Операция установки таймаута выполнена! ",
                                                   appLogger.SYSTEM_LOGGER );
    }

    ftStatus = FT_Read( m_ftHandleB, &data, 1, &BytesRead );
    if ( ftStatus != FT_OK ) {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                   " Операция чтения из порта не выполнена! ",
                                                   appLogger.SYSTEM_LOGGER );
    }
    else {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                   " Операция чтения из порта выполнена! ",
                                                   appLogger.SYSTEM_LOGGER );
    }

    ftStatus = FT_Close( m_ftHandleB );
    if ( ftStatus != FT_OK ) {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                  " Операция закрытия порта не выполнена! ",
                                  appLogger.SYSTEM_LOGGER );
    }
    else {
      /* Запись в лог сообщения */
      if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                  " Операция закрытия порта выполнена! ",
                                  appLogger.SYSTEM_LOGGER );
    }
  }

  /* Запись в лог сообщения */
  if ( isNeedLog ) appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                               QString(" Значения порта = %1").arg( data ),
                                               appLogger.SYSTEM_LOGGER );

  return data;
}


/**
 *  Чтение данных с устройства
 */
int FtdiDevices::readData( char *data, DWORD size, unsigned int *rcnt ) {
  FT_STATUS ftStatus;
  DWORD     BytesReceived;

  QString msg = QString(" Исполнение операции чтения (READ)."\
                        " Дескриптор устройства = %1"\
                        " Размер = %2").arg( ( int )m_ftHandleA ).arg( size );

  /* Запись в лог сообщения */
  appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, msg, appLogger.SYSTEM_LOGGER  );

  ftStatus = FT_SetTimeouts( m_ftHandleA, 100, 100 );
  if ( ftStatus != FT_OK ) {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE,
                                                 " Операция установки таймаута не выполнена! ",
                                                 appLogger.SYSTEM_LOGGER );
  }
  else {
    /* Запись в лог сообщения */
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
                                                 " Операция установки таймаута выполнена! ",
                                                 appLogger.SYSTEM_LOGGER );
  }

  ftStatus = FT_Read( m_ftHandleA, data, size, &BytesReceived );

  /* Запись дампа пакета в лог */
  if ( BytesReceived != 0) {
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, "Дамп ответа: ", appLogger.PROTOCOL_LOGGER );
    QString dump = "";
    for ( unsigned int i = 0; i < BytesReceived; i++ ) {
      dump += QString(" 0x%1 ").arg( (unsigned char)data[i], 0, 16 );
    }
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, dump, appLogger.PROTOCOL_LOGGER );
  }
  *rcnt = BytesReceived;

  if ( ftStatus == FT_OK ) {
    if ( BytesReceived == size ) {
      /* Запись в лог сообщения */
        appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,QString(" Все данные получены успешно! "), appLogger.SYSTEM_LOGGER );
      }
    else {
      /* Запись в лог сообщения */
        appLogger.sendDataToViewer( appLogger.WARNING_MSG_TYPE,QString(" Не все данные получены успешно! "), appLogger.SYSTEM_LOGGER );
        return FT_ERROR;
      }
    }
  else {
    /* Запись в лог сообщения */
      appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE, QString(" Read выполнился с ошибкой! "), appLogger.SYSTEM_LOGGER );
      return FT_ERROR;
    }

  return FT_SUCCESSFUL;
}

/**
 * Инициализация ftdi устройств
 */
FtdiDevices::FtdiDevices() {
}

/**
 * Деструктор объекта
 */
//FtdiDevices::~FtdiDevices() {
//}


/**
 * Инициализация COM порта
 */
int FtdiDevices::Initialization() {

  int state = 0;

  if ( !openDSUSession() )          state = 1;
  if ( !reset() )                   state = 1;
  if ( !setSpeed(115200) )          state = 1;
  if ( !setDataCharacteristics() )  state = 1;
  if ( !getModemStatus() )          state = 1;

  setEventNotification();
  setDtrRts();
  purge();

  if ( !setFlowControl() ) state = 1;

  QString msg;
  int type;

  if ( state == 1 ) {
    msg  = "Не могу открыть устройство( COM порт A )!" ;
    type = appLogger.ERROR_MSG_TYPE;
  }
  else {
    msg  = "Устройство открыто успешно( COM порт A )!";
    type = appLogger.INFO_MSG_TYPE;
  }

  /* Запись в лог сообщения */
  appLogger.sendDataToViewer( type, msg, appLogger.SYSTEM_LOGGER );

  return state;
}


