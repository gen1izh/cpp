#ifndef AT_THREAD_H
#define AT_THREAD_H

#include <QThread>
#include <Windows.h>
#include "at_ftdi_module.h"
#include "prt/cmd_packet.h"



enum thread_state{
  at_send_command_packet,
  at_wait_answer_packet,
  at_idle_state
};

extern thread_state at_thread_state;

class AtThread : public QThread
{
public:
//  AtThread(QObject *parent=0): QThread(parent){}

  AtThread();
  ~AtThread();

  void run();
};


/**
  * Потоки UART
  */



class Uart1SenderThread : public QThread
{
public:
  int               size;
  QString           filename;
  Uart1SenderThread();
  ~Uart1SenderThread();
  void run();
};



class Uart2SenderThread : public QThread
{
public:
  int size;
  QString filename;
  Uart2SenderThread();
  ~Uart2SenderThread();
  void run();
};

class Uart3SenderThread : public QThread
{
public:
  int size;
  QString filename;
  Uart3SenderThread();
  ~Uart3SenderThread();
  void run();
};

class Uart4SenderThread : public QThread
{
public:
  int size;
  QString filename;
  Uart4SenderThread();
  ~Uart4SenderThread();
  void run();
};


class Uart1ReceiverThread : public QThread
{
public:
  int size;
  QString filename;
  Uart1ReceiverThread();
  ~Uart1ReceiverThread();
  void run();
};



class Uart2ReceiverThread : public QThread
{
public:
  int size;
  QString filename;
  Uart2ReceiverThread();
  ~Uart2ReceiverThread();
  void run();
};

class Uart3ReceiverThread : public QThread
{
public:
  int size;
  QString filename;
  Uart3ReceiverThread();
  ~Uart3ReceiverThread();
  void run();
};

class Uart4ReceiverThread : public QThread
{
public:
  int size;
  QString filename;
  Uart4ReceiverThread();
  ~Uart4ReceiverThread();
  void run();
};
extern Uart1SenderThread uart1thrd_sender;
extern Uart2SenderThread uart2thrd_sender;
extern Uart3SenderThread uart3thrd_sender;
extern Uart4SenderThread uart4thrd_sender;

extern Uart1ReceiverThread uart1thrd_receive;
extern Uart2ReceiverThread uart2thrd_receive;
extern Uart3ReceiverThread uart3thrd_receive;
extern Uart4ReceiverThread uart4thrd_receive;
#endif // AT_THREAD_H
