#ifndef STANDARTREGISTERFORMAT_H
#define STANDARTREGISTERFORMAT_H

#include <QBitArray>

/*******************************************************************************
 *                 –абота со стандартными функци€ми регистра
 ******************************************************************************/

/**
  * ‘ормат стандартного регистра
  */
class StandartRegisterFormat {
  protected:
    unsigned int addr;  // адресс расположени€ регистра в пам€ти вычислител€
    QBitArray    value; // значение регистра в пам€ти вычислител€
  public:
    StandartRegisterFormat();
    unsigned int getAddr();
    unsigned int getValue();
    void         setValue( unsigned int v );
    int          arrayToInt32(unsigned index, unsigned size);
    void         int32ToArray(unsigned int src, unsigned index, unsigned size);
};


#endif // STANDARTREGISTERFORMAT_H
