#ifndef BITARRAYTOREGISTER_H
#define BITARRAYTOREGISTER_H

#include <QBitArray>

class BitArrayToRegister {
  public:
    BitArrayToRegister();

    QBitArray value;

    /* ��������� ������ ��� � ����� */
    int arrayToInt32( unsigned index, unsigned size );
    /* ��������� ����� � ������ ��� */
    void int32ToArray( unsigned int src, unsigned index, unsigned size );
};

#endif // BITARRAYTOREGISTER_H
