#ifndef CPUREGISTERFILE_H
#define CPUREGISTERFILE_H

#include "standartregisterformat.h"

/**
  * Регистр PSR
  */
class cpuPSRRegister : public StandartRegisterFormat {
  public:
    cpuPSRRegister();
  private:
    static const int cwpSize  = 5;
    static const int pilSize  = 4;
    static const int iccSize  = 4;
    static const int verSize  = 4;
    static const int implSize = 4;

    // индексы положения определнного бита в регистре
    unsigned cwpIndex, pilIndex, iccIndex, verIndex, implIndex,
             ecIndex, efIndex, sIndex, psIndex, etIndex,
             iccnIndex, icczIndex, iccvIndex, icccIndex;

    void setCWP( unsigned int v );    // Установка cwp
    void setPIL( unsigned int v );    // Установка pil
    void setICC( unsigned int v );    // Установка icc
    void setVER( unsigned int v );    // Установка ver
    void setIMPL( unsigned int v );   // Установка impl
    void toggleEC();  // Переключение ec
    void toggleEF();  // Переключение ef
    void toggleS();   // Переключение s
    void togglePS();  // Переключение ps
    void toggleET();  // Переключение et

    unsigned int getCWP();   // Чтение cwp
    unsigned int getPIL();   // Чтение pil
    unsigned int getICC();   // Чтение icc
    unsigned int getICCn();  // Чтение icc бит n
    unsigned int getICCz();  // Чтение icc бит z
    unsigned int getICCv();  // Чтение icc бит v
    unsigned int getICCc();  // Чтение icc бит c

    unsigned int getVER();   // Чтение ver
    unsigned int getIMPL();  // Чтение impl
    unsigned int getEC();    // Чтение ec
    unsigned int getEF();    // Чтение ef
    unsigned int getS();     // Чтение s
    unsigned int getPS();    // Чтение ps
    unsigned int getET();    // Чтение et

};

/**
  * Регистр FSR
  */
class cpuFSRRegister : public StandartRegisterFormat {
  public:
    cpuFSRRegister();
  private:
    static const int cexcSize  = 5;
    static const int aexcSize  = 5;
    static const int fccSize  = 2;
    static const int fttSize  = 3;
    static const int verSize  = 3;
    static const int resSize  = 2;
    static const int temSize  = 5;
    static const int uSize    = 2;
    static const int rdSize   = 2;

    // индексы положения определнного бита в регистре
    unsigned int  cexcIndex,  aexcIndex,  fccIndex, fttIndex, verIndex,
                  resIndex,   temIndex,   uIndex,   rdIndex, nsIndex, qneIndex, UbIndex;

    void setCEXC( unsigned int v );   // Установка CEXC
    void setAEXC( unsigned int v );   // Установка AEXC
    void setFCC( unsigned int v );    // Установка FCC
    void setFTT( unsigned int v );    // Установка FFT
    void setVER( unsigned int v );    // Установка VER
    void setRES( unsigned int v );    // Установка RES
    void setTEM( unsigned int v );    // Установка TEM
    void setU( unsigned int v );      // Установка U
    void setRD( unsigned int v );     // Установка RD

    void toggleNS();    // Переключение NS
    void toggleQNE();   // Переключение QNE
    void toggleUb();    // Переключение Ub

    unsigned int getCEXC();  // Чтение CEXC
    unsigned int getAEXC();  // Чтение AEXC
    unsigned int getFCC();   // Чтение FCC
    unsigned int getFTT();   // Чтение FTT
    unsigned int getVER();   // Чтение VER
    unsigned int getRES();   // Чтение RES
    unsigned int getTEM();   // Чтение TEM
    unsigned int getU();     // Чтение U
    unsigned int getRD();    // Чтение RD
    unsigned int getNS();    // Чтение NS
    unsigned int getQNE();   // Чтение QNE
    unsigned int getUb();    // Чтение Ub

};


/**
  * Регистр WIM
  */
class cpuWIMRegister : public StandartRegisterFormat {
  public:
    cpuWIMRegister();
  private:

    unsigned int getWIMNumber( unsigned int n );   // Чтение значения бита n регистра WIM

};


/**
  * Регистр TBR
  */
class cpuTBRRegister : public StandartRegisterFormat {
  public:
    cpuTBRRegister();
  private:
    static const int ttSize   = 8;
    static const int tbaSize  = 20;

    // индексы положения определнного бита в регистре
    unsigned ttIndex, tbaIndex;

    void setTT( unsigned int v );     // Установка tt
    void setTBA( unsigned int v );    // Установка tba

    unsigned int getTT();     // Чтение tt
    unsigned int getTBA();    // Чтение tba

};


/**
  * Регистр Y
  */
class cpuYRegister : public StandartRegisterFormat {
  public:
    cpuYRegister();
};


/**
  * Регистр PC
  */
class cpuPCRegister : public StandartRegisterFormat {
  public:
    cpuPCRegister();
};


/**
  * Регистр NPC
  */
class cpuNPCRegister : public StandartRegisterFormat {
  public:
    cpuNPCRegister();
};


/*******************************************************************************
 *                  Работа с основными регистрами CPU
 ******************************************************************************/

class cpuRegisterFile {
  public:
    cpuRegisterFile();

    cpuPSRRegister  PSR;
    cpuFSRRegister  FSR;
    cpuWIMRegister  WIM;
    cpuTBRRegister  TBR;
    cpuYRegister    Y;
    cpuPCRegister   PC;
    cpuNPCRegister  NPC;
};

#endif // CPUREGISTERFILE_H
