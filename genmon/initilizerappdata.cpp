#include "initilizerappdata.h"

FtdiDevices             ftdiPort;              // ������������� ������ ������ � FTDI
dsuRegisterFile         dsuRegs;               // ������������� dsu ���������
logger                  appLogger;             // ������������� ������� ����������
traceBufferRegisterFile tbRegs;                // ������������� ����� ������
dsuProto                dsuProtocol;
