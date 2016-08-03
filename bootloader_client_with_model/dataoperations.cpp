#include "dataoperations.h"

DataArraysOperations doperations;

DataArraysOperations::DataArraysOperations()
{
    init();
}

void DataArraysOperations::init()
{
    _currentPosX = 0;
    _currentPosY = 0;
//    fillTableCrc32();
    init_crc_table( 0, 0 );
}

void DataArraysOperations::init_crc_table( int szz, int ezz ) {
  start_zero_zone = szz;
  end_zero_zone   = ezz;
}

quint32 DataArraysOperations::crc32_calc( quint8 const *buf, size_t len, quint8 pr )
{
quint32  crc_table[256];
quint32  crc;
int       i, j;
quint32  curr_index;

curr_index = 0;

for (i = 0; i < 256; i++) {
  crc = i;
  for (j = 0; j < 8; j++)
    crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
  crc_table[i] = crc;
};
crc = 0xFFFFFFFFUL;
while (len--) {
    if (( pr == 0 ) && ( start_zero_zone <= curr_index   ) && ( curr_index <= end_zero_zone ) ) {
      crc = crc_table[(crc ^ 0x00) & 0xFF] ^ (crc >> 8);
      buf++;
    }
    else {
      crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);
    }
  curr_index++;
}

return crc ^ 0xFFFFFFFFUL;
}





//void DataOperations::fillTableCrc32()
//{
//    quint32 poly = 0xedb88320;
//    quint32 temp = 0;
//    for ( quint32 i = 0; i < CRC_TABLE_LEN; ++i ) {
//        temp = i;
//        for ( qint32 j = 8; j > 0; --j ) {
//            if ( (temp & 1) == 1 ) {
//                temp = (quint32)((temp >> 1) ^ poly);
//            }
//            else
//            {
//                temp >>= 1;
//            }
//        }
//        tableCrc32[i] = temp;
//    }
//}

//quint32 DataOperations::calcCrc32( quint8 *buf, quint32 kol ) {
//    quint32 crc = 0xffffffff;
//    for (qint32 i = 0; i < kol; i++)
//    {
//        quint8 index = (quint8)(((crc) & 0xff) ^ buf[i]);
//        crc = (qint32)((crc >> 8) ^ tableCrc32[index]);
//    }
//    return ~crc;
//}

void DataArraysOperations::fillMdCrc32()
{
    for ( int j = 0; j < _currentPosX; j++ ) {
        _mdCrc32[j] = crc32_calc( (quint8 *)&_md[j][0], MD_SIZE, 1 );
    }

    _mdCrc32[_currentPosX] = crc32_calc( (quint8 *)&_md[_currentPosX][0], _currentPosY, 1 );

}

void DataArraysOperations::fillMdQueue( quint8 data)
{
    _md[_currentPosX][_currentPosY] = data;

    if ( _currentPosX < IMG_HAVE_N_MD ) {
        if (_currentPosY+1 < MD_SIZE) {
            _currentPosY++;
        }
        else {
            _currentPosX++;
            _currentPosY = 0;
        }
    }
    else {
        //error TODO
    }

}

void DataArraysOperations::getCurrentPosXY(int *_currPosX, int *_currPosY)
{
    *_currPosX = _currentPosX;
    *_currPosY = _currentPosY;
}
