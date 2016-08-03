#ifndef MACRO_H
#define MACRO_H
#include <QtGui>
#include "interpreter.h"


//typedef struct{
//  int             type_dev;
//  int             opcode;
//  AT_interpreter *cmd;
//}send_packet_s;

/*
 *  Константы для регулярных выражений
 */

#define AT_START_TXT      "START"
#define AT_CLOSE_TXT      "CLOSE"

/* ========================================================================== */
/*                               Вид команды                                  */
/* ========================================================================== */

#define READ_OPERATION                                              0x1
#define WRITE_OPERATION                                             0x0

/* ========================================================================== */
/*                           Коды операции команд                             */
/* ========================================================================== */

#define OPEN_CMD_OP                                                 0x01
#define CLOSE_CMD_OP                                                0x02
#define START_CMD_OP                                                0x03
#define STOP_CMD_OP                                                 0x04
#define RESET_CMD_OP                                                0x05
#define CLEAR_STATS_CMD_OP                                          0x06
#define CLEAR_BUFFER_CMD_OP                                         0x07
#define RECEIVE_CMD_OP                                              0x08
#define SEND_CMD_OP                                                 0x09
#define EXCHANGE_STOP_CMD_OP                                        0x0A
#define SET_CONFIGURE_CMD_OP                                        0x20
#define SET_SPEED_CMD_OP                                            0x21
#define SET_BUFFER_LENGTH_CMD_OP                                    0x22
#define GET_STATE_CMD_OP                                            0x40
#define GET_CONFIGURE_CMD_OP                                        0x41
#define GET_SPEED_CMD_OP                                            0x42
#define GET_BUFFER_LENGTH_CMD_OP                                    0x43
#define GET_STATS_CMD_OP                                            0x44
#define SET_TOD_CMD_OP                                              0x28
#define GET_TOD_CMD_OP                                              0x46
#define SET_FREQ_IN_MCSEC_CMD_OP                                    0x21
#define GET_FREQ_IN_MCSEC_CMD_OP                                    0x42
#define SET_PRESCALER_VALUE_CMD_OP                                  0x24
#define GET_PRESCALER_VALUE_CMD_OP                                  0x49


/* ========================================================================== */
/*                       Названия операции команд                             */
/* ========================================================================== */

#define OPEN_CMD_NAME                                                 "OPEN"
#define CLOSE_CMD_NAME                                                "CLOSE"
#define START_CMD_NAME                                                "START"
#define STOP_CMD_NAME                                                 "STOP"
#define RESET_CMD_NAME                                                "RESET"
#define CLEAR_STATS_CMD_NAME                                          "CLEAR_STATS"
#define CLEAR_BUFFER_CMD_NAME                                         "CLEAR_BUFFER"
#define RECEIVE_CMD_NAME                                              "RECEIVE"
#define SEND_CMD_NAME                                                 "SEND"
#define EXCHANGE_STOP_CMD_NAME                                        "EXCHANGE_STOP"
#define SET_CONFIGURE_CMD_NAME                                        "SET_CONFIGURE"
#define SET_SPEED_CMD_NAME                                            "SET_SPEED"
#define SET_BUFFER_LENGTH_CMD_NAME                                    "SET_BUFFER_LENGTH"
#define GET_STATE_CMD_NAME                                            "GET_STATE"
#define GET_CONFIGURE_CMD_NAME                                        "GET_CONFIGURE"
#define GET_SPEED_CMD_NAME                                            "GET_SPEED"
#define GET_BUFFER_LENGTH_CMD_NAME                                    "GET_BUFFER_LENGTH"
#define GET_STATS_CMD_NAME                                            "GET_STATS"

#define SET_TOD_CMD_NAME                                            "SET_TOD"
#define GET_TOD_CMD_NAME                                            "GET_TOD"

#define SET_FREQ_IN_MCSEC_CMD_NAME                                  "SET_FREQ_IN_MCSEC"
#define GET_FREQ_IN_MCSEC_CMD_NAME                                  "GET_FREQ_IN_MCSEC"
#define SET_PRESCALER_VALUE_CMD_NAME                                "SET_PRESCALER_VALUE"
#define GET_PRESCALER_VALUE_CMD_NAME                                "GET_PRESCALER_VALUE"

/* ========================================================================== */
/*                          Размеры параметров команд                         */
/* ========================================================================== */

#define CONST_DATA_SIZE                                         0x5  // код операции 1 байт,
                                                                     // тип устройства 1 байт,
                                                                     // бай на размер данных еще
                                                                     // crc16
#define CONST_CRC16_BYTE_SIZE                                   0x2

#define CLOSE_CMD_DATA_SIZE                                     0x0
#define START_CMD_DATA_SIZE                                     0x0
#define RESET_CMD_DATA_SIZE                                     0x0
#define STOP_CMD_DATA_SIZE                                      0x0

#define extract_dataword(packet_data, i) \
       ( (quint32) packet_data[i]   << 24 ) \
     | ( (quint32) packet_data[i+1] << 16 ) \
     | ( (quint32) packet_data[i+2] << 8  ) \
     |   (quint32) packet_data[i+3];

#define extract_quadroword(packet_data, i) \
        ( (quint64) packet_data[i]    << 56  ) \
      | ( (quint64) packet_data[i+1]  << 48  ) \
      | ( (quint64) packet_data[i+2]  << 40  ) \
      | (  (quint64) packet_data[i+3] << 32  ) \
      | ( (quint64) packet_data[i+4]  << 24  ) \
      | ( (quint64) packet_data[i+5]  << 16  ) \
      | ( (quint64) packet_data[i+6]  << 8   ) \
      |   (quint64) packet_data[i+7];

#define extract_word(packet_data, i) \
       ( (quint16) packet_data[i]   << 8 ) \
     | ( (quint16) packet_data[i+1] )

#define construct_dataword(packet_data, i, word) \
  packet_data[i]   = (quint8) ( 0xff & (word >> 24) ); \
  packet_data[i+1] = (quint8) ( 0xff & (word >> 16) ); \
  packet_data[i+2] = (quint8) ( 0xff & (word >> 8) ); \
  packet_data[i+3] = (quint8) ( 0xff & (word)  );

#define construct_word(packet_data, i, word) \
  packet_data[i] =   (quint8) ( 0xff & (word >> 8) ); \
  packet_data[i+1] = (quint8) ( 0xff & (word)  );


typedef enum {
  AT_UNDEFINED_DEVICE       =  0,
  AT_DEVICE_TYPE_NUART      =  1,
  AT_DEVICE_TYPE_OCCAN      =  2,
  AT_DEVICE_TYPE_NSPI       =  3,
  AT_DEVICE_TYPE_GPIO       =  4,
  AT_DEVICE_TYPE_NBTS       =  5,
  AT_DEVICE_TYPE_NTIMER     =  6,
  AT_DEVICE_TYPE_MCTRL      =  10
} at_device_type;



#endif // MACRO_H
