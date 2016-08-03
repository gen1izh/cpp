#ifndef AT_COMMON_COMMANDS_H
#define AT_COMMON_COMMANDS_H
#include <QRegExp>
#include <QString>
#include "at_debuger.h"
#include "interpreter.h"
#include "macro.h"
#include "prt\cmd_packet.h"


/**
 * Command OPEN
 */
class at_open: public AT_interpreter{
public:
  at_open(int):AT_interpreter(1){
    at_interpret_cmd_name       =   OPEN_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x01;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command CLOSE
 */
class at_close: public AT_interpreter{
public:
  at_close(int):AT_interpreter(1){
    at_interpret_cmd_name       =   CLOSE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x02;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command START
 */
class at_start: public AT_interpreter{
public:
  at_start(int):AT_interpreter(1){
    at_interpret_cmd_name       =   START_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x03;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command STOP
 */
class at_stop: public AT_interpreter{
public:
  at_stop(int):AT_interpreter(1){
    at_interpret_cmd_name       =   STOP_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x04;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command RESET
 */
class at_reset: public AT_interpreter{
public:
  at_reset(int):AT_interpreter(1){
    at_interpret_cmd_name       =   RESET_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x05;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command CLEAR_STATS
 */
class at_clear_stats: public AT_interpreter{
public:
  at_clear_stats(int):AT_interpreter(1){
    at_interpret_cmd_name       =   CLEAR_STATS_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x06;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command CLEAR_BUFFER
 */
class at_clear_buffer: public AT_interpreter{
public:
  at_clear_buffer(int):AT_interpreter(1){
    at_interpret_cmd_name       =   CLEAR_BUFFER_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x07;
    at_interpret_cmd_data_size  =   0x1;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command RECEIVE
 */
class at_receive: public AT_interpreter{
public:
  at_receive(int):AT_interpreter(1){
    at_interpret_cmd_name       =   RECEIVE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x08;
    at_interpret_cmd_data_size  =   0x4;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command SEND
 */
class at_send: public AT_interpreter{
public:
  at_send(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SEND_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x09;
    at_interpret_cmd_data_size  =   0x6;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command EXCHANGE_STOP
 */
class at_exchange_stop: public AT_interpreter{
public:
  at_exchange_stop(int):AT_interpreter(1){
    at_interpret_cmd_name       =   EXCHANGE_STOP_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x0A;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command SET_CONFIGURE
 */
class at_set_configure: public AT_interpreter{
public:
  at_set_configure(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SET_CONFIGURE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x20;
    at_interpret_cmd_data_size  =   0x4;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command SET_SPEED
 */
class at_set_speed: public AT_interpreter{
public:
  at_set_speed(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SET_SPEED_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x21;
    at_interpret_cmd_data_size  =   0x4;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command SET_BUFFER_LENGTH
 */
class at_set_buffer_length: public AT_interpreter{
public:
  at_set_buffer_length(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SET_BUFFER_LENGTH_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x22;
    at_interpret_cmd_data_size  =   0x5;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command GET_STATE
 */
class at_get_state: public AT_interpreter{
public:
  at_get_state(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_STATE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x40;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command GET_CONFIGURE
 */
class at_get_configure: public AT_interpreter{
public:
  at_get_configure(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_CONFIGURE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x41;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command GET_SPEED
 */
class at_get_speed: public AT_interpreter{
public:
  at_get_speed(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_SPEED_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x42;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command GET_BUFFER_LEN
 */
class at_get_buffer_length: public AT_interpreter{
public:
  at_get_buffer_length(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_BUFFER_LENGTH_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x43;
    at_interpret_cmd_data_size  =   0x1;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command GET_STATS
 */
class at_get_stats: public AT_interpreter{
public:
  at_get_stats(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_STATS_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x44;
    at_interpret_cmd_data_size  =   0x0;

    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 40;

  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command SET_TOD
 */
class at_set_tod: public AT_interpreter{
public:
  at_set_tod(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SET_TOD_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x28;
    at_interpret_cmd_data_size  =   0x8;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 4;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command GET_TOD
 */
class at_get_tod: public AT_interpreter{
public:
  at_get_tod(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_TOD_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x46;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 8;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command SET_FREQ_IN_MCSEC
 */
class at_set_freq_in_mcsec: public AT_interpreter{
public:
  at_set_freq_in_mcsec(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SET_FREQ_IN_MCSEC_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x21;
    at_interpret_cmd_data_size  =   0x4;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 8;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command SET_PRESCALER_VALUE
 */
class at_set_prescaler_value: public AT_interpreter{
public:
  at_set_prescaler_value(int):AT_interpreter(1){
    at_interpret_cmd_name       =   SET_PRESCALER_VALUE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x24;
    at_interpret_cmd_data_size  =   0x4;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 8;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};


/**
 * Command GET_FREQ_IN_MCSEC
 */
class at_get_freq_in_mcsec: public AT_interpreter{
public:
  at_get_freq_in_mcsec(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_FREQ_IN_MCSEC_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x42;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 8;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};

/**
 * Command GET_PRESCALER_VALUE
 */
class at_get_prescaler_value: public AT_interpreter{
public:
  at_get_prescaler_value(int):AT_interpreter(1){
    at_interpret_cmd_name       =   GET_PRESCALER_VALUE_CMD_NAME;
    at_interpret_cmd_op_type    =   WRITE_OPERATION;
    at_interpret_cmd_op         =   0x49;
    at_interpret_cmd_data_size  =   0x0;
    at_interpret_cmd_ret_data_size = CONST_DATA_SIZE + 8;
  }
  void evaluate(QString input, ATMC_obCodeLine *output);
};
#endif // AT_COMMON_COMMANDS_H
