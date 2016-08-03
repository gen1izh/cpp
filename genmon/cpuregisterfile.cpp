#include "cpuregisterfile.h"



/*******************************************************************************
 *                      ������ � ��������� ��������� CPU
 ******************************************************************************/

cpuRegisterFile::cpuRegisterFile() {
}

/*******************************************************************************
 *                      ������ � PSR
 ******************************************************************************/

/**
  * ��������� �������� CWP
  */
void cpuPSRRegister::setCWP(unsigned int v) {
  int32ToArray( v, cwpIndex, cwpSize );
}

/**
  * ��������� �������� PIL
  */
void cpuPSRRegister::setPIL(unsigned int v) {
  int32ToArray( v, pilIndex, pilSize );
}

/**
  * ��������� �������� ICC
  */
void cpuPSRRegister::setICC(unsigned int v) {
  int32ToArray( v, iccIndex, iccSize );
}

/**
  * ��������� �������� VER
  */
void cpuPSRRegister::setVER(unsigned int v) {
  int32ToArray( v, verIndex, verSize );
}

/**
  * ��������� �������� IMPL
  */
void cpuPSRRegister::setIMPL(unsigned int v) {
  int32ToArray( v, implIndex, implSize );
}

/**
  * ��������� �������� EC
  */
void cpuPSRRegister::toggleEC() {
  value.toggleBit( ecIndex );
}

/**
  * ��������� �������� EF
  */
void cpuPSRRegister::toggleEF() {
  value.toggleBit( efIndex );
}

/**
  * ��������� �������� S
  */
void cpuPSRRegister::toggleS() {
  value.toggleBit( sIndex );
}

/**
  * ��������� �������� PS
  */
void cpuPSRRegister::togglePS() {
  value.toggleBit( psIndex );
}

/**
  * ��������� �������� ET
  */
void cpuPSRRegister::toggleET() {
  value.toggleBit( etIndex );
}

/**
  * ��������� �������� CWP
  */
unsigned int cpuPSRRegister::getCWP() {
  return arrayToInt32( cwpIndex, cwpSize );
}

/**
  * ��������� �������� PIL
  */
unsigned int cpuPSRRegister::getPIL() {
  return arrayToInt32( pilIndex, pilSize );
}

/**
  * ��������� �������� ICC
  */
unsigned int cpuPSRRegister::getICC() {
  return arrayToInt32( iccIndex, iccSize );
}

/**
  * ��������� �������� ICCn
  */
unsigned int cpuPSRRegister::getICCn() {
  return value[iccnIndex];
}

/**
  * ��������� �������� ICCz
  */
unsigned int cpuPSRRegister::getICCz() {
  return value[icczIndex];
}

/**
  * ��������� �������� ICCv
  */
unsigned int cpuPSRRegister::getICCv() {
  return value[iccvIndex];
}


/**
  * ��������� �������� ICCc
  */
unsigned int cpuPSRRegister::getICCc() {
  return value[icccIndex];
}

/**
  * ��������� �������� VER
  */
unsigned int cpuPSRRegister::getVER(){
  return arrayToInt32( verIndex, verSize );
}

/**
  * ��������� �������� IMPL
  */
unsigned int cpuPSRRegister::getIMPL() {
  return arrayToInt32( implIndex, implSize );
}

/**
  * ��������� �������� EC
  */
unsigned int cpuPSRRegister::getEC() {
  return value[ecIndex];
}

/**
  * ��������� �������� EF
  */
unsigned int cpuPSRRegister::getEF() {
  return value[efIndex];
}

/**
  * ��������� �������� S
  */
unsigned int cpuPSRRegister::getS() {
  return value[sIndex];
}

/**
  * ��������� �������� PS
  */
unsigned int cpuPSRRegister::getPS() {
  return value[psIndex];
}

/**
  * ��������� �������� ET
  */
unsigned int cpuPSRRegister::getET() {
  return value[etIndex];
}

/**
  * ������������� PSR
  */
cpuPSRRegister::cpuPSRRegister() {
  addr      = 0x90080004;

  cwpIndex  = 0;
  pilIndex  = 8;
  iccIndex  = 20;
  verIndex  = 24;
  implIndex = 28;
  ecIndex   = 13;
  efIndex   = 12;
  sIndex    = 7;
  psIndex   = 6;
  etIndex   = 5;
  iccnIndex = 23;
  icczIndex = 22;
  iccvIndex = 21;
  icccIndex = 20;
}


/*******************************************************************************
 *                            ������ � FSR
 ******************************************************************************/

/**
  * ��������� CEXC
  */
void cpuFSRRegister::setCEXC(unsigned int v) {
  int32ToArray( v, cexcIndex, cexcSize );
}

/**
  * ��������� AEXC
  */
void cpuFSRRegister::setAEXC(unsigned int v) {
  int32ToArray( v, aexcIndex, aexcSize );
}

/**
  * ��������� FCC
  */
void cpuFSRRegister::setFCC(unsigned int v) {
  int32ToArray( v, fccIndex, fccSize );
}

/**
  * ��������� FTT
  */
void cpuFSRRegister::setFTT(unsigned int v) {
  int32ToArray( v, fttIndex, fttSize );
}

