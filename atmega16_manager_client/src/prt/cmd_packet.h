#ifndef PRT_ATM_H_
#define PRT_ATM_H_

#include "../utils/crc.h"
#include "at_manager_client.h"


/*
 * Command structure
 */
typedef struct {
   quint8  DevType;
   quint8  DevMinor;
   quint8  cmd_type;
   quint8  err_flag;
   quint8  operation;
   quint8  data_size;
   quint8  data[246];
   quint16 crc16;
}ATMC_cmdPacket;


class at_cmd_packet{
public:



    at_cmd_packet();
    ~at_cmd_packet();

    ATMC_cmdPacket pack;
    quint8             rawData[256];

    /* ========================================================================== */
    /*                             Operation functions                            */
    /* ========================================================================== */

    /*
     *  Очистка пакета с командой
     */
    void clear();

    /*
     *  Конвертируем массив сырых данных команды в командный пакет
     */
    void to_packet(quint8 *data_packet);

    /*
     *  Конвертируем командный пакет в массив сырых данных
     */
    quint8 *to_rawData();

    /*
     * Формирования командного пакета
     */
    void set_dev_minor(quint8 DevMinor);
    void set_dev_type(quint8 DevType);
    void set_operation(quint8 op);
    void set_flag_error(quint8 flag_error);
    void set_cmd_type(quint8 command_type);
    void set_data_size(quint8 data_size);
    void set_crc16(quint16 crc16);

    /*
     * Получение параметров команды
     */
    void get_dev_minor(quint8 DevMinor);
    void get_dev_type(quint8 DevType);
    void get_operation(quint8 op);
    void get_flag_error(quint8 flag_error);
    void get_cmd_type(quint8 command_type);
    void get_data_size(quint8 data_size);

    ATMC_cmdPacket get_pack();


    /* ========================================================================== */
    /*                              Utility functions                             */
    /* ========================================================================== */

    /*
     *  � ассчет CRC16
     */
    quint16 crc16(
      quint8         *buf,
      quint16         buf_size
    );


    /*
     * � ассчет CRC32
     */
    quint32 crc32(
      quint8 *buf,
      qint32 buf_size
    );
};



/* ========================================================================== */
/*                              Коммандные пакеты                             */
/* ========================================================================== */

 /*
  * Команда, выдаваемая серверу
  */
extern at_cmd_packet cmd_packet;
/*
 * Ответ, полученный от сервера
 */
extern at_cmd_packet answer_packet;



#endif /* PRT_ATM_H_ */
