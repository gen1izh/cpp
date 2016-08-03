#ifndef __CRC__H__
#define __CRC__H__
 
#include <QtGui>
 
#define  CRC16_POLY       0x08005
#define  CRC16_INIT       0x0FFFF
#define  CRC16_REFIN      TRUE
#define  CRC16_REFOUT     TRUE
#define  CRC16_XOROUT     0
 
#define  CRC32_POLY       0x004C11DB7
#define  CRC32_INIT       0x0FFFFFFFF
#define  CRC32_REFIN      TRUE
#define  CRC32_REFOUT     TRUE
#define  CRC32_XOROUT     0x0FFFFFFFF
 
 
class compute_crc_16_32 {
 
public:
    compute_crc_16_32();
    ~compute_crc_16_32();
 
    quint16 compute_crc16(quint8 *buf, qint32 buf_size);
    quint16 compute_crc16_with_init(quint8 *buf, qint32 buf_size, quint16 init_crc);
    quint16 compute_crc16_finalize(quint16  crc);
 
    quint32 compute_crc32(quint8 *buf, qint32 buf_size);
    quint32 compute_crc32_with_init(quint8 *buf, qint32 buf_size, quint32 init_crc);
    quint32 compute_crc32_finalize(quint32  crc);
 
};
 
#endif /* __CRC__H__ */
