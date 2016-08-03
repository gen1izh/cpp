#include "standartregisterformat.h"


/*******************************************************************************
 *                 ����������� ������ � ����������
 ******************************************************************************/


/**
  * ���������� ����� ��������
  */
StandartRegisterFormat::StandartRegisterFormat() {
  addr = 0;
  value.resize(32); // 32 ���� ��������
  value.clear();
}

/**
  * ���������� ����� ��������
  */
unsigned int StandartRegisterFormat::getAddr() {
  return addr;
}

/**
  * ���������� �������� �� ������
  */
unsigned int StandartRegisterFormat::getValue() {
  return arrayToInt32( 0, 32 );
}

/**
  * ������������� �������� �� ������
  */
void StandartRegisterFormat::setValue( unsigned int v ) {
  value.clear();
}

/**
  * ��������������� ������� ��� � �����
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
  * ��������������� ����� � ������ ���
  */
void StandartRegisterFormat::int32ToArray( unsigned int src,
                                       unsigned index,   unsigned size ) {
  for ( unsigned int i = 0; i < size; i++ ) {
    value[index + i] = (unsigned int)( 0x1 & (src >> i ) );
  }
}
