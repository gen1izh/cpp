#include "dsuproto.h"
#include "initilizerappdata.h"
#include "dsuregisterfile.h"
/**
 *  ������������� ���������
 */
dsuProto::dsuProto() {
  state = IDLE_STATE;
}

/**
 *  ������ ������ ����� �������� DSU
 */
void dsuProto::writeDSUDataCmd(unsigned int addr, unsigned char *data, unsigned char len) {

  unsigned char msg[100]; /* 1 ���� �����������, 4 ����� �����,
                             2^6=64 ���� ������. �� ���� � ������� 100 ����. */

  for ( int i = 0; i < 100; i++ ) msg[i] = 0;

  msg[0] = 0xC0;  // ��� ������� ( ������ ������ )

  msg[0] =( msg[0] | (0x3F & len) ); // ���������� ����� (����������� ����)

  // ��������� �������� ������
  msg[4] = ( 0xFF & addr );
  msg[3] = ( 0xFF00 & addr )      >> 8;
  msg[2] = ( 0xFF0000 & addr )    >> 16;
  msg[1] = ( 0xFF000000 & addr )  >> 24;

  for ( int i = 0; i < len; i++ ) {
    msg[5+i] = data[i];
  }

  /* �������� ������ */
  ftdiPort.writeData( (char *)&msg[0],  5 + len );

  tmpLen = 1;
  state = READ_CMD_STATE; // ��������� ���������  ������

}

/**
 *  ������ ������ ����� �������� DSU
 */
void dsuProto::readDSUDataCmd(unsigned int addr, unsigned char len) {
  unsigned char msg[100]; /* 1 ���� �����������, 4 ����� �����,
                             2^6=64 ���� ������. �� ���� � ������� 100 ����. */

  for ( int i = 0; i < 100; i++ ) msg[i] = 0;

  msg[0] = 0x80;  // ��� ������� ( ������ ������ )

  msg[0] =( msg[0] | (0x3F & len) ); // ���������� ����� (����������� ����)

  // ��������� �������� ������
  msg[4] = ( 0xFF & addr );
  msg[3] = ( 0xFF00 & addr )      >> 8;
  msg[2] = ( 0xFF0000 & addr )    >> 16;
  msg[1] = ( 0xFF000000 & addr )  >> 24;

  tmpLen = len;

  /* �������� ������ */
  ftdiPort.writeData( (char *)&msg[0], 5 /* 1 ���� ���������, 4 ����� - ����� */ );

  state = READ_CMD_STATE; // ��������� ���������  ������
}

/**
  * �������� ������
  */
void dsuProto::waitAnswer() {

  unsigned int  rcnt = 0;

  ftdiPort.readData( &respData[100], tmpLen, &rcnt );

  /* �������� ������� ��������� ������ */
  if ( rcnt == 0 ) {
    appLogger.sendDataToViewer( appLogger.WARNING_MSG_TYPE, QString(" ����� ���� DSUC.lr = 0 " ), appLogger.SYSTEM_LOGGER );
  }
  else {
    /* ������ � ��� ��������� */
     appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE,
           QString(" hresp = %1 dmode = %2" ).arg(
             (respData[rcnt]&0x3),
            ((respData[rcnt]&0x4)>>2)) , appLogger.SYSTEM_LOGGER );
  }

  for ( unsigned int i = 0; i < rcnt; i++ ) {
    appLogger.sendDataToViewer( appLogger.INFO_MSG_TYPE, QString(" i = %1 data = %2" ).arg( i, respData[rcnt] ), appLogger.SYSTEM_LOGGER );
  }

  state = IDLE_STATE; // ��������� ���������  ������
}

/**
  * ���� ������
  */
void dsuProto::run() {

  while (1) {

    switch ( state ) {

      case IDLE_STATE:
      /* �������� */
        msleep(10);
        break;

      case READ_CMD_STATE:
        msleep(100);
        waitAnswer();
        break;

      default:
      /* ������ � ��� ��������� */
        appLogger.sendDataToViewer( appLogger.ERROR_MSG_TYPE, " ����������� ��������� ������ ��������� DSU " , appLogger.SYSTEM_LOGGER );
        break;
    }

  }
}


/*******************************************************************************
 *                     �������� ������� ������ ���������
 ******************************************************************************/

/**
  * ������ �� ������
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
  * �������� ������
  */
void dsuProto::eeload( unsigned int addr, char* filename ) {

}

/**
  * ������ � ������
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
  * ������ ������
  */
void dsuProto::runimage( unsigned int addr ) {

}
