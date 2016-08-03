#ifndef INITILIZERAPPDATA_H
#define INITILIZERAPPDATA_H

#include "dsuregisterfile.h"
#include "tracebufferregisterfile.h"
#include "ftdimodule.h"
#include "dsuproto.h"
#include "logger.h"

extern FtdiDevices             ftdiPort;    // Инициализация модуля работы с FTDI
extern dsuRegisterFile         dsuRegs;     // Инициализация dsu регистров
extern logger                  appLogger;   // Инициализация журнала приложения
extern traceBufferRegisterFile tbRegs;      // Инициализация трейс буфера
extern dsuProto                dsuProtocol;


#endif // INITILIZERAPPDATA_H
