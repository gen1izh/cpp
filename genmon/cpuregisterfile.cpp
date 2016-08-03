#include "cpuregisterfile.h"



/*******************************************************************************
 *                      Работа с основными регистром CPU
 ******************************************************************************/

cpuRegisterFile::cpuRegisterFile() {
}

/*******************************************************************************
 *                      Работа с PSR
 ******************************************************************************/

/**
  * Установка значения CWP
  */
void cpuPSRRegister::setCWP(unsigned int v) {
  int32ToArray( v, cwpIndex, cwpSize );
}

/**
  * Установка значения PIL
  */
void cpuPSRRegister::setPIL(unsigned int v) {
  int32ToArray( v, pilIndex, pilSize );
}

/**
  * Установка значения ICC
  */
void cpuPSRRegister::setICC(unsigned int v) {
  int32ToArray( v, iccIndex, iccSize );
}

/**
  * Установка значения VER
  */
void cpuPSRRegister::setVER(unsigned int v) {
  int32ToArray( v, verIndex, verSize );
}

/**
  * Установка значения IMPL
  */
void cpuPSRRegister::setIMPL(unsigned int v) {
  int32ToArray( v, implIndex, implSize );
}

/**
  * Установка значения EC
  */
void cpuPSRRegister::toggleEC() {
  value.toggleBit( ecIndex );
}

/**
  * Установка значения EF
  */
void cpuPSRRegister::toggleEF() {
  value.toggleBit( efIndex );
}

/**
  * Установка значения S
  */
void cpuPSRRegister::toggleS() {
  value.toggleBit( sIndex );
}

/**
  * Установка значения PS
  */
void cpuPSRRegister::togglePS() {
  value.toggleBit( psIndex );
}

/**
  * Установка значения ET
  */
void cpuPSRRegister::toggleET() {
  value.toggleBit( etIndex );
}

/**
  * Получение значения CWP
  */
unsigned int cpuPSRRegister::getCWP() {
  return arrayToInt32( cwpIndex, cwpSize );
}

/**
  * Получение значения PIL
  */
unsigned int cpuPSRRegister::getPIL() {
  return arrayToInt32( pilIndex, pilSize );
}

/**
  * Получение значения ICC
  */
unsigned int cpuPSRRegister::getICC() {
  return arrayToInt32( iccIndex, iccSize );
}

/**
  * Получение значения ICCn
  */
unsigned int cpuPSRRegister::getICCn() {
  return value[iccnIndex];
}

/**
  * Получение значения ICCz
  */
unsigned int cpuPSRRegister::getICCz() {
  return value[icczIndex];
}

/**
  * Получение значения ICCv
  */
unsigned int cpuPSRRegister::getICCv() {
  return value[iccvIndex];
}


/**
  * Получение значения ICCc
  */
unsigned int cpuPSRRegister::getICCc() {
  return value[icccIndex];
}

/**
  * Получение значения VER
  */
unsigned int cpuPSRRegister::getVER(){
  return arrayToInt32( verIndex, verSize );
}

/**
  * Получение значения IMPL
  */
unsigned int cpuPSRRegister::getIMPL() {
  return arrayToInt32( implIndex, implSize );
}

/**
  * Получение значения EC
  */
unsigned int cpuPSRRegister::getEC() {
  return value[ecIndex];
}

/**
  * Получение значения EF
  */
unsigned int cpuPSRRegister::getEF() {
  return value[efIndex];
}

/**
  * Получение значения S
  */
unsigned int cpuPSRRegister::getS() {
  return value[sIndex];
}

/**
  * Получение значения PS
  */
unsigned int cpuPSRRegister::getPS() {
  return value[psIndex];
}

/**
  * Получение значения ET
  */
unsigned int cpuPSRRegister::getET() {
  return value[etIndex];
}

/**
  * Инициализация PSR
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
 *                            Работа с FSR
 ******************************************************************************/

/**
  * Установка CEXC
  */
void cpuFSRRegister::setCEXC(unsigned int v) {
  int32ToArray( v, cexcIndex, cexcSize );
}

/**
  * Установка AEXC
  */
void cpuFSRRegister::setAEXC(unsigned int v) {
  int32ToArray( v, aexcIndex, aexcSize );
}

/**
  * Установка FCC
  */
void cpuFSRRegister::setFCC(unsigned int v) {
  int32ToArray( v, fccIndex, fccSize );
}

/**
  * Установка FTT
  */
void cpuFSRRegister::setFTT(unsigned int v) {
  int32ToArray( v, fttIndex, fttSize );
}

/**
  * Установка VER
  */
