#ifndef DSUPROTO_H
#define DSUPROTO_H


#include <QThread>

/**
  * TODO: �� �������� ��������� � ������� �� ���� ��� �������� length
  * len = addr_BYTES + data_BYTES
  * ��� len = data_BYTES
  */
class dsuProto : public QThread {

  /* ��������� ������ */
  enum {
    IDLE_STATE,
    WRITE_CMD_STATE,
    READ_CMD_STATE
  };

  // ������� ��������� ������
  int state;
  // ��������� ���������� ��� ����������� ����� ��������� ������
  int tmpLen;
  // �����
  char respData[100];

  public:
    dsuProto();

    void run();

    // ������ ������ � ������
    // len ������ ���� ������ 64
    void writeDSUDataCmd( unsigned int addr, unsigned char *data, unsigned char len );

    // ������ ������ �� ������
    // len ������ ���� ������ 64
    void readDSUDataCmd( unsigned int addr, unsigned char len );

    // �������� ������
    void waitAnswer();

    char *mem(unsigned int addr, unsigned int len);
    void eeload(unsigned int addr, char *filename);
    void wmem(unsigned int addr, unsigned int data);
    void runimage(unsigned int addr);
};



#endif // DSUPROTO_H
