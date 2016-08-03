
#include "prt/answerExtractor.h"
#include "at_registers.h"
#include "at_report.h"
#include "macro.h"
#include "at_thread.h"
/* ========================================================================== */
/*                                                                            */
/* ========================================================================== */


 /*
  * Извлекаем из ответа состояние устройства
  */
void ATMC_answerExtractor::answerPacketStateExtract(QString cmd_name) {
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,16);
  report.DevType   = QString::number(dev_type,16);
  report.is_ok      = true;

  Report->AddItem( report );

  quint32 state = extract_dataword(buf, 3);

  if (dev_type == 1)
    switch (dev_minor){
      case 1:
        set_reg_value("UART1_SuR", state);
        break;
      case 2:
        set_reg_value("UART2_SuR", state);
        break;
      case 3:
        set_reg_value("UART3_SuR", state);
        break;
      case 4:
        set_reg_value("UART4_SuR", state);
        break;
      default:
        break;
      };

  if (dev_type == 4)
    set_reg_value("BTS_SuR", state);

  if (dev_type == 5)
    switch (dev_minor){
      case 1:
        set_reg_value("TIMER1_SuR", state);
        break;
      case 2:
        set_reg_value("TIMER2_SuR", state);
        break;
      case 3:
        set_reg_value("TIMER3_SuR", state);
        break;
      case 4:
        set_reg_value("TIMER4_SuR", state);
        break;
      case 5:
        set_reg_value("TIMER5_SuR", state);
        break;
      case 6:
        set_reg_value("TIMER6_SuR", state);
        break;
      case 7:
        set_reg_value("TIMER7_SuR", state);
        break;
      case 8:
        set_reg_value("TIMER8_SuR", state);
        break;
      case 9:
        set_reg_value("TIMER9_SuR", state);
        break;
      case 10:
        set_reg_value("TIMER10_SuR", state);
        break;
      case 11:
        set_reg_value("TIMER11_SuR", state);
        break;
      case 12:
        set_reg_value("TIMER12_SuR", state);
        break;
      case 13:
        set_reg_value("TIMER13_SuR", state);
        break;
      case 14:
        set_reg_value("TIMER14_SuR", state);
        break;
      default:
        break;
      };
}



/*
 * Извлекаем из ответа конфигурацию устройства
 */
void ATMC_answerExtractor::answerPacketConfigureExtract(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( unsigned int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,16);
  report.DevType   = QString::number(dev_type,16);
  report.is_ok      = true;

  Report->AddItem( report );

  quint32 state = extract_dataword(buf, 3);

  if (dev_type == 1)
    switch (dev_minor){
      case 1:
        set_reg_value("UART1_CR", state);
        break;
      case 2:
        set_reg_value("UART2_CR", state);
        break;
      case 3:
        set_reg_value("UART3_CR", state);
        break;
      case 4:
        set_reg_value("UART4_CR", state);
        break;
      default:
        break;
      };

  if (dev_type == 4)
    set_reg_value("BTS_CR", state);


  if (dev_type == 1)
    switch (dev_minor){
      case 1:
        set_reg_value("TIMER1_CR", state);
        break;
      case 2:
        set_reg_value("TIMER2_CR", state);
        break;
      case 3:
        set_reg_value("TIMER3_CR", state);
        break;
      case 4:
        set_reg_value("TIMER4_CR", state);
        break;
      case 5:
        set_reg_value("TIMER5_CR", state);
        break;
      case 6:
        set_reg_value("TIMER6_CR", state);
        break;
      case 7:
        set_reg_value("TIMER7_CR", state);
        break;
      case 8:
        set_reg_value("TIMER8_CR", state);
        break;
      case 9:
        set_reg_value("TIMER9_CR", state);
        break;
      case 10:
        set_reg_value("TIMER10_CR", state);
        break;
      case 11:
        set_reg_value("TIMER11_CR", state);
        break;
      case 12:
        set_reg_value("TIMER12_CR", state);
        break;
      case 13:
        set_reg_value("TIMER13_CR", state);
        break;
      case 14:
        set_reg_value("TIMER14_CR", state);
        break;
      default:
        break;
      };
}

/*
 * Извлекаем из ответа скорость приема\передачи устройства
 */
