//---------------------------------------------------------------------------
#include <windows.h>
#include "at_ftdi_module.h"
#include <QtGui>

/* ========================================================================== */
/*                                  ABSTRACT                                  */
/* ========================================================================== */

bool FtdiDevices::reset() {
  FT_STATUS ftStatus;
  ftStatus = FT_ResetDevice(handle);
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


bool FtdiDevices::setSpeed(ULONG BaudRate){
  FT_STATUS ftStatus;
  ftStatus = FT_SetBaudRate(handle, BaudRate);
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

  ftStatus = FT_SetDataCharacteristics(handle, WordLength, StopBits,
    (UCHAR)FT_INDEX_PARITY_NONE);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

bool FtdiDevices::getModemStatus() {
  FT_STATUS ftStatus;
  ULONG Status;
  ftStatus = FT_GetModemStatus(handle, &Status);
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

  ftStatus = FT_SetFlowControl(handle, FlowControl, XonChar, XoffChar);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

bool FtdiDevices::setChars() {
  FT_STATUS ftStatus;
  ftStatus = FT_SetChars(handle, 0, false ? (UCHAR)1 : (UCHAR)0, 0,
    false ? (UCHAR)1 : (UCHAR)0);
  if (!FT_SUCCESS(ftStatus)) {
    return false;
  }
  return true;
}

void FtdiDevices::setEventNotification() {
  FT_SetEventNotification(handle, 0, NULL);
}

 void FtdiDevices::setDtrRts() {
//	 if (true) {
                 FT_SetDtr(handle);
//	 }
//	 else {
//		 FT_ClrDtr(dev.ftHandle);
//	 }

//	 if (true) {
                 FT_SetRts(handle);
//	 }
//	 else {
//		 FT_ClrRts(dev.ftHandle);
//	 }
 }

//void FtdiDevices::SetTimeouts() {
//  FT_SetTimeouts(Handle, FT_DEFAULT_RX_TIMEOUT, FT_DEFAULT_TX_TIMEOUT);
//}

void FtdiDevices::purge() {
  FT_Purge(handle, FT_PURGE_TX | FT_PURGE_RX);
}

/*
 * Открытие устройства
 */
int FtdiDevices::open(QString DevSerialNumber) {
  FT_STATUS ftStatus;
  ftStatus = FT_OpenEx((PVOID)DevSerialNumber.toStdString().c_str(),FT_OPEN_BY_SERIAL_NUMBER, &(handle));
  if (!FT_SUCCESS(ftStatus)) {
      return false;
    }
  return true;
}

/*
 * Установка таймаута
 */
int FtdiDevices::setTimeouts(int timeout_rx, int timeout_tx ) {
  FT_STATUS ftStatus;
  ftStatus = FT_SetTimeouts(handle, timeout_rx, timeout_tx);
  if (!FT_SUCCESS(ftStatus)) {
      return false;
    }
  return true;
}

/*
 * Закрытие устройства
 * TODO: Сделать проверку правильно закрытия и освобождения дескриптора
 */
int FtdiDevices::close(FT_HANDLE Handle) {
  FT_Close(Handle);
  return 0;
}

/*
 *  Запись данных в устройства
 *  TODO: реализовать проверку BytesTransmited параметра
 *  и при необходимости производить запись по новой
 *..пока не запишет все data_size байт
 */
int FtdiDevices::write(char *data, DWORD data_size) {
  FT_STATUS ftStatus;
  DWORD BytesTransmited;
  qDebug()<<"device_write ftHandle"<<handle;
  ftStatus = FT_Write(handle, data, data_size, &BytesTransmited);
  if (ftStatus == FT_OK) {
    if (BytesTransmited == data_size) {
      // передал столько сколько нужно
    }
  }
  else {
  }
  return 0;
}

/*
 *  Чтение данных с устройства
 *  TODO: реализовать проверку BytesReceived параметра
 *  и при необходимости производить чтение по новой
 *..пока не прочитает data_size байт
 */
int FtdiDevices::read(unsigned char *data, DWORD data_size,unsigned int *read_cnt) {
  FT_STATUS ftStatus;
  DWORD BytesReceived;
  qDebug()<<"device_read ftHandle"<<handle;
  ftStatus = FT_Read(handle, data, data_size, &BytesReceived);
  *read_cnt=BytesReceived;
  if (ftStatus == FT_OK) {
      if (BytesReceived == data_size) {
          // принял столько сколько нужно
        }
      else {
          return FT_OTHER_ERROR;
        }
    }
  else {
    }
  return 0;
}

/*
 *
 */
FtdiDevices::FtdiDevices() {
  state=rxTimeout=txTimeout=baudrate=0;
}

/*
 * Деструктор
 */
FtdiDevices::~FtdiDevices() {
}



/* ========================================================================== */
/*                                  UART                                      */
/* ========================================================================== */

/*
 * Открываем сессию работы с UART
 */
UartDevice::UartDevice(QString DevSerialNumber) {

  if (!open(DevSerialNumber))
    state = 1;//return DEV_NOT_OPEN;

  if (!reset())
    state = 1;//return DEV_NOT_RESET;

  if (!setSpeed(9600))
    state = 1;//return DEV_NOT_SET_SPEED;

  if (!setDataCharacteristics())
    state = 1;//return DEV_NOT_SET_DATA_CHARACTERISTICS;

  if (!getModemStatus())
    state = 1;//return DEV_NOT_GET_MODEM_STATUS;

  setEventNotification();

  setDtrRts();

  purge();

  if (!setFlowControl())
    state = 1;//return DEV_NOT_SET_FLOW_CONTROL;

  if (state==0)
    qDebug()<<"I CAN OPEN DEVICE :)!";
  else
    qDebug()<<" I CAN NOT OPEN DEVICE :(!";

}


/*
 * Закрываем сессию работы с UART
 */
UartDevice::~UartDevice() {
  close(handle);
}


