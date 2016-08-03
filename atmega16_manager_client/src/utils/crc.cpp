#include <errno.h>
#include "utils/crc.h"
#include "utils/crcmodel.h"

compute_crc_16_32::compute_crc_16_32(){

}

compute_crc_16_32::~compute_crc_16_32(){

}

/* ========================================================================== */
/*                         Функции рассчета crc16                             */
/* ========================================================================== */

quint16 compute_crc_16_32::compute_crc16(
  quint8     *buf,
  qint32   buf_size
)
{
    quint16  crc = compute_crc16_with_init(buf, buf_size, CRC16_INIT);

    return   compute_crc16_finalize(crc);
}//compute_crc16



quint16 compute_crc_16_32::compute_crc16_with_init(
  quint8        *buf,
  qint32       buf_size,
  quint16      init_crc
)
{
    cm_t   cm;
    p_cm_t p_cm = &cm;

    p_cm->cm_width = 16;
    p_cm->cm_poly  = CRC16_POLY;
    p_cm->cm_init  = init_crc;
    p_cm->cm_refin = CRC16_REFIN;
    p_cm->cm_refot = CRC16_REFOUT;
    p_cm->cm_xorot = CRC16_XOROUT;

    cm_ini(p_cm);
    cm_blk(p_cm, (quint8 *)buf, buf_size);

    return p_cm->cm_reg & 0x0FFFF;
}//compute_crc16_with_init


quint16 compute_crc_16_32::compute_crc16_finalize(
  quint16 crc
)
{
    cm_t    cm;
    p_cm_t  p_cm = &cm;

    p_cm->cm_width = 16;
    p_cm->cm_poly  = CRC16_POLY;
    p_cm->cm_init  = crc;
    p_cm->cm_refin = CRC16_REFIN;
    p_cm->cm_refot = CRC16_REFOUT;
    p_cm->cm_xorot = CRC16_XOROUT;

    cm_ini(p_cm);

    return cm_crc(p_cm) & 0x0FFFF;
}//compute_crc16_finalize



/* ========================================================================== */
/*                         Функции рассчета crc32                             */
/* ========================================================================== */

quint32 compute_crc_16_32::compute_crc32(
  quint8    *buf,
  qint32   buf_size
)
{
    quint32   crc = compute_crc32_with_init(buf, buf_size, CRC32_INIT);

    return  compute_crc32_finalize(crc);
}//compute_crc32


quint32 compute_crc_16_32::compute_crc32_with_init(
  quint8 *buf,
  qint32     buf_size,
  quint32    init_crc)
{
    cm_t    cm;
    p_cm_t  p_cm = &cm;

    p_cm->cm_width = 32;
    p_cm->cm_poly  = CRC32_POLY;
    p_cm->cm_init  = init_crc;
    p_cm->cm_refin = CRC32_REFIN;
    p_cm->cm_refot = CRC32_REFOUT;
    p_cm->cm_xorot = CRC32_XOROUT;

    cm_ini(p_cm);
    cm_blk(p_cm, buf, buf_size);

    return p_cm->cm_reg & 0x0FFFFFFFF;
}//compute_crc32_with_init


quint32 compute_crc_16_32::compute_crc32_finalize(
  quint32 crc
)
{
    cm_t    cm;
    p_cm_t  p_cm = &cm;

    p_cm->cm_width = 32;
    p_cm->cm_poly  = CRC32_POLY;
    p_cm->cm_init  = crc;
    p_cm->cm_refin = CRC32_REFIN;
    p_cm->cm_refot = CRC32_REFOUT;
    p_cm->cm_xorot = CRC32_XOROUT;

    cm_ini(p_cm);

    return cm_crc(p_cm) & 0x0FFFFFFFF;
}//compute_crc32_finalize



