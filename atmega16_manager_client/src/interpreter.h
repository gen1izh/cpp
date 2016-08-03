#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <QString>
#include <QRegExp>
#include "at_manager_client.h"
#include "at_debuger.h"
#include "at_service_cmd.h"
#include "macro.h"


bool parse(QString input);
void device_type_get(QString input, int *major, int *minor);
void label_get(QString input);



//class at_service_cmds;

 /*
  * Ядро интерпретатора
  */
class AT_interpreter{
public:
    AT_interpreter();
    AT_interpreter(int){}
    void evaluate(QString input, qint32 line_num);
    void try_cmd(QString input, ATMC_obCodeLine *output);
    void devParser(QString input, int *major, int *minor);
    void paramParser(QString input, char *buf, int *size);

    QString at_interpret_cmd_name;
    bool    at_interpret_cmd_op_type;
    quint8  at_interpret_cmd_op;
    quint8  at_interpret_cmd_data_size;
    quint8  at_interpret_cmd_ret_data_size;
    /*
     * Формирование output
     */
    virtual void evaluate(QString input, ATMC_obCodeLine *output){}

private:
    AT_interpreter *at_open_cmd;
    AT_interpreter *at_close_cmd;
    AT_interpreter *at_start_cmd;
    AT_interpreter *at_stop_cmd;
    AT_interpreter *at_reset_cmd;
    AT_interpreter *at_clear_stats_cmd;
    AT_interpreter *at_clear_buffer_cmd;
    AT_interpreter *at_receive_cmd;
    AT_interpreter *at_send_cmd;
    AT_interpreter *at_exchange_stop_cmd;
    AT_interpreter *at_set_configure_cmd;
    AT_interpreter *at_set_speed_cmd;
    AT_interpreter *at_set_buffer_length_cmd;
    AT_interpreter *at_get_state_cmd;
    AT_interpreter *at_get_configure_cmd;
    AT_interpreter *at_get_speed_cmd;
    AT_interpreter *at_get_buffer_length_cmd;
    AT_interpreter *at_get_stats_cmd;

    AT_interpreter *at_set_tod_cmd;
    AT_interpreter *at_get_tod_cmd;

    AT_interpreter *at_set_freq_in_mcsec_cmd;
    AT_interpreter *at_set_prescaler_value_cmd;
    AT_interpreter *at_get_freq_in_mcsec_cmd;
    AT_interpreter *at_get_prescaler_value_cmd;

    //ATMC_cmdSystem *at_service_cmd;
};

extern AT_interpreter at_send_packet;

#endif // INTERPRETER_H
