// ---------------------------------------------------------------------------

#pragma hdrstop

#include "ftdiapiwrapper.h"
#include <vcl.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------

BOOL DeviceFtdi::device_reset() {
  FT_STATUS ftStatus;
  ftStatus = FT_ResetDevice(ftHandle);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

BOOL DeviceFtdi::device_set_speed(ULONG BaudRate) {
  FT_STATUS ftStatus;
  ftStatus = FT_SetBaudRate(ftHandle, BaudRate);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

BOOL DeviceFtdi::device_set_data_characteristics() {
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

  ftStatus = FT_SetDataCharacteristics(ftHandle, WordLength, StopBits,
    (UCHAR)FT_INDEX_PARITY_NONE);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

BOOL DeviceFtdi::device_get_modem_status() {
  FT_STATUS ftStatus;
  ULONG Status;
  ftStatus = FT_GetModemStatus(ftHandle, &Status);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

BOOL DeviceFtdi::device_set_flow_control() {
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

  ftStatus = FT_SetFlowControl(ftHandle, FlowControl, XonChar, XoffChar);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

BOOL DeviceFtdi::device_set_chars() {
  FT_STATUS ftStatus;
  ftStatus = FT_SetChars(ftHandle, 0, false ? (UCHAR)1 : (UCHAR)0, 0,
    false ? (UCHAR)1 : (UCHAR)0);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

void DeviceFtdi::device_set_event_notification() {
  FT_SetEventNotification(ftHandle, 0, NULL);
}

void DeviceFtdi::device_set_dtr_rts() {
  // if (true) {
  FT_SetDtr(ftHandle);
  // }
  // else {
  // FT_ClrDtr(ftHandle);
  // }

  // if (true) {
  FT_SetRts(ftHandle);
  // }
  // else {
  // FT_ClrRts(ftHandle);
  // }
}

void DeviceFtdi::device_set_timeouts() {
  FT_SetTimeouts(ftHandle, FT_DEFAULT_RX_TIMEOUT, FT_DEFAULT_TX_TIMEOUT);
}

void DeviceFtdi::device_purge() {
  FT_Purge(ftHandle, FT_PURGE_TX | FT_PURGE_RX);
}

//
void DeviceFtdi::device_open(int DevNum) {

  FT_STATUS ftStatus;

  ftStatus = FT_Open(DevNum, &ftHandle);
  if (!FT_SUCCESS(ftStatus))
    ShowMessage("Не могу открыть устройство!");

  if (!device_reset())
    return;

  if (!device_set_speed(9600))
    return;

  if (!device_set_data_characteristics())
    return;

  if (!device_get_modem_status())
    return;

  device_set_event_notification();

  device_set_dtr_rts();

  device_set_timeouts();

  device_purge();

  if (!device_set_flow_control())
    return;

  ShowMessage("Смог открыть устройство!");
}

void DeviceFtdi::device_close() {
  FT_Close(ftHandle);
}

DeviceFtdi::DeviceFtdi() {

}

DeviceFtdi::~DeviceFtdi() {
}

void DeviceFtdi::device_write(char *data, DWORD data_size) {
  FT_STATUS ftStatus;
  DWORD BytesTransmited;

  ftStatus = FT_Write(ftHandle, data, data_size, &BytesTransmited);
  if (ftStatus == FT_OK) {
    if (BytesTransmited == data_size) {
      // передал столько сколько нужно
    }
  }
  else {
    ShowMessage("FAIL");
  }
}

void DeviceFtdi::device_read(char *data, DWORD data_size) {
  FT_STATUS ftStatus;
  DWORD BytesReceived;

  ftStatus = FT_Read(ftHandle, data, data_size, &BytesReceived);
  if (ftStatus == FT_OK) {
    if (BytesReceived == data_size) {
      // передал столько сколько нужно

    }
  }
  else {
    ShowMessage("FAIL");
  }
}
