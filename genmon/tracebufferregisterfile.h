#ifndef TRACEBUFFERREGISTERFILE_H
#define TRACEBUFFERREGISTERFILE_H

#include <QList>

/**
  * Трейс буффер инструкций
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
  * Трейс буффер данных
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
  * Работа с трейс буфером
  */
class traceBufferRegisterFile {
  unsigned int w1;
  unsigned int w2;
  unsigned int w3;
  unsigned int w4;

  unsigned int instTBCurrentOpIndex; // номер инструкции в кольцевом буфере
  unsigned int dataTBCurrentOpIndex; // номер инструкции в кольцевом буфере

  instructionTraceBuffer traceBufferIfInstr[512]; /* 512 записей в кольцевом буфере */
  dataTraceBuffer        traceBufferIfData[512];  /* 512 записей в кольцевом буфере */

  public:
    traceBufferRegisterFile();

//    instructionTraceBuffer inst;
//    dataTraceBuffer        data;

    /* После получения данных блока, перевод его в переменные */
    void convertDataFlowCharToW( char * src );

};

#endif // TRACEBUFFERREGISTERFILE_H
