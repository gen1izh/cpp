//---------------------------------------------------------------------------

#ifndef _ftdiModuleH
#define _ftdiModuleH

#include <windows.h>
#define _WINDOWS  // TODO: ��� ������ ������������ � windows.h, �� ������-��...
#include "ftd2xx.h"
#include <QStringList>

/* ========================================================================== */
/*                            Class FTDI API                                  */
/* ========================================================================== */

class FtdiDevices {

  enum {
    FT_INDEX_BAUD_300 = 0,
    FT_INDEX_BAUD_600,    FT_INDEX_BAUD_1200,   FT_INDEX_BAUD_2400,   FT_INDEX_BAUD_4800,
    FT_INDEX_BAUD_9600,   FT_INDEX_BAUD_14400,  FT_INDEX_BAUD_19200,  FT_INDEX_BAUD_38400,
    FT_INDEX_BAUD_57600,  FT_INDEX_BAUD_115200, FT_INDEX_BAUD_230400, FT_INDEX_BAUD_460800,
    FT_INDEX_BAUD_921600,
    FT_INDEX_DATA_BITS_7 = 0,
    FT_INDEX_DATA_BITS_8,
    FT_INDEX_STOP_BITS_1 = 0,
    FT_INDEX_STOP_BITS_2,
    FT_INDEX_PARITY_NONE = 0,
    FT_INDEX_PARITY_ODD,
    FT_INDEX_PARITY_EVEN,
    FT_INDEX_PARITY_MARK,
    FT_INDEX_PARITY_SPACE,
    FT_INDEX_FLOW_NONE = 0,
    FT_INDEX_FLOW_RTS_CTS,
    FT_INDEX_FLOW_DTR_DSR,
    FT_INDEX_FLOW_XON_XOFF
  };

  enum {
    FT_SUCCESSFUL = 0,
    FT_ERROR
  };

  FT_STATUS                 ftStatus;           /* ��������� ���������� �������� ���������� ftdi */
  FT_DEVICE_LIST_INFO_NODE *devInfo;           /* ���������� �� ���������� */
  QStringList               listPorts;          /* ������ ������ */
  FT_HANDLE                 m_ftHandleA ,m_ftHandleB;         /* ����������� ���������� */

  public:

    FtdiDevices();
   // ~FtdiDevices();

    /* ����� ���� ������ */
    QString showPorts( int i, DWORD *numDevs, QString *serialNum  );

    /* �������� ���������� (�������� ��������������) */
    int   openDSUSession();
    /* �������� ���������� (�������� ��������������) */
    int   closeDSUSession();

    int   setTimeouts( int rxTimeout, int txTimeout );
    bool  reset();
    bool  setSpeed( ULONG baudRate );
    bool  getDevList();
    int   writeData( char *data, DWORD size );
    int   readData( char *data, DWORD size, unsigned int *rcnt );
    bool  setDataCharacteristics();
    bool  setFlowControl();
    bool  setChars();
    bool  getModemStatus();
    void  setEventNotification();
    void  setDtrRts();
    void  purge();

    /* ������ �������� ����� B */
    char readFromPortB( bool isNeedLog );
    /* ������ �������� � ���� B */
    void writeToPortB( char data );

    /* ������������� ������ � ������ */
    int Initialization();
};

#endif
