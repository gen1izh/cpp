#ifndef INTERPRETER_CPP
#define INTERPRETER_CPP

#include "interpreter.h"
#include "at_common_cmd.h"
#include "at_thread.h"

AT_interpreter at_send_packet;

AT_interpreter::AT_interpreter(){

  at_open_cmd               = new at_open(1);
  at_start_cmd              = new at_start(1);
  at_close_cmd              = new at_close(1);
  at_stop_cmd               = new at_stop(1);
  at_reset_cmd              = new at_reset(1);
  at_clear_stats_cmd        = new at_clear_stats(1);
  at_clear_buffer_cmd       = new at_clear_buffer(1);
  at_receive_cmd            = new at_receive(1);
  at_send_cmd               = new at_send(1);
  at_exchange_stop_cmd      = new at_exchange_stop(1);
  at_set_configure_cmd      = new at_set_configure(1);
  at_set_speed_cmd          = new at_set_speed(1);
  at_set_buffer_length_cmd  = new at_set_buffer_length(1);
  at_get_state_cmd          = new at_get_state(1);
  at_get_configure_cmd      = new at_get_configure(1);
  at_get_speed_cmd          = new at_get_speed(1);
  at_get_buffer_length_cmd  = new at_get_buffer_length(1);
  at_get_stats_cmd          = new at_get_stats(1);

  at_set_tod_cmd          = new at_set_tod(1);
  at_get_tod_cmd          = new at_get_tod(1);

  at_set_freq_in_mcsec_cmd    = new at_set_freq_in_mcsec(1);
  at_set_prescaler_value_cmd  = new at_set_prescaler_value(1);
  at_get_freq_in_mcsec_cmd    = new at_get_freq_in_mcsec(1);
  at_get_prescaler_value_cmd  = new at_get_prescaler_value(1);

}


/* ========================================================================== */
/*                                            */
/* ========================================================================== */
void AT_interpreter::evaluate(QString input, qint32 line_num){

  ATMC_obCodeLine output;

  if ( input == "" )
    return;

  at_open_cmd->evaluate             ( input, &output );
  at_start_cmd->evaluate            ( input, &output );
  at_close_cmd->evaluate            ( input, &output );
  at_stop_cmd->evaluate             ( input, &output );
  at_reset_cmd->evaluate            ( input, &output );
  at_clear_stats_cmd->evaluate      ( input, &output );
  at_clear_buffer_cmd->evaluate     ( input, &output );
  at_receive_cmd->evaluate          ( input, &output );
  at_send_cmd->evaluate             ( input, &output );
  at_exchange_stop_cmd->evaluate    ( input, &output );
  at_set_configure_cmd->evaluate    ( input, &output );
  at_set_speed_cmd->evaluate        ( input, &output );
  at_set_buffer_length_cmd->evaluate( input, &output );
  at_get_state_cmd->evaluate        ( input, &output );
  at_get_configure_cmd->evaluate    ( input, &output );
  at_get_speed_cmd->evaluate        ( input, &output );
  at_get_buffer_length_cmd->evaluate( input, &output );
  at_get_stats_cmd->evaluate        ( input, &output );

  at_set_tod_cmd->evaluate        ( input, &output );
  at_get_tod_cmd->evaluate        ( input, &output );

  at_set_freq_in_mcsec_cmd->evaluate   ( input, &output );
  at_set_prescaler_value_cmd->evaluate ( input, &output );
  at_get_freq_in_mcsec_cmd->evaluate   ( input, &output );
  at_get_prescaler_value_cmd->evaluate ( input, &output );


  cmdCollection.toInterpret( input, &output );

  output.link_edit_line =  line_num ;
  output.num_cmd        = QString("%1").arg(virtualDebbuger.cmdSequence.size());

  virtualDebbuger.add_dbg_line(output);

}


/* ========================================================================== */
/*                                             */
/* ========================================================================== */
void AT_interpreter::paramParser(QString input, char *buf, int *size) {
  bool ok;
  /**
   * Clear spaces
   */
  QString Device = input.trimmed();
  QRegExp rx("\\(.*\\)");
  Qt::CaseSensitivity cs = Qt::CaseInsensitive;
  cs = Qt::CaseSensitive;
  rx.setCaseSensitivity(cs);

  QString dataLen = input;
  QString typeLen = input;

  //if have ( ... )
  if ( rx.indexIn(Device) != -1) {
    /**
      * Parse type len
      */
     typeLen = typeLen.remove( rx.matchedLength(),
                                    input.size() - rx.indexIn(Device) );
    typeLen.remove(0, rx.indexIn(Device) + 1 );
    typeLen.chop( 1 );
    /**
      * Parse data
      */
    dataLen = dataLen.remove( rx.indexIn(Device),
                                  rx.matchedLength() );

    if ( typeLen == "32" ) {
        *size = 4;
       buf[3] = (quint32)dataLen.toInt(&ok,0);
       buf[2] = (quint32)dataLen.toInt(&ok,0)>>8;
       buf[1] = (quint32)dataLen.toInt(&ok,0)>>16;
       buf[0] = (quint32)dataLen.toInt(&ok,0)>>24;
      }
    if ( typeLen == "16" ) {
        *size = 2;
        buf[1] = (quint32)dataLen.toInt(&ok,0);
        buf[0] = (quint32)dataLen.toInt(&ok,0)>>8;
      }
    if ( typeLen == "8" )  {
        *size = 1;
        buf[0] = (quint32)dataLen.toInt(&ok,0);
      }
  }
  else  {
      *size = 1;
      buf[0] = (quint32)input.toInt(&ok,0);
    }

  return;
}

