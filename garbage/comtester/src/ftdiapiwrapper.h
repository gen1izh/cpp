// ---------------------------------------------------------------------------

#ifndef ftdiapiwrapperH
#define ftdiapiwrapperH
#include <Classes.hpp>
#include "stdio.h"
#include "ftd2xx.h"


//
//// ---------------------------------------------------------------------------
enum {
	FT_INDEX_BAUD_300 = 0, FT_INDEX_BAUD_600, FT_INDEX_BAUD_1200,
	FT_INDEX_BAUD_2400, FT_INDEX_BAUD_4800, FT_INDEX_BAUD_9600,
	FT_INDEX_BAUD_14400, FT_INDEX_BAUD_19200, FT_INDEX_BAUD_38400,
	FT_INDEX_BAUD_57600, FT_INDEX_BAUD_115200, FT_INDEX_BAUD_230400,
	FT_INDEX_BAUD_460800, FT_INDEX_BAUD_921600,

	FT_INDEX_DATA_BITS_7 = 0, FT_INDEX_DATA_BITS_8,

	FT_INDEX_STOP_BITS_1 = 0, FT_INDEX_STOP_BITS_2,

	FT_INDEX_PARITY_NONE = 0, FT_INDEX_PARITY_ODD, FT_INDEX_PARITY_EVEN,
	FT_INDEX_PARITY_MARK, FT_INDEX_PARITY_SPACE,

	FT_INDEX_FLOW_NONE = 0, FT_INDEX_FLOW_RTS_CTS, FT_INDEX_FLOW_DTR_DSR,
	FT_INDEX_FLOW_XON_XOFF
};
//



class DeviceFtdi {
public:
  FT_HANDLE ftHandle;
  DeviceFtdi();
  ~DeviceFtdi();

  void device_open(int DevNum);
  void device_close();

  BOOL device_reset();
  BOOL device_set_speed(ULONG BaudRate);

  void device_write(char *data, DWORD data_size);
  void device_read(char *data, DWORD data_size);
  BOOL device_set_data_characteristics();
  BOOL device_set_flow_control();
  BOOL device_set_chars();

  BOOL device_get_modem_status();

  void device_set_event_notification();

  void device_set_dtr_rts();

  void device_set_timeouts();

  void device_purge();

};

#endif
