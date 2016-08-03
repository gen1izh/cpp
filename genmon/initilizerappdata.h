#ifndef INITILIZERAPPDATA_H
#define INITILIZERAPPDATA_H

#include "dsuregisterfile.h"
#include "tracebufferregisterfile.h"
#include "ftdimodule.h"
#include "dsuproto.h"
#include "logger.h"

extern FtdiDevices             ftdiPort;    // ������������� ������ ������ � FTDI
extern dsuRegisterFile         dsuRegs;     // ������������� dsu ���������
extern logger                  appLogger;   // ������������� ������� ����������
extern traceBufferRegisterFile tbRegs;      // ������������� ����� ������
extern dsuProto                dsuProtocol;


#endif // INITILIZERAPPDATA_H