/* ========================================================================== */
/*                                            */
/* ========================================================================== */
void AT_interpreter::devParser(QString input, int *major, int *minor) {
  bool ok;
  /**
  * Clear spaces
  */
  QString Device = input.trimmed();
  QRegExp rx("(?=)\\d");
  Qt::CaseSensitivity cs = Qt::CaseInsensitive;
  cs = Qt::CaseSensitive;
  rx.setCaseSensitivity(cs);
  if ( rx.indexIn(Device) != -1) {
    // Returns a substring that contains the n rightmost characters of the string.
    *minor  = Device.right(rx.matchedLength()).toInt(&ok,10);
    // Removes n characters from the end of the string.
    Device.chop( rx.matchedLength() );
    *major = devMapNames[Device];
  }

  return;
}

/* ========================================================================== */
/*                                            */
/* ========================================================================== */
int get_ret_data_size(int opcode, int dev_type){
  if (OPEN_CMD_OP == opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (CLOSE_CMD_OP == opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (START_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (STOP_CMD_OP  ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (RESET_CMD_OP  ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (CLEAR_STATS_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (CLEAR_BUFFER_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (RECEIVE_CMD_OP  ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (SEND_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (EXCHANGE_STOP_CMD_OP==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (SET_CONFIGURE_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (SET_SPEED_CMD_OP  ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (SET_BUFFER_LENGTH_CMD_OP==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (GET_STATE_CMD_OP==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (GET_CONFIGURE_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (GET_SPEED_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (GET_BUFFER_LENGTH_CMD_OP==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);

  if (GET_STATS_CMD_OP ==opcode) {
    if (dev_type == 1)return (CONST_DATA_SIZE + 40);
    if (dev_type == 4)return (CONST_DATA_SIZE + 28);
    if (dev_type == 5)return (CONST_DATA_SIZE + 44);
    }

  if (SET_TOD_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 4);
  if (GET_TOD_CMD_OP ==opcode)
    if ((dev_type >= 1)&&(dev_type <=5))return (CONST_DATA_SIZE + 8);
  return 0;
}

/* ========================================================================== */
/*                         Interpret command to object code                   */
/* ========================================================================== */
void AT_interpreter::try_cmd(QString input, ATMC_obCodeLine *output){

  bool          ok;
  int           major, minor;
  QStringList   params;
  int           kol_param;
  char          buf[256];
  int           size;


  /**
    * String for translate to obCodeLine
    */
  QStringList tmpCodeLineList = input.split(QRegExp("\\s+|,"));

  /**
    * Delete empty string
    */
  for ( int i = 0; i < tmpCodeLineList.size(); i++ )
    if ( tmpCodeLineList[i] == "" ) {
      tmpCodeLineList.removeAt(i);
      i--;
    }


  /**
    * If command was found  ...
    */
  if ( tmpCodeLineList.size() > 1 ) // check error
  if ( (tmpCodeLineList[0] == at_interpret_cmd_name) ||
       (tmpCodeLineList[1] == at_interpret_cmd_name)) {

  if ( tmpCodeLineList[1] == at_interpret_cmd_name ){
    output->label = tmpCodeLineList[0];
    devParser(tmpCodeLineList[2], &major, &minor);
    for ( int i = 3; i < tmpCodeLineList.size(); i++ )
      params.append(tmpCodeLineList.at(i));
    }
  else if ( tmpCodeLineList[0] == at_interpret_cmd_name ) {
      devParser(tmpCodeLineList[1], &major, &minor);
      for ( int i = 2; i < tmpCodeLineList.size(); i++ )
        params.append(tmpCodeLineList.at(i));
    }

  /**
    * Analyze and fill params of packet
    */
  int bufFillCnt = 0;
  for ( int i = 0; i < params.size(); i++ ) {
    paramParser( params[i], (char *)&buf[0], &size );
    qDebug() << "size=" << size;
    for ( int j = 0; j < size; j++ ) {
      output->pack.pack.data[bufFillCnt] = buf[j];
      bufFillCnt++;
    }
  }

  output->pack.pack.data_size = bufFillCnt;

  output->pack.set_cmd_type  (  at_interpret_cmd_op_type  );
  output->pack.set_crc16     (  output->pack.crc16( output->pack.to_rawData(),
                               CONST_DATA_SIZE + at_interpret_cmd_data_size
                               - CONST_CRC16_BYTE_SIZE )     );
  output->pack.set_data_size (  bufFillCnt );
  output->pack.set_dev_minor (  minor );
  output->pack.set_dev_type  (  major  );
  output->pack.set_flag_error(  0x0  );
  output->pack.set_operation (  at_interpret_cmd_op );



//       if (at_interpret_cmd_name==CLEAR_BUFFER_CMD_NAME)
//         output->pack.pack.data[0] = (quint8)param[0].toInt(&ok,0);

//       if (at_interpret_cmd_name==RECEIVE_CMD_NAME){
//         output->pack.pack.data[3] = (quint32)param[0].toInt(&ok,0);
//         output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0)>>8;
//         output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>16;
//         output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>24;
//         }


//       if (at_interpret_cmd_name==SEND_CMD_NAME) {
//           output->pack.pack.data[3] = (quint32)param[0].toInt(&ok,0);
//           output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0)>>8;
//           output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>16;
//           output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>24;
//           output->pack.pack.data[4] = (quint8)param[1].toInt(&ok,0);
//           output->pack.pack.data[5] = (quint8)param[2].toInt(&ok,0);
//           if (minor == 1) {
//               output->filename_data = param[3];
//               output->size_transfer =(quint32)param[0].toInt(&ok,0);
//             }
//           if (minor == 2) {
//               output->filename_data = param[3];
//               output->size_transfer =(quint32)param[0].toInt(&ok,0);
//             }
//           if (minor == 3) {
//               output->filename_data = param[3];
//               output->size_transfer =(quint32)param[0].toInt(&ok,0);
//             }
//           if (minor == 4) {
//               output->filename_data = param[3];
//               output->size_transfer =(quint32)param[0].toInt(&ok,0);
//             }
//         }

//       if (at_interpret_cmd_name==SET_CONFIGURE_CMD_NAME){
//         output->pack.pack.data[3] = (quint32)param[0].toInt(&ok,0);
//         output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0)>>8;
//         output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>16;
//         output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>24;
//         }

//       if (at_interpret_cmd_name==SET_SPEED_CMD_NAME){
//           output->pack.pack.data[3] = (quint32)param[0].toInt(&ok,0);
//           output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0)>>8;
//           output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>16;
//           output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>24;
//           FTDIDesciptorTable.SetSpeed( minor, major,(quint32)param[0].toInt(&ok,0) );
//         }

//       if (at_interpret_cmd_name==SET_BUFFER_LENGTH_CMD_NAME){
//         output->pack.pack.data[0] = (quint8)param[0].toInt(&ok,0);
//         output->pack.pack.data[4] = (quint32)param[1].toInt(&ok,0);
//         output->pack.pack.data[3] = (quint32)param[1].toInt(&ok,0)>>8;
//         output->pack.pack.data[2] = (quint32)param[1].toInt(&ok,0)>>16;
//         output->pack.pack.data[1] = (quint32)param[1].toInt(&ok,0)>>24;
//         }

//       if (at_interpret_cmd_name==SET_TOD_CMD_NAME){

//         output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0);
//         output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>8;
//         output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>16;

//         output->pack.pack.data[4] = (quint32)param[1].toInt(&ok,0);
//         output->pack.pack.data[3] = (quint32)param[1].toInt(&ok,0)>>8;

//         output->pack.pack.data[5] = (quint32)param[2].toInt(&ok,0);

//         output->pack.pack.data[6] = (quint32)param[3].toInt(&ok,0);
//         qDebug()<<"param[3] = "<<param[3]<<"  "<<(quint32)param[3].toInt(&ok,0);
//         output->pack.pack.data[7] = (quint32)param[4].toInt(&ok,0);

//         }

//       if (at_interpret_cmd_name==SET_FREQ_IN_MCSEC_CMD_NAME){
//           output->pack.pack.data[3] = (quint32)param[0].toInt(&ok,0);
//           output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0)>>8;
//           output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>16;
//           output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>24;
//         }


//       if (at_interpret_cmd_name==SET_PRESCALER_VALUE_CMD_NAME){
//           output->pack.pack.data[3] = (quint32)param[0].toInt(&ok,0);
//           output->pack.pack.data[2] = (quint32)param[0].toInt(&ok,0)>>8;
//           output->pack.pack.data[1] = (quint32)param[0].toInt(&ok,0)>>16;
//           output->pack.pack.data[0] = (quint32)param[0].toInt(&ok,0)>>24;
//         }

//       if (at_interpret_cmd_name==GET_BUFFER_LENGTH_CMD_NAME)
//         output->pack.pack.data[0] = (quint8)param[0].toInt(&ok,0);

       output->cmd_name = at_interpret_cmd_name;

       output->pack.to_rawData();

       for ( int i = 0; i< CONST_DATA_SIZE + bufFillCnt; i++){
           output->dump += QString("%1").arg(output->pack.rawData[i],2,16,QChar('0')).toUpper()+" ";
         }

       output->cmd_type= "PKT";
       output->ret_buf_size = get_ret_data_size(at_interpret_cmd_op, major);
    }
}

#endif // INTERPRETER_CPP