void ATMC_answerExtractor::answerPacketSpeedExtract(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,10);
  report.DevType   = QString::number(dev_type,10);
  report.is_ok      = true;

  Report->AddItem( report );

  quint32 state = extract_dataword(buf, 3);

  if (dev_type == 1)
    switch (dev_minor){
      case 1:
        set_reg_value("UART1_SPEED", state);
        break;
      case 2:
        set_reg_value("UART2_SPEED", state);
        break;
      case 3:
        set_reg_value("UART3_SPEED", state);
        break;
      case 4:
        set_reg_value("UART4_SPEED", state);
        break;
      default:
        break;
      };

   if (dev_type == 5)
  switch (dev_minor){
    case 1:
      set_reg_value("TIMER1_INTERVAL", state);
      break;
    case 2:
      set_reg_value("TIMER2_INTERVAL", state);
      break;
    case 3:
      set_reg_value("TIMER3_INTERVAL", state);
      break;
    case 4:
      set_reg_value("TIMER4_INTERVAL", state);
      break;
    case 5:
      set_reg_value("TIMER5_INTERVAL", state);
      break;
    case 6:
      set_reg_value("TIMER6_INTERVAL", state);
      break;
    case 7:
      set_reg_value("TIMER7_INTERVAL", state);
      break;
    case 8:
      set_reg_value("TIMER8_INTERVAL", state);
      break;
    case 9:
      set_reg_value("TIMER9_INTERVAL", state);
      break;
    case 10:
      set_reg_value("TIMER10_INTERVAL", state);
      break;
    case 11:
      set_reg_value("TIMER11_INTERVAL", state);
      break;
    case 12:
      set_reg_value("TIMER12_INTERVAL", state);
      break;
    case 13:
      set_reg_value("TIMER13_INTERVAL", state);
      break;
    case 14:
      set_reg_value("TIMER14_INTERVAL", state);
      break;
    default:
      break;
    };
}


/*
 * Извлекаем из ответа длину буфера устройства
 */
void ATMC_answerExtractor::answerPacketBufLengthExtract(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,16);
  report.DevType   = QString::number(dev_type,16);
  report.is_ok      = true;

  Report->AddItem( report );

  quint32 state = extract_dataword(buf, 3);

  if (dev_type == 1)
    switch (dev_minor){
      case 1:
        if (buf_type == 1)
          set_reg_value("UART1_RX_BL", state);
        else
          set_reg_value("UART1_TX_BL", state);
        break;
      case 2:
        if (buf_type == 1)
          set_reg_value("UART2_RX_BL", state);
        else
          set_reg_value("UART2_TX_BL", state);
        break;
      case 3:
        if (buf_type == 1)
          set_reg_value("UART3_RX_BL", state);
        else
          set_reg_value("UART3_TX_BL", state);
        break;
      case 4:
        if (buf_type == 1)
          set_reg_value("UART4_RX_BL", state);
        else
          set_reg_value("UART4_TX_BL", state);
        break;
      default:
        break;
      };
}




