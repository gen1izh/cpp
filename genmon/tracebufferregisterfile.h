#ifndef TRACEBUFFERREGISTERFILE_H
#define TRACEBUFFERREGISTERFILE_H

#include <QList>

/**
  * ����� ������ ����������
  */
class instructionTraceBuffer {

  unsigned int instBreakpointHit;
  unsigned int multiCycleInstruction;
  unsigned int timeTagCounter;
  unsigned int loadStoreParams;
  unsigned int pc;
  unsigned int instTrap;
  unsigned int errMode;
  unsigned int opcode;

  public:
    instructionTraceBuffer();

    void fillAllFields( unsigned int w1, unsigned int w2,
                        unsigned int w3, unsigned int w4  );

    unsigned int getInstBreakpointHit();
    unsigned int getMultiCycleInstruction();
    unsigned int getTimeTagCounter();
    unsigned int getLoadStoreParams();
    unsigned int getPC();
    unsigned int getInstTrap();
    unsigned int getErrMode();
    unsigned int getOpcode();
};

/**
  * ����� ������ ������
  */
class dataTraceBuffer {

  unsigned int ahbBreakpointHit;
  unsigned int dsuCounter;
  unsigned int IRL;
  unsigned int PIL;
  unsigned int trapType;
  unsigned int hWrite;
  unsigned int hTrans;
  unsigned int hSize;
  unsigned int hBurst;
  unsigned int hMaster;
  unsigned int hMastLock;
  unsigned int hResp;
  unsigned int loadStoreData;
  unsigned int loadStoreAddr;

  public:
    dataTraceBuffer();

    void fillAllFields( unsigned int w1, unsigned int w2,
                        unsigned int w3, unsigned int w4  );

    unsigned int getAHBBreakpointHit();
    unsigned int getDSUCounter();
    unsigned int getIRL();
    unsigned int getPIL();
    unsigned int getTrapType();
    unsigned int getHWrite();
    unsigned int getHTrans();
    unsigned int getHSize();
    unsigned int getHBurst();
    unsigned int getHMaster();
    unsigned int getHMastLock();
    unsigned int getHResp();
    unsigned int getLoadStoreData();
    unsigned int getLoadStoreAddr();

};

/**
  * ������ � ����� �������
  */
class traceBufferRegisterFile {
  unsigned int w1;
  unsigned int w2;
  unsigned int w3;
  unsigned int w4;

  unsigned int instTBCurrentOpIndex; // ����� ���������� � ��������� ������
  unsigned int dataTBCurrentOpIndex; // ����� ���������� � ��������� ������

  instructionTraceBuffer traceBufferIfInstr[512]; /* 512 ������� � ��������� ������ */
  dataTraceBuffer        traceBufferIfData[512];  /* 512 ������� � ��������� ������ */

  public:
    traceBufferRegisterFile();

//    instructionTraceBuffer inst;
//    dataTraceBuffer        data;

    /* ����� ��������� ������ �����, ������� ��� � ���������� */
    void convertDataFlowCharToW( char * src );

};

#endif // TRACEBUFFERREGISTERFILE_H
