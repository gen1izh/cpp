#include "cmd_packet.h"
#include "macro.h"
#include "utils/crc.h"
#include <Windows.h>
#include "at_ftdi_module.h"


at_cmd_packet cmd_packet;
at_cmd_packet answer_packet;

at_cmd_packet::at_cmd_packet(){
}

at_cmd_packet::~at_cmd_packet(){
}
/*
 *  Copies src packet to the dest packet.
 */
void at_cmd_packet::clear()
{
  memset( (ATMC_cmdPacket *)&pack, 0, sizeof( ATMC_cmdPacket ) );
}

/*
 *  Converts received raw data to the C-structure.
 */
void at_cmd_packet::to_packet(
  quint8                *raw_data_packet
)
{
  pack.DevType   =  raw_data_packet[0] >> 4;
  pack.DevMinor  =  (raw_data_packet[0] & 0x0f ) - 1 ;

  pack.err_flag = ( raw_data_packet[1] >> 7 );
  pack.cmd_type   = ( raw_data_packet[1]& 0x40 ) >> 6;
  pack.operation  =  raw_data_packet[1] & 0x7f;

  pack.data_size  = raw_data_packet[2];

  for (int  i = 0; i < pack.data_size ; i++ )
    pack.data[i]  = raw_data_packet[3 + i];

  pack.crc16 = (quint16)raw_data_packet[3 + pack.data_size];
}

/*
 *  Converts packet's C-structure to the byte series.
 */
quint8 *at_cmd_packet::to_rawData()
{
  int                         i;
  quint8                      packet_data[2]; 
  compute_crc_16_32           crc16;

  rawData[0] = ( ( (quint8)pack.DevType << 4 ) | ( (quint8)(pack.DevMinor) & 0x0f ) );

  rawData[1] = ( pack.err_flag ? (quint8)0x80 : (quint8)0 )
                        | ( pack.cmd_type   ? (quint8)0x40 : (quint8)0 )
                        | ( (quint8)pack.operation & 0x7f );

  rawData[2] = pack.data_size;

  for ( i = 0; i < pack.data_size ; i++ )
    rawData[i+3] = pack.data[i];


  construct_word(packet_data, 0, crc16.compute_crc16(rawData, (qint32)(3 + pack.data_size) ));

  rawData[3 + pack.data_size] = (quint16)packet_data[0];
  rawData[4 + pack.data_size] = (quint16)packet_data[1];

  return rawData;
}

/*
 * � ассчет CRC16.
 */
quint16 at_cmd_packet::crc16(
  quint8 *buf,
  quint16 buf_size
)
{
  compute_crc_16_32 crc16;
  return crc16.compute_crc16(buf, buf_size);
}

/*
 * � ассчет CRC32
 */
quint32 at_cmd_packet::crc32(
  quint8     *buf,
  qint32     buf_size
)
{
  compute_crc_16_32 crc32;
  return crc32.compute_crc32(buf, buf_size);
}


/*
 * Формирования командного пакета
 */
void at_cmd_packet::set_dev_minor(quint8 dev_minor){
    pack.DevMinor = dev_minor;
}

void at_cmd_packet::set_dev_type(quint8 dev_type){
    pack.DevType = dev_type;
}

void at_cmd_packet::set_operation(quint8 op){
    pack.operation = op;
}

void at_cmd_packet::set_flag_error(quint8 flag_error){
    pack.err_flag = flag_error;
}

void at_cmd_packet::set_cmd_type(quint8 command_type){
    pack.cmd_type = command_type;
}

void at_cmd_packet::set_data_size(quint8 data_size){
    pack.data_size = data_size;
}

void at_cmd_packet::set_crc16(quint16 crc16){
    pack.crc16 = crc16;
}

/*
 * Получение параметров команды
 */
void at_cmd_packet::get_dev_minor(quint8 dev_minor){

}

void at_cmd_packet::get_dev_type(quint8 dev_type){

}


void at_cmd_packet::get_operation(quint8 op){

}

void at_cmd_packet::get_flag_error(quint8 flag_error){

}

void at_cmd_packet::get_cmd_type(quint8 command_type){

}

void at_cmd_packet::get_data_size(quint8 data_size){

}

ATMC_cmdPacket at_cmd_packet::get_pack(){
  return pack;
}