/**
  * ��������� VER
  */
void cpuFSRRegister::setVER(unsigned int v) {
  int32ToArray( v, verIndex, verSize );
}

/**
  * ��������� RES
  */
void cpuFSRRegister::setRES(unsigned int v){
  int32ToArray( v, resIndex, resSize );
}

/**
  * ��������� TEM
  */
void cpuFSRRegister::setTEM(unsigned int v){
  int32ToArray( v, temIndex, temSize );
}

/**
  * ��������� U
  */
void cpuFSRRegister::setU(unsigned int v){
  int32ToArray( v, uIndex, uSize );
}

/**
  * ��������� RD
  */
void cpuFSRRegister::setRD(unsigned int v){
  int32ToArray( v, rdIndex, rdSize );
}

/**
  * ������������ NS
  */
void cpuFSRRegister::toggleNS(){
  value.toggleBit( nsIndex );
}

/**
  * ������������ QNE
  */
void cpuFSRRegister::toggleQNE(){
  value.toggleBit( qneIndex );
}

/**
  * ������������ Ub
  */
void cpuFSRRegister::toggleUb(){
  value.toggleBit( UbIndex );
}

/**
  * ��������� CEXC
  */
unsigned int cpuFSRRegister::getCEXC(){

    return arrayToInt32( cexcIndex, cexcSize );
}

/**
  * ��������� AEXC
  */
unsigned int cpuFSRRegister::getAEXC(){
  return arrayToInt32(aexcIndex, aexcSize );
}

/**
  * ��������� FCC
  */
unsigned int cpuFSRRegister::getFCC(){
  return arrayToInt32(fccIndex, fccSize );
}

/**
  * ��������� FTT
  */
unsigned int cpuFSRRegister::getFTT(){
  return arrayToInt32(fttIndex, fttSize );
}

/**
  * ��������� VER
  */
unsigned int cpuFSRRegister::getVER(){
  return arrayToInt32(verIndex, verSize );
}

/**
  * ��������� RES
  */
unsigned int cpuFSRRegister::getRES(){
  return arrayToInt32(resIndex, resSize );
}

/**
  * ��������� TEM
  */
unsigned int cpuFSRRegister::getTEM(){
  return arrayToInt32(temIndex, temSize );
}

/**
  * ��������� U
  */
unsigned int cpuFSRRegister::getU() {
  return arrayToInt32(uIndex, uSize );
}

/**
  * ��������� RD
  */
unsigned int cpuFSRRegister::getRD() {
  return arrayToInt32(rdIndex, rdSize );
}

/**
  * ��������� NS
  */
unsigned int cpuFSRRegister::getNS() {
  return value[ nsIndex ];

}

/**
  * ��������� QNE
  */
unsigned int cpuFSRRegister::getQNE() {
  return value[ qneIndex ];
}

/**
  * ��������� Ub
  */
unsigned int cpuFSRRegister::getUb() {
  return value[ UbIndex ];
}

/**
  * ������������� FSR
  */
cpuFSRRegister::cpuFSRRegister() {
  addr = 0x90080018;

  cexcIndex = 0;
  aexcIndex = 5;
  fccIndex  = 10;
  fttIndex  = 14;
  verIndex  = 17;
  resIndex  = 20;
  temIndex  = 23;
  uIndex    = 12;
  rdIndex   = 30;
  nsIndex   = 22;
  qneIndex  = 13;
  UbIndex   = 13;
}

/*******************************************************************************
 *                            ������ � WIM
 ******************************************************************************/

/**
  * ������������� WIM ��������
  */
cpuWIMRegister::cpuWIMRegister() {
  addr = 0x90080008;
}

/**
  * ������ �������� ���� n �������� WIM
  */
unsigned int cpuWIMRegister::getWIMNumber(unsigned int n) {
  return value[n];
}

/*******************************************************************************
 *                            ������ � TBR
 ******************************************************************************/

/**
  * ������������� TBR ��������
  */
cpuTBRRegister::cpuTBRRegister() {
  addr = 0x9008000C;
}

/**
  * ������ TT
  */
void cpuTBRRegister::setTT(unsigned int v) {
  int32ToArray( v, ttIndex, ttSize );
}

/**
  * ������ TBA
  */
void cpuTBRRegister::setTBA(unsigned int v) {
  int32ToArray( v, tbaIndex, tbaSize );
}

/**
  * ��������� ��
  */
unsigned int cpuTBRRegister::getTT() {
  return arrayToInt32(ttIndex, ttSize );
}

/**
  * ��������� TBA
  */
unsigned int cpuTBRRegister::getTBA() {
  return arrayToInt32(tbaIndex, tbaSize );
}

/*******************************************************************************
 *                            ������ � Y
 ******************************************************************************/
cpuYRegister::cpuYRegister() {
  addr = 0x90080000;
}

/*******************************************************************************
 *                            ������ � PC
 ******************************************************************************/
cpuPCRegister::cpuPCRegister() {
  addr = 0x90080010;
}

/*******************************************************************************
 *                            ������ � NPC
 ******************************************************************************/
cpuNPCRegister::cpuNPCRegister() {
  addr = 0x90080014;
}


