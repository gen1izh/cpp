#ifndef DSUPROTO_H
#define DSUPROTO_H


#include <QThread>

/**
  * TODO: Из описания протокола в мануале не ясно что означает length
  * len = addr_BYTES + data_BYTES
  * или len = data_BYTES
  */
class dsuProto : public QThread {

  /* Состояния потока */
  enum {
    IDLE_STATE,
    WRITE_CMD_STATE,
    READ_CMD_STATE
  };

  // текущее состояние потока
  int state;
  // временная переменная для оперделения длины ответного пакета
  int tmpLen;
  // ответ
  char respData[100];

  public:
    dsuProto();

    void run();

    // Запись данных в память
    // len должен быть меньше 64
    void writeDSUDataCmd( unsigned int addr, unsigned char *data, unsigned char len );

    // Чтение данных из память
    // len должен быть менбше 64
    void readDSUDataCmd( unsigned int addr, unsigned char len );

    // Ожидание ответа
    void waitAnswer();

    char *mem(unsigned int addr, unsigned int len);
    void eeload(unsigned int addr, char *filename);
    void wmem(unsigned int addr, unsigned int data);
    void runimage(unsigned int addr);
};



#endif // DSUPROTO_H
