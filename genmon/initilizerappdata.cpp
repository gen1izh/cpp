#include "initilizerappdata.h"

FtdiDevices             ftdiPort;              // Инициализация модуля работы с FTDI
dsuRegisterFile         dsuRegs;               // Инициализация dsu регистров
logger                  appLogger;             // Инициализация журнала приложения
traceBufferRegisterFile tbRegs;                // Инициализация трейс буфера
dsuProto                dsuProtocol;
