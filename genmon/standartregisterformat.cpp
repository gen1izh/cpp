#include "standartregisterformat.h"


/*******************************************************************************
 *                 Стандартная работа с регистрами
 ******************************************************************************/


/**
  * Возвращает адрес регистра
  */
StandartRegisterFormat::StandartRegisterFormat() {
  addr = 0;
  value.resize(32); // 32 бита регистры
  value.clear();
}

/**
  * Возвращает адрес регистра
  */
unsigned int StandartRegisterFormat::getAddr() {
  return addr;
}

/**
  * Возвращает значение по адресу
  */
unsigned int StandartRegisterFormat::getValue() {
  return arrayToInt32( 0, 32 );
}

/**
  * Устанавливает значение по адресу
  */
void StandartRegisterFormat::setValue( unsigned int v ) {
  value.clear();
}

/**
  * Конвертирование массива бит в число
  */
int StandartRegisterFormat::arrayToInt32( unsigned index, unsigned size ) {
  int result=0, j=0;

  for ( unsigned int i = index; i < index+size; i++,j++ ) {
    bool b = value.testBit(i);
    int b1 = b;
    result |= (int)( b << j );
  }
  return result;
}

/**
  * Конвертирвоание числа в массив бит
  */
void StandartRegisterFormat::int32ToArray( unsigned int src,
                                       unsigned index,   unsigned size ) {
  for ( unsigned int i = 0; i < size; i++ ) {
    value[index + i] = (unsigned int)( 0x1 & (src >> i ) );
  }
}