void cpuFSRRegister::setVER(unsigned int v) {
  int32ToArray( v, verIndex, verSize );
}

/**
  * Установка RES
  */
void cpuFSRRegister::setRES(unsigned int v){
  int32ToArray( v, resIndex, resSize );
}

/**
  * Установка TEM
  */
void cpuFSRRegister::setTEM(unsigned int v){
  int32ToArray( v, temIndex, temSize );
}

/**
  * Установка U
  */
void cpuFSRRegister::setU(unsigned int v){
  int32ToArray( v, uIndex, uSize );
}

/**
  * Установка RD
  */
void cpuFSRRegister::setRD(unsigned int v){
  int32ToArray( v, rdIndex, rdSize );
}

/**
  * Переключение NS
  */
void cpuFSRRegister::toggleNS(){
  value.toggleBit( nsIndex );
}

/**
  * Переключение QNE
  */
void cpuFSRRegister::toggleQNE(){
  value.toggleBit( qneIndex );
}

/**
  * Переключение Ub
  */
void cpuFSRRegister::toggleUb(){
  value.toggleBit( UbIndex );
}

/**
  * Получение CEXC
  */
unsigned int cpuFSRRegister::getCEXC(){

    return arrayToInt32( cexcIndex, cexcSize );
}

/**
  * Получение AEXC
  */
unsigned int cpuFSRRegister::getAEXC(){
  return arrayToInt32(aexcIndex, aexcSize );
}

/**
  * Получение FCC
  */
unsigned int cpuFSRRegister::getFCC(){
  return arrayToInt32(fccIndex, fccSize );
}

/**
  * Получение FTT
  */
unsigned int cpuFSRRegister::getFTT(){
  return arrayToInt32(fttIndex, fttSize );
}

/**
  * Получение VER
  */
unsigned int cpuFSRRegister::getVER(){
  return arrayToInt32(verIndex, verSize );
}

/**
  * Получение RES
  */
unsigned int cpuFSRRegister::getRES(){
  return arrayToInt32(resIndex, resSize );
}

/**
  * Получение TEM
  */
unsigned int cpuFSRRegister::getTEM(){
  return arrayToInt32(temIndex, temSize );
}

/**
  * Получение U
  */
unsigned int cpuFSRRegister::getU() {
  return arrayToInt32(uIndex, uSize );
}

/**
  * Получение RD
  */
unsigned int cpuFSRRegister::getRD() {
  return arrayToInt32(rdIndex, rdSize );
}

/**
  * Получение NS
  */
unsigned int cpuFSRRegister::getNS() {
  return value[ nsIndex ];

}

/**
  * Получение QNE
  */
unsigned int cpuFSRRegister::getQNE() {
  return value[ qneIndex ];
}

/**
  * Получение Ub
  */
unsigned int cpuFSRRegister::getUb() {
  return value[ UbIndex ];
}

/**
  * Инициализация FSR
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
 *                            Работа с WIM
 ******************************************************************************/

/**
  * Инициализация WIM регистра
  */
cpuWIMRegister::cpuWIMRegister() {
  addr = 0x90080008;
}

/**
  * Чтение значения бита n регистра WIM
  */
unsigned int cpuWIMRegister::getWIMNumber(unsigned int n) {
  return value[n];
}

/*******************************************************************************
 *                            Работа с TBR
 ******************************************************************************/

/**
  * Инициализация TBR регистра
  */
cpuTBRRegister::cpuTBRRegister() {
  addr = 0x9008000C;
}

/**
  * Запись TT
  */
void cpuTBRRegister::setTT(unsigned int v) {
  int32ToArray( v, ttIndex, ttSize );
}

/**
  * Запись TBA
  */
void cpuTBRRegister::setTBA(unsigned int v) {
  int32ToArray( v, tbaIndex, tbaSize );
}

/**
  * Получение ТТ
  */
unsigned int cpuTBRRegister::getTT() {
  return arrayToInt32(ttIndex, ttSize );
}

/**
  * Получение TBA
  */
unsigned int cpuTBRRegister::getTBA() {
  return arrayToInt32(tbaIndex, tbaSize );
}

/*******************************************************************************
 *                            Работа с Y
 ******************************************************************************/
cpuYRegister::cpuYRegister() {
  addr = 0x90080000;
}

/*******************************************************************************
 *                            Работа с PC
 ******************************************************************************/
cpuPCRegister::cpuPCRegister() {
  addr = 0x90080010;
}

/*******************************************************************************
 *                            Работа с NPC
 ******************************************************************************/
cpuNPCRegister::cpuNPCRegister() {
  addr = 0x90080014;
}


