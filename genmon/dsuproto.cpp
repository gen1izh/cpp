#include "dsuproto.h"
#include "initilizerappdata.h"
#include "dsuregisterfile.h"
/**
 *  Инициализация протокола
 */
dsuProto::dsuProto() {
  state = IDLE_STATE;
}

/**
 *  Запись данных через протокол DSU
 */
void dsuProto::writeDSUDataCmd(unsigned int addr, unsigned char *data, unsigned char len) {

  unsigned char msg[100]; /* 1 байт управляющий, 4 байта адрес,
                             2^6=64 байт данных. То есть с запасом 100 байт. */

  for ( int i = 0; i < 100; i++ ) msg[i] = 0;

  msg[0] = 0xC0;  // Тип команды ( запись данных )

  msg[0] =( msg[0] | (0x3F & len) ); // Установили длину (управляющий байт)

  // Установка значения адреса
  msg[4] = ( 0xFF & addr );
  msg[3] = ( 0xFF00 & addr )      >> 8;
  msg[2] = ( 0xFF0000 & addr )    >> 16;
  msg[1] = ( 0xFF000000 & addr )  >> 24;

  for ( int i = 0; i < len; i++ ) {
    msg[5+i] = data[i];
  }

  /* Отправка пакета */
  ftdiPort.writeData( (char *)&msg[0],  5 + len );

  tmpLen = 1;
  state = READ_CMD_STATE; // Установка состояния  потока

}

/**
 *  Чтение данных через протокол DSU
 */
void dsuProto::readDSUDataCmd(unsigned int addr, unsigned char len) {
  unsigned char msg[100]; /* 1 байт управляющий, 4 байта адрес,
                             2^6=64 байт данных. То есть с запасом 100 байт. */

  for ( int i = 0; i < 100; i++ ) msg[i] = 0;

  msg[0] = 0x80;  // Тип команды ( запись данных )

  msg[0] =( msg[0] | (0x3F & len) ); // Установили длину (управляющий байт)

  // Установка значения адреса
  msg[4] = ( 0xFF & addr );
  msg[3] = ( 0xFF00 & addr )      >> 8;
  msg[2] = ( 0xFF0000 & addr )    >> 16;
  msg[1] = ( 0xFF000000 & addr )  >> 24;

  tmpLen = len;

  /* Отправка пакета */
  ftdiPort.writeData( (char *)&msg[0], 5 /* 1 байт преамбула, 4 байта - адрес */ );

  state = READ_CMD_STATE; // Установка состояния  потока
}

/**
  * Ожидание ответа
  */
void dsuProto::waitAnswer() {

  unsigned int  rcnt = 0;

  ftdiPort.readData( &respData[100], tmpLen, &rcnt );

  /* Проверка наличия ответного пакета */
  if ( rcnt == 0 ) {
    appLogger.sendDataToViewer( appLogger.WARNING_MSG_TYPE, QString(" Может быть DSUC.lr = 0 " ), appLogger.SYSTEM_LOGGER );
  }
  else {
    /* Запись в лог сообщения */
     appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
           QString(" hresp = %1 dmode = %2" ).arg(
             (respData[rcnt]&0x3),
            ((respData[rcnt]&0x4)>>2)) , appLogger.SYSTEM_LOGGER );
  }

  for ( unsigned int i = 0; i < rcnt; i++ ) {
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, QString(" i = %1 data = %2" ).arg( i, respData[rcnt] ), appLogger.SYSTEM_LOGGER );
  }

  state = IDLE_STATE; // Установка состояния  потока
}

/**
  * Тело потока
  */
void dsuProto::run() {

  while (1) {

    switch ( state ) {

      case IDLE_STATE:
      /* Ожидание */
        msleep(10);
        break;

      case READ_CMD_STATE:
        msleep(100);
        waitAnswer();
        break;

      default:
      /* Запись в лог сообщения */
        appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE, " Неизвестное состояние потока протокола DSU " , appLogger.SYSTEM_LOGGER );
        break;
    }

  }
}


/*******************************************************************************
 *                     Основные функции работы протокола
 ******************************************************************************/

/**
  * Чтение из памяти
  */
 char *dsuProto::mem( unsigned int addr, unsigned int len ) {

  char tdata[4];
  tdata[0] = (char)(0xff & addr);
  tdata[1] = (char)((0xff00 & addr)>>8);
  tdata[2] = (char)((0xff0000 & addr)>>16);
  tdata[3] = (char)((0xff000000 & addr)>>24);

  readDSUDataCmd( addr, len );

  return ((char *)&respData[0]);
}

/**
  * Загрузка образа
  */
void dsuProto::eeload( unsigned int addr, char* filename ) {

}

/**
  * Запись в память
  */
void dsuProto::wmem( unsigned int addr, unsigned int data ) {
  char tdata[4];
  tdata[3] = (char)(0xff & data);
  tdata[2] = (char)((0xff00 & data)>>8);
  tdata[1] = (char)((0xff0000 & data)>>16);
  tdata[0] = (char)((0xff000000 & data)>>24);

  writeDSUDataCmd( addr,(unsigned char *)&tdata, 4 );
}

/**
  * Запуск образа
  */
void dsuProto::runimage( unsigned int addr ) {

}
