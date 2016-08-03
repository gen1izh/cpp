#ifndef CPUREGISTERFILE_H
#define CPUREGISTERFILE_H

#include "standartregisterformat.h"

/**
  * ������� PSR
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

    // ������� ��������� ������������ ���� � ��������
    unsigned cwpIndex, pilIndex, iccIndex, verIndex, implIndex,
             ecIndex, efIndex, sIndex, psIndex, etIndex,
             iccnIndex, icczIndex, iccvIndex, icccIndex;

    void setCWP( unsigned int v );    // ��������� cwp
    void setPIL( unsigned int v );    // ��������� pil
    void setICC( unsigned int v );    // ��������� icc
    void setVER( unsigned int v );    // ��������� ver
    void setIMPL( unsigned int v );   // ��������� impl
    void toggleEC();  // ������������ ec
    void toggleEF();  // ������������ ef
    void toggleS();   // ������������ s
    void togglePS();  // ������������ ps
    void toggleET();  // ������������ et

    unsigned int getCWP();   // ������ cwp
    unsigned int getPIL();   // ������ pil
    unsigned int getICC();   // ������ icc
    unsigned int getICCn();  // ������ icc ��� n
    unsigned int getICCz();  // ������ icc ��� z
    unsigned int getICCv();  // ������ icc ��� v
    unsigned int getICCc();  // ������ icc ��� c

    unsigned int getVER();   // ������ ver
    unsigned int getIMPL();  // ������ impl
    unsigned int getEC();    // ������ ec
    unsigned int getEF();    // ������ ef
    unsigned int getS();     // ������ s
    unsigned int getPS();    // ������ ps
    unsigned int getET();    // ������ et

};

/**
  * ������� FSR
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

    // ������� ��������� ������������ ���� � ��������
    unsigned int  cexcIndex,  aexcIndex,  fccIndex, fttIndex, verIndex,
                  resIndex,   temIndex,   uIndex,   rdIndex, nsIndex, qneIndex, UbIndex;

    void setCEXC( unsigned int v );   // ��������� CEXC
    void setAEXC( unsigned int v );   // ��������� AEXC
    void setFCC( unsigned int v );    // ��������� FCC
    void setFTT( unsigned int v );    // ��������� FFT
    void setVER( unsigned int v );    // ��������� VER
    void setRES( unsigned int v );    // ��������� RES
    void setTEM( unsigned int v );    // ��������� TEM
    void setU( unsigned int v );      // ��������� U
    void setRD( unsigned int v );     // ��������� RD

    void toggleNS();    // ������������ NS
    void toggleQNE();   // ������������ QNE
    void toggleUb();    // ������������ Ub

    unsigned int getCEXC();  // ������ CEXC
    unsigned int getAEXC();  // ������ AEXC
    unsigned int getFCC();   // ������ FCC
    unsigned int getFTT();   // ������ FTT
    unsigned int getVER();   // ������ VER
    unsigned int getRES();   // ������ RES
    unsigned int getTEM();   // ������ TEM
    unsigned int getU();     // ������ U
    unsigned int getRD();    // ������ RD
    unsigned int getNS();    // ������ NS
    unsigned int getQNE();   // ������ QNE
    unsigned int getUb();    // ������ Ub

};


/**
  * ������� WIM
  */
class cpuWIMRegister : public StandartRegisterFormat {
  public:
    cpuWIMRegister();
  private:

    unsigned int getWIMNumber( unsigned int n );   // ������ �������� ���� n �������� WIM

};


/**
  * ������� TBR
  */
class cpuTBRRegister : public StandartRegisterFormat {
  public:
    cpuTBRRegister();
  private:
    static const int ttSize   = 8;
    static const int tbaSize  = 20;

    // ������� ��������� ������������ ���� � ��������
    unsigned ttIndex, tbaIndex;

    void setTT( unsigned int v );     // ��������� tt
    void setTBA( unsigned int v );    // ��������� tba

    unsigned int getTT();     // ������ tt
    unsigned int getTBA();    // ������ tba

};


/**
  * ������� Y
  */
class cpuYRegister : public StandartRegisterFormat {
  public:
    cpuYRegister();
};


/**
  * ������� PC
  */
class cpuPCRegister : public StandartRegisterFormat {
  public:
    cpuPCRegister();
};


/**
  * ������� NPC
  */
class cpuNPCRegister : public StandartRegisterFormat {
  public:
    cpuNPCRegister();
};


/*******************************************************************************
 *                  ������ � ��������� ���������� CPU
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
