//---------------------------------------------------------------------------

#ifndef _at_ftdi_moduleH
#define _at_ftdi_moduleH

#include "drv_uart/ftd2xx.h"
#include <QtGui>

enum {
  FT_INDEX_BAUD_300 = 0,
  FT_INDEX_BAUD_600,
  FT_INDEX_BAUD_1200,
  FT_INDEX_BAUD_2400,
  FT_INDEX_BAUD_4800,
  FT_INDEX_BAUD_9600,
  FT_INDEX_BAUD_14400,
  FT_INDEX_BAUD_19200,
  FT_INDEX_BAUD_38400,
  FT_INDEX_BAUD_57600,
  FT_INDEX_BAUD_115200,
  FT_INDEX_BAUD_230400,
  FT_INDEX_BAUD_460800,
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

/* ========================================================================== */
/*                            Class FTDI API                                  */
/* ========================================================================== */

class FtdiDevices {
public:

  FtdiDevices();
  ~FtdiDevices();

  int       state;
  FT_HANDLE handle;
  QString   devSerialNumber;
  int       rxTimeout;
  int       txTimeout;
  int       baudrate;

  int   open(QString devSerialNumber);
  int   setTimeouts(int timeout_rx, int timeout_tx);
  int   close(FT_HANDLE handle);
  bool  reset();
  bool  setSpeed(ULONG BaudRate);
  bool  getDevList();
  int   write(char *data, DWORD data_size);
  int   read(unsigned char *data, DWORD data_size, unsigned int *read_cnt);
  bool  setDataCharacteristics();
  bool  setFlowControl();
  bool  setChars();
  bool  getModemStatus();
  void  setEventNotification();
  void  setDtrRts();
  void  purge();
};


/* ========================================================================== */
/*                           UART specific Class FTDI API                     */
/* ========================================================================== */

class UartDevice: public FtdiDevices{
  public:
    UartDevice(QString devSerialNumber);
    ~UartDevice();
};


#endif
