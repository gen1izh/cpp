#ifndef BITARRAYTOREGISTER_H
#define BITARRAYTOREGISTER_H

#include <QBitArray>

class BitArrayToRegister {
  public:
    BitArrayToRegister();

    QBitArray value;

    /* переводит массив бит в число */
    int arrayToInt32( unsigned index, unsigned size );
    /* переводит число в массив бит */
    void int32ToArray( unsigned int src, unsigned index, unsigned size );
};

#endif // BITARRAYTOREGISTER_H
