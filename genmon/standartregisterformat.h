#ifndef STANDARTREGISTERFORMAT_H
#define STANDARTREGISTERFORMAT_H

#include <QBitArray>

/*******************************************************************************
 *                 ������ �� ������������ ��������� ��������
 ******************************************************************************/

/**
  * ������ ������������ ��������
  */
class StandartRegisterFormat {
  protected:
    unsigned int addr;  // ������ ������������ �������� � ������ �����������
    QBitArray    value; // �������� �������� � ������ �����������
  public:
    StandartRegisterFormat();
    unsigned int getAddr();
    unsigned int getValue();
    void         setValue( unsigned int v );
    int          arrayToInt32(unsigned index, unsigned size);
    void         int32ToArray(unsigned int src, unsigned index, unsigned size);
};


#endif // STANDARTREGISTERFORMAT_H