void ATMC_answerExtractor::answerPacketStatsExtract(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,10);
  report.DevType   = QString::number(dev_type,10);
  report.is_ok      = true;

  Report->AddItem( report );

  if (dev_type == 1) {
      quint32 RX_MSGS       = extract_dataword(buf, 3);
      quint32 TX_MSGS       = extract_dataword(buf, 7);
      quint32 RX_MSGS_LAST  = extract_dataword(buf, 11);
      quint32 TX_MSGS_LAST  = extract_dataword(buf, 15);
      quint32 HW_PE         = extract_dataword(buf, 19);
      quint32 HW_FE         = extract_dataword(buf, 23);
      quint32 HW_OV         = extract_dataword(buf, 27);
      quint32 SW_OV         = extract_dataword(buf, 31);
      quint32 CRC32_RX      = extract_dataword(buf, 35);
      quint32 CRC32_TX      = extract_dataword(buf, 39);
    switch (dev_minor){
      case 1:
        set_reg_value("UART1_CRC32_TX",     CRC32_TX);
        set_reg_value("UART1_CRC32_RX",     CRC32_RX);
        set_reg_value("UART1_SW_OV",        SW_OV);
        set_reg_value("UART1_HW_OV",        HW_OV);
        set_reg_value("UART1_HW_PE",        HW_PE);
        set_reg_value("UART1_HW_FE",        HW_FE);
        set_reg_value("UART1_TX_MSGS_LAST", TX_MSGS_LAST);
        set_reg_value("UART1_RX_MSGS_LAST", RX_MSGS_LAST);
        set_reg_value("UART1_TX_MSGS",      TX_MSGS);
        set_reg_value("UART1_RX_MSGS",      RX_MSGS);
        break;
      case 2:
        set_reg_value("UART2_CRC32_TX",     CRC32_TX);
        set_reg_value("UART2_CRC32_RX",     CRC32_RX);
        set_reg_value("UART2_SW_OV",        SW_OV);
        set_reg_value("UART2_HW_OV",        HW_OV);
        set_reg_value("UART2_HW_PE",        HW_PE);
        set_reg_value("UART2_HW_FE",        HW_FE);
        set_reg_value("UART2_TX_MSGS_LAST", TX_MSGS_LAST);
        set_reg_value("UART2_RX_MSGS_LAST", RX_MSGS_LAST);
        set_reg_value("UART2_TX_MSGS",      TX_MSGS);
        set_reg_value("UART2_RX_MSGS",      RX_MSGS);
        break;
      case 3:
        set_reg_value("UART3_CRC32_TX",     CRC32_TX);
        set_reg_value("UART3_CRC32_RX",     CRC32_RX);
        set_reg_value("UART3_SW_OV",        SW_OV);
        set_reg_value("UART3_HW_OV",        HW_OV);
        set_reg_value("UART3_HW_PE",        HW_PE);
        set_reg_value("UART3_HW_FE",        HW_FE);
        set_reg_value("UART3_TX_MSGS_LAST", TX_MSGS_LAST);
        set_reg_value("UART3_RX_MSGS_LAST", RX_MSGS_LAST);
        set_reg_value("UART3_TX_MSGS",      TX_MSGS);
        set_reg_value("UART3_RX_MSGS",      RX_MSGS);
        break;
      case 4:
        set_reg_value("UART4_CRC32_TX",     CRC32_TX);
        set_reg_value("UART4_CRC32_RX",     CRC32_RX);
        set_reg_value("UART4_SW_OV",        SW_OV);
        set_reg_value("UART4_HW_OV",        HW_OV);
        set_reg_value("UART4_HW_PE",        HW_PE);
        set_reg_value("UART4_HW_FE",        HW_FE);
        set_reg_value("UART4_TX_MSGS_LAST", TX_MSGS_LAST);
        set_reg_value("UART4_RX_MSGS_LAST", RX_MSGS_LAST);
        set_reg_value("UART4_TX_MSGS",      TX_MSGS);
        set_reg_value("UART4_RX_MSGS",      RX_MSGS);
        break;
      default:
        break;
      };
    }

  if (dev_type == 4) {
      quint32 CFINT       = extract_dataword(buf, 3);
      quint32 CFEXT       = extract_dataword(buf, 7);

      set_reg_value("BTS_CFINT", CFINT);
      set_reg_value("BTS_CFEXT", CFEXT);
    }

  if (dev_type == 5) {
      quint32 TIMER_EXEC_ISR_CNT                = extract_dataword(buf, 3);
      quint32 TIMER_TIMER_START_CNT             = extract_dataword(buf, 7);
      quint32 TIMER_TIMER_STOP_CNT              = extract_dataword(buf, 11);
      quint32 TIMER_MAX_ISR_START_DELAY         = extract_dataword(buf, 15);
      quint32 TIMER_MAX_ISR_END_DELAY           = extract_dataword(buf, 19);
      quint32 TIMER_START_STOP_ISR_CNT_ERROR    = extract_dataword(buf, 23);
      quint64 TIMER_TIME_AT_START               = extract_quadroword(buf, 27);
      quint64 TIMER_TIME_AT_STOP                = extract_quadroword(buf, 35);
      quint32 TIMER_MAX_ISR_EXEC_TIME           = extract_dataword(buf, 43);
    switch (dev_minor){
      case 1:
        set_reg_value("TIMER1_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER1_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER1_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER1_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER1_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER1_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER1_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER1_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER1_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 2:
        set_reg_value("TIMER2_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER2_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER2_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER2_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER2_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER2_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER2_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER2_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER2_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 3:
        set_reg_value("TIMER3_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER3_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER3_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER3_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER3_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER3_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER3_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER3_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER3_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 4:
        set_reg_value("TIMER4_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER4_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER4_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER4_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER4_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER4_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER4_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER4_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER4_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 5:
        set_reg_value("TIMER5_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER5_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER5_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER5_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER5_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER5_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER5_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER5_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER5_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 6:
        set_reg_value("TIMER6_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER6_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER6_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER6_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER6_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER6_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER6_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER6_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER6_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 7:
        set_reg_value("TIMER7_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER7_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER7_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER7_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER7_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER7_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER7_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER7_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER7_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 8:
        set_reg_value("TIMER8_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER8_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER8_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER8_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER8_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER8_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER8_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER8_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER8_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 9:
        set_reg_value("TIMER9_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER9_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER9_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER9_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER9_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER9_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER9_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER9_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER9_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 10:
        set_reg_value("TIMER10_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER10_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER10_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER10_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER10_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER10_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER10_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER10_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER10_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 11:
        set_reg_value("TIMER11_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER11_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER11_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER11_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER11_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER11_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER11_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER11_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER11_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 12:
        set_reg_value("TIMER12_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER12_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER12_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER12_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER12_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER12_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER12_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER12_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER12_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 13:
        set_reg_value("TIMER13_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER13_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER13_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER13_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER13_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER13_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER13_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER13_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER13_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      case 14:
        set_reg_value("TIMER14_EXEC_ISR_CNT",             TIMER_EXEC_ISR_CNT);
        set_reg_value("TIMER14_TIMER_START_CNT",          TIMER_TIMER_START_CNT);
        set_reg_value("TIMER14_TIMER_STOP_CNT",           TIMER_TIMER_STOP_CNT);
        set_reg_value("TIMER14_MAX_ISR_START_DELAY",      TIMER_MAX_ISR_START_DELAY);
        set_reg_value("TIMER14_MAX_ISR_END_DELAY",        TIMER_MAX_ISR_END_DELAY);
        set_reg_value("TIMER14_START_STOP_ISR_CNT_ERROR", TIMER_START_STOP_ISR_CNT_ERROR);
        set_reg_value("TIMER14_START_STOP_ISR_CNT_ERROR", TIMER_TIME_AT_START);
        set_reg_value("TIMER14_TIME_AT_STOP",             TIMER_TIME_AT_STOP);
        set_reg_value("TIMER14_MAX_ISR_EXEC_TIME",        TIMER_MAX_ISR_EXEC_TIME);
        break;
      default:
        break;
      };
    }
}




void ATMC_answerExtractor::answerPacketTODExtract(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,10);
  report.DevType   = QString::number(dev_type,10);
  report.is_ok      = true;

  Report->AddItem( report );


  quint32 YEAR          = (quint32) ( buf[5])     |
                          (quint32) ( buf[4]<<8)  |
                          (quint32) ( buf[3]<<16);
  qDebug()<<"YEAR="<<YEAR;
  quint32 DAY           = (quint32) (buf[7]) |
                          (quint32) (buf[6]<<8);
  qDebug()<<"DAY="<<DAY;
  quint32 HOUR          = (quint32) buf[8];
  qDebug()<<"HOUR="<<HOUR;
  quint32 MINUTE        = (quint32) buf[9];
  qDebug()<<"MINUTE="<<MINUTE;
  quint32 SECOND        = (quint32) buf[10];
  qDebug()<<"SECOND="<<SECOND;


  if (dev_type == 4){
        set_reg_value("BTS_YEAR",    YEAR);
        set_reg_value("BTS_DAY",     DAY);
        set_reg_value("BTS_HOUR",    HOUR);
        set_reg_value("BTS_MINUTE",  MINUTE);
        set_reg_value("BTS_SECOND",  SECOND);
  }
}



void ATMC_answerExtractor::answerPacketFreqInMcSecExtract(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                           QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( unsigned int i = 0; i< size; i++)
          report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( unsigned int i = 0; i< size; i++)
      report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,16);
  report.DevType   = QString::number(dev_type,16);
  report.is_ok      = true;

  Report->AddItem( report );

  quint32 state = extract_dataword(buf, 3);

    switch (dev_minor){
      case 1:
        set_reg_value("TIMER1_INTERVAL", state);
        break;
      case 2:
        set_reg_value("TIMER2_INTERVAL", state);
        break;
      case 3:
        set_reg_value("TIMER3_INTERVAL", state);
        break;
      case 4:
        set_reg_value("TIMER4_INTERVAL", state);
        break;
      case 5:
        set_reg_value("TIMER5_INTERVAL", state);
        break;
      case 6:
        set_reg_value("TIMER6_INTERVAL", state);
        break;
      case 7:
        set_reg_value("TIMER7_INTERVAL", state);
        break;
      case 8:
        set_reg_value("TIMER8_INTERVAL", state);
        break;
      case 9:
        set_reg_value("TIMER9_INTERVAL", state);
        break;
      case 10:
        set_reg_value("TIMER10_INTERVAL", state);
        break;
      case 11:
        set_reg_value("TIMER11_INTERVAL", state);
        break;
      case 12:
        set_reg_value("TIMER12_INTERVAL", state);
        break;
      case 13:
        set_reg_value("TIMER13_INTERVAL", state);
        break;
      case 14:
        set_reg_value("TIMER14_INTERVAL", state);
        break;
      default:
        break;
      };
}



void ATMC_answerExtractor::answerPacketPrescalerValue(QString cmd_name){
  // Считаем crc16 квитанции
  quint16 crc16 = cmd_packet.crc16( (quint8 *)buf, size - 2 );
  // Получаем crc16 из самой квитанции
  quint16 lo_crc16 = 0xFF&buf[size-2];
  quint16 hi_crc16 = 0xFF&buf[size-1];
  quint16 answer_crc16 = (quint16)((lo_crc16<<8) | hi_crc16);

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  // по мажору и минору устройства определить состояние какого
  // устройства нужно обновить
  int dev_type   =  (int) buf[0] >> 4;
  int dev_minor  =  (int)(buf[0] & 0x0f );

  // Сравниваем crc16 из самой квитанции и рассчитанной нами
  if (crc16 != answer_crc16) {

      ATMC_ReportItem report;
      report.Command        =  cmd_name;
      report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
          QTime::currentTime().toString("hh:mm:ss.zzz");
      report.Desc       = "Incorrect crc16!!!";

      for ( unsigned int i = 0; i< size; i++)
        report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

      report.DevMinor  = QString::number(dev_minor,16);
      report.DevType   = QString::number(dev_type,16);
      report.is_ok      = false;

      Report->AddItem( report );

      return;
    }

  ATMC_ReportItem report;
  report.Command        =  cmd_name;
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
      QTime::currentTime().toString("hh:mm:ss.zzz");
  report.Desc       = "OK";

  for ( unsigned int i = 0; i< size; i++)
    report.Dump += QString("%1").arg(buf[i],2,16,QChar('0')).toUpper()+" ";

  report.DevMinor  = QString::number(dev_minor,16);
  report.DevType   = QString::number(dev_type,16);
  report.is_ok      = true;

  Report->AddItem( report );

  quint32 state = extract_dataword(buf, 3);


  switch (dev_minor){
    case 1:
      set_reg_value("TIMER1_PRESCALER", state);
      break;
    case 2:
      set_reg_value("TIMER2_PRESCALER", state);
      break;
    case 3:
      set_reg_value("TIMER3_PRESCALER", state);
      break;
    case 4:
      set_reg_value("TIMER4_PRESCALER", state);
      break;
    case 5:
      set_reg_value("TIMER5_PRESCALER", state);
      break;
    case 6:
      set_reg_value("TIMER6_PRESCALER", state);
      break;
    case 7:
      set_reg_value("TIMER7_PRESCALER", state);
      break;
    case 8:
      set_reg_value("TIMER8_PRESCALER", state);
      break;
    case 9:
      set_reg_value("TIMER9_PRESCALER", state);
      break;
    case 10:
      set_reg_value("TIMER10_PRESCALER", state);
      break;
    case 11:
      set_reg_value("TIMER11_PRESCALER", state);
      break;
    case 12:
      set_reg_value("TIMER12_PRESCALER", state);
      break;
    case 13:
      set_reg_value("TIMER13_PRESCALER", state);
      break;
    case 14:
      set_reg_value("TIMER14_PRESCALER", state);
      break;
    default:
      break;
    };
}


/* ========================================================================== */
/*                                                                            */
/* ========================================================================== */
  ATMC_answerExtractor::ATMC_answerExtractor(){}
  ATMC_answerExtractor::~ATMC_answerExtractor(){}

  /**
  *  Route answer to extract data
  */
  void ATMC_answerExtractor::answerPacketRoute(ATMC_cmdPacket pack, unsigned char *bf, int sz, quint8 bf_type){
    buf  = bf;
    size = sz;
    buf_type=bf_type;

    switch (pack.operation){
      case OPEN_CMD_OP:
        answerPacketStateExtract(OPEN_CMD_NAME);
        break;
      case CLOSE_CMD_OP:
        answerPacketStateExtract(CLOSE_CMD_NAME);
        break;
      case START_CMD_OP:
        answerPacketStateExtract(START_CMD_NAME);
        break;
      case STOP_CMD_OP:
        answerPacketStateExtract(STOP_CMD_NAME);
        break;
      case RESET_CMD_OP:
        answerPacketStateExtract(RESET_CMD_NAME);
        break;
      case CLEAR_STATS_CMD_OP:
        answerPacketStateExtract(CLEAR_STATS_CMD_NAME);
        break;

      case CLEAR_BUFFER_CMD_OP:
        answerPacketStateExtract(CLEAR_BUFFER_CMD_NAME);
        break;
      case RECEIVE_CMD_OP:
        answerPacketStateExtract(RECEIVE_CMD_NAME);
        break;
      case SEND_CMD_OP:
        answerPacketStateExtract(SEND_CMD_NAME);
        if (pack.DevMinor==1) uart1thrd_sender.start();
        if (pack.DevMinor==2) uart2thrd_sender.start();
        if (pack.DevMinor==3) uart3thrd_sender.start();
        if (pack.DevMinor==4) uart4thrd_sender.start();
        break;
      case EXCHANGE_STOP_CMD_OP:
        answerPacketStateExtract(EXCHANGE_STOP_CMD_NAME);
        break;
      case SET_CONFIGURE_CMD_OP:
        answerPacketStateExtract(SET_CONFIGURE_CMD_NAME);
        break;
      case SET_SPEED_CMD_OP:
        answerPacketStateExtract(SET_SPEED_CMD_NAME);
        break;
      case SET_BUFFER_LENGTH_CMD_OP:
        answerPacketStateExtract(SET_BUFFER_LENGTH_CMD_NAME);
        break;

      case GET_STATE_CMD_OP:
        answerPacketStateExtract(GET_STATE_CMD_NAME);
        break;
      case GET_CONFIGURE_CMD_OP:
        answerPacketConfigureExtract(GET_CONFIGURE_CMD_NAME);
        break;
      case GET_SPEED_CMD_OP:
        answerPacketSpeedExtract(GET_SPEED_CMD_NAME);
        break;
      case GET_BUFFER_LENGTH_CMD_OP:
        answerPacketBufLengthExtract(GET_BUFFER_LENGTH_CMD_NAME);
        break;
      case GET_STATS_CMD_OP:
        answerPacketStatsExtract(GET_STATS_CMD_NAME);
        break;

      case SET_TOD_CMD_OP:
        answerPacketStateExtract(SET_TOD_CMD_NAME);
        break;
      case GET_TOD_CMD_OP:
        answerPacketTODExtract(GET_TOD_CMD_NAME);
        break;

// TODO. Это set_speed команда. С таким же кодом.
//      case SET_FREQ_IN_MCSEC_CMD_OP:
//        extract_state(SET_FREQ_IN_MCSEC_CMD_NAME);
//        break;
// TODO. Это get_speed команда. С таким же кодом.
//      case GET_FREQ_IN_MCSEC_CMD_OP:
//        extract_freq_in_mcsec(GET_FREQ_IN_MCSEC_CMD_NAME);
//        break;
      case SET_PRESCALER_VALUE_CMD_OP:
        answerPacketStateExtract(SET_PRESCALER_VALUE_CMD_NAME);
        break;
      case GET_PRESCALER_VALUE_CMD_OP:
        answerPacketPrescalerValue(GET_PRESCALER_VALUE_CMD_NAME);
        break;

      default:
        break;
      };
  }
