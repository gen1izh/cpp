#include "AT_common_cmd.h"
#include <QDebug>


/* ========================================================================== */
/*                            Проверка команды                                */
/* ========================================================================== */

//void at_open::evaluate(QString input, AT_manager_dbg_line *output){
//  try_cmd( input, output);
//}


/* ========================================================================== */
/*                             Общие команды                                  */
/* ========================================================================== */

void at_open::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_close::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_start::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_stop::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_reset::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_clear_stats::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_clear_buffer::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_receive::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_send::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_exchange_stop::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);

}

void at_set_configure::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_set_speed::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_set_buffer_length::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_get_state::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_get_configure::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_get_speed::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_get_buffer_length::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_get_stats::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_set_tod::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_get_tod::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}

void at_set_freq_in_mcsec::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}
void at_set_prescaler_value::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}
void at_get_freq_in_mcsec::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}
void at_get_prescaler_value::evaluate(QString input, ATMC_obCodeLine *output){
  try_cmd( input, output);
}
