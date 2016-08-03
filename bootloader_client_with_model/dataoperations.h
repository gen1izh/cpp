#ifndef DATAOPERATIONS_H
#define DATAOPERATIONS_H

#include <QtGui>

#define MD_SIZE 64*1024 // 64K

#define IMG_HAVE_N_MD 10 // 10MD max - img

#define CRC_TABLE_LEN 256 // 10MD max - img

class DataArraysOperations
{
private:
    quint32 tableCrc32[CRC_TABLE_LEN];

public: 
    int         _currentPosX;
    int         _currentPosY;
    quint32     start_zero_zone;
    quint32     end_zero_zone;
    quint32     _mdCrc32[IMG_HAVE_N_MD];
    quint8      _md[IMG_HAVE_N_MD][MD_SIZE];

    DataArraysOperations();
    void    init();
//    void    fillTableCrc32();
//    quint32 calcCrc32(quint8 *buf, quint32 kol);
    void    fillMdCrc32();
    void    fillMdQueue( quint8 data );
    void    getCurrentPosXY( int *_currPosX, int *_currPosY );

    void init_crc_table(int szz, int ezz);
    quint32 crc32_calc(const quint8 *buf, size_t len, quint8 pr);

};

extern DataArraysOperations doperations;

#endif // DATAOPERATIONS_H
