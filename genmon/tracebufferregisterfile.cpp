#include "tracebufferregisterfile.h"


/*******************************************************************************
 *                     ������ � instruction trace buffer
 ******************************************************************************/

instructionTraceBuffer::instructionTraceBuffer(){
}

/**
  * TODO: magic number
  * ���������� ����� instruction trace buffer
  */
void instructionTraceBuffer::fillAllFields(unsigned int w1,
                                           unsigned int w2,
                                           unsigned int w3,
                                           unsigned int w4 ) {


  instBreakpointHit     = (w1 >> 31);
  multiCycleInstruction = (w1 >> 30);
  timeTagCounter        = 0x3fffffff&w1;

  loadStoreParams = w2;

  pc              = (w3 >> 2);
  instTrap        = ((0x2 & w3) >> 1) ;
  errMode         = (0x1 & w3);

  opcode  = w4;
}



/**
  * ��������� �������� ���� ��� "����������" �� ����������
  */
unsigned int instructionTraceBuffer::getInstBreakpointHit() {
  return instBreakpointHit;
}

/**
  * ��������� �������� ��������������� ����������
  */
unsigned int instructionTraceBuffer::getMultiCycleInstruction() {
  return multiCycleInstruction;
}

/**
  * ��������� �������� �������� ����� �������
  */
unsigned int instructionTraceBuffer::getTimeTagCounter() {
  return  timeTagCounter;
}

/**
  * ��������� ��������� ���������� ����������
  */
unsigned int instructionTraceBuffer::getLoadStoreParams() {
  return loadStoreParams;
}

/**
  * ��������� ��������� �� �������
  */
unsigned int instructionTraceBuffer::getPC() {
  return pc;
}

/**
  * ��������� �������� �������� �����
  */
unsigned int instructionTraceBuffer::getInstTrap() {
  return instTrap;
}

/**
  * ��������� ���������� ������
  */
unsigned int instructionTraceBuffer::getErrMode() {
 return  errMode;
}

/**
  * ��������� ���� �������
  */
unsigned int instructionTraceBuffer::getOpcode() {
  return opcode;
}


/*******************************************************************************
 *                           ������ � data trace buffer
 ******************************************************************************/

dataTraceBuffer::dataTraceBuffer() {
}

/**
  * TODO: magic number
  * ���������� ����� data trace buffer
  */
void dataTraceBuffer::fillAllFields(unsigned int w1,
                                    unsigned int w2,
                                    unsigned int w3,
                                    unsigned int w4) {

  ahbBreakpointHit  = (w1 >> 31);
  dsuCounter        = 0x3fffffff&w1;

  IRL               = (w2 & 0xf0000000) >>  28;
  PIL               = (w2 & 0xf000000)  >>  24;
  trapType          = (w2 & 0xff000)    >>  16;
  hWrite            = (w2 & 0x8000)     >>  15;
  hTrans            = (w2 & 0x6000)     >>  13;
  hSize             = (w2 & 0x1C00)     >>  10;
  hBurst            = (w2 & 0x380)      >> 7;
  hMaster           = (w2 & 0x78 )      >> 3;
  hMastLock         = (0x4 & w2)        >> 2;
  hResp             =  0x3 & w2;

  loadStoreData     = w3;

  loadStoreAddr     = w4;

}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getAHBBreakpointHit() {
  return ahbBreakpointHit;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getDSUCounter() {
  return dsuCounter;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getIRL() {
  return IRL;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getPIL() {
  return PIL;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getTrapType() {
  return trapType;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHWrite() {
  return hWrite;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHTrans() {
  return hTrans;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHSize() {
  return hSize;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHBurst() {
  return hBurst;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHMaster() {
  return hMaster;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHMastLock(){
  return hMastLock;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getHResp(){
  return hResp;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getLoadStoreData() {
  return loadStoreData;
}

/**
  * ���������
  */
unsigned int dataTraceBuffer::getLoadStoreAddr() {
  return loadStoreAddr;
}


/*******************************************************************************
 *                          ������ � ����� �������
 ******************************************************************************/

traceBufferRegisterFile::traceBufferRegisterFile() {
}

/**
  * ����� ��������� ������ �����, ������� ��� � ����������
  */
void traceBufferRegisterFile::convertDataFlowCharToW(char *src) {
  w1 = (unsigned int)((src[0]<<24)  | (src[1]<<16)  | (src[2]<<8)  | (src[3]));
  w2 = (unsigned int)((src[4]<<24)  | (src[5]<<16)  | (src[6]<<8)  | (src[7]));
  w3 = (unsigned int)((src[8]<<24)  | (src[9]<<16)  | (src[10]<<8) | (src[11]));
  w4 = (unsigned int)((src[12]<<24) | (src[13]<<16) | (src[14]<<8) | (src[15]));
}





