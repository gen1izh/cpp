#include "at_thread.h"
#include "at_debuger.h"
#include "prt/answerExtractor.h"
#include "macro.h"
#include <QtGui>
#include <QSettings>
#include "at_report.h"

thread_state at_thread_state;

AtThread::AtThread() {
}

AtThread::~AtThread() {
}

AtThread at_send_state;

void AtThread::run(){
  unsigned char     packet[256];
  unsigned int      size,read_cnt;

  quint8            buf_type;
  ATMC_answerExtractor  rat;
  ATMC_ReportItem    report;

  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  QSettings setting("home","atmc");

  QString str = setting.value("/Setting/DeviceName","").toString();
  if (str == "") {
      str="A6007kOi";
      setting.setValue("/Setting/DeviceName",str);
    }

  UartDevice        ops(str);
  ops.setTimeouts(5000,5000);

  at_thread_state = at_idle_state;
  forever {
    msleep(10);
    //    // Тело потока
    switch(at_thread_state){

      case at_send_command_packet:
        buf_type = 0;
        cmd_packet= virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).pack;
        cmd_packet.to_rawData();
        ops.write((char *)&cmd_packet.rawData[0],
                  cmd_packet.pack.data_size + CONST_DATA_SIZE);


        /*
          * Формирование записи в отчете о том что  ушла команда
          */


        report.Command        = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).cmd_name;
        report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
            QTime::currentTime().toString("hh:mm:ss.zzz");
        report.Desc       = "SEND CMD";
        report.DevMinor  = "NULL";
        report.Dump="";
        for (int i=0; i<cmd_packet.pack.data_size + CONST_DATA_SIZE; i++)
          report.Dump += QString("%1").arg(cmd_packet.rawData[i],2,16,QChar('0')).toUpper()+" ";

        report.DevType   = "NULL";
        report.is_ok      = true;
        Report->AddItem( report );



        at_thread_state = at_wait_answer_packet;
        if ( cmd_packet.pack.operation == 0x43 )
          if (cmd_packet.pack.data[0] == 0)
            buf_type = 1;/*RX*/
          else buf_type =2;/*TX*/



        if ( cmd_packet.pack.operation == 0x09 ) {
            if (cmd_packet.pack.DevMinor==1) {
                uart1thrd_sender.filename = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).filename_data;
                uart1thrd_sender.size     = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).size_transfer;
              }
            if (cmd_packet.pack.DevMinor==2) {
                uart2thrd_sender.filename = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).filename_data;
                uart2thrd_sender.size     = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).size_transfer;
              }
            if (cmd_packet.pack.DevMinor==3) {
                uart3thrd_sender.filename = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).filename_data;
                uart3thrd_sender.size     = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).size_transfer;
              }
            if (cmd_packet.pack.DevMinor==4) {
                uart4thrd_sender.filename = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).filename_data;
                uart4thrd_sender.size     = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).size_transfer;
              }
          }

        break;

      case at_wait_answer_packet:
        size = virtualDebbuger.cmdSequence.at(virtualDebbuger.PC).ret_buf_size;
        ops.read((unsigned char *)&packet[0], size, &read_cnt);

        rat.answerPacketRoute( cmd_packet.pack, (unsigned char *)&packet[0], size, buf_type);
        at_thread_state = at_idle_state;

        virtualDebbuger.PC++;

        break;
      case at_idle_state:
        break;
      }
  }
}


/**
  * Потоки UART
  */

  Uart1SenderThread uart1thrd_sender;
  Uart2SenderThread uart2thrd_sender;
  Uart3SenderThread uart3thrd_sender;
  Uart4SenderThread uart4thrd_sender;

  Uart1ReceiverThread uart1thrd_receive;
  Uart2ReceiverThread uart2thrd_receive;
  Uart3ReceiverThread uart3thrd_receive;
  Uart4ReceiverThread uart4thrd_receive;


Uart1SenderThread::Uart1SenderThread(){}

Uart1SenderThread::~Uart1SenderThread(){}


void Uart1SenderThread::run(){
  unsigned char     *packet = new unsigned char[size];
  unsigned int       read_cnt=0,all_bytes_recieve=0;
  int status=0;

  QFile file(filename);
  if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    return;
  QTextStream out(&file);

  QSettings setting("home","atmc");

  QString str = setting.value("/Setting/Uart1Name","").toString();
  if (str == "") {
      str="A6007kOi";
      setting.setValue("/Setting/Uart1Name",str);
    }

  UartDevice ops(str);
  ops.setTimeouts(5000,500);


  while((status!=FT_OTHER_ERROR/*TODO timeout*/)&&(all_bytes_recieve<size)) {
      status = ops.read((unsigned char *)&packet[0], size-all_bytes_recieve, &read_cnt);
       qDebug()<<"uart1 after read ";
      if (status==FT_OTHER_ERROR)
        qDebug()<<"timeout!";
      all_bytes_recieve+=read_cnt;
      qDebug()<<"uart1  read_cnt ="<< read_cnt;
      for( unsigned int i = 0; i< read_cnt; i++)
        out<<packet[i];
      msleep(10);
    }
  qDebug()<<"uart1 read end";

  delete []packet;
}

//=============================
Uart2SenderThread::Uart2SenderThread()
{
}

Uart2SenderThread::~Uart2SenderThread()
{
}


void Uart2SenderThread::run(){

}

//=============================
Uart3SenderThread::Uart3SenderThread()
{
}

Uart3SenderThread::~Uart3SenderThread()
{
}


void Uart3SenderThread::run(){

}

//=============================
Uart4SenderThread::Uart4SenderThread()
{
}

Uart4SenderThread::~Uart4SenderThread()
{
}


void Uart4SenderThread::run(){

}



//==================================================




Uart1ReceiverThread::Uart1ReceiverThread()
{
}

Uart1ReceiverThread::~Uart1ReceiverThread()
{
}


void Uart1ReceiverThread::run(){

}

//=============================
Uart2ReceiverThread::Uart2ReceiverThread()
{
}

Uart2ReceiverThread::~Uart2ReceiverThread()
{
}


void Uart2ReceiverThread::run(){

}

//=============================
Uart3ReceiverThread::Uart3ReceiverThread()
{
}

Uart3ReceiverThread::~Uart3ReceiverThread()
{
}


void Uart3ReceiverThread::run(){

}

//=============================
Uart4ReceiverThread::Uart4ReceiverThread()
{
}

Uart4ReceiverThread::~Uart4ReceiverThread()
{
}


void Uart4ReceiverThread::run(){

}



