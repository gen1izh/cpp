#include "bitarraytoregister.h"

BitArrayToRegister::BitArrayToRegister() {
  value.resize( 32 );
}

/**
  * Конвертирование массива бит в число
  */
int BitArrayToRegister::arrayToInt32( unsigned index, unsigned size ) {
  int result=0, j=0;

  for ( int i = index; i < index+size; i++,j++ ) {
    result |= (int)( (int)(value->at(i)) << j );
  }
  return result;
}

/**
  * Конвертирвоание числа в массив бит
  */
void BitArrayToRegister::int32ToArray( unsigned int src,
                                       unsigned index,   unsigned size ) {
  for ( int i = 0; i < size; i++ ) {    
    value[index + i] = (unsigned int)( 0x1 & (src >> i ) );
  }
}
