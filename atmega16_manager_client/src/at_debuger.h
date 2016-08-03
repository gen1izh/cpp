#ifndef AT_DEBUGER_H
#define AT_DEBUGER_H
#include <QList>
#include <QtGui>
#include "prt/cmd_packet.h"
#include "prt/answerExtractor.h"


/* ========================================================================== */
/*                          Virtual Debbuger                                  */
/* ========================================================================== */

  /**
  * Debug-code line structure
  */
struct ATMC_obCodeLine
{
    bool          exec;             // Выполняемая команда в текущий момент
    QString       num_cmd;          // Номер команды
    QString       label;            // Переход-метка на команду, если есть
    QString       cmd_type;         // Тип команды(общий - PKT, служебная - CMD)
    QString       goto_cmd;         // Переход на метку, если нет то PC++
    QString       dump;             // Дамп пакета команды(для наглядности),
                                    // если cmd_type=PKT
    QString       op1;              // Операнд 1
    QString       op2;              // Операнд 2
    int           link_edit_line;   // Ссылка на строку кода в textEdit
    at_cmd_packet pack;             // Содержимое командого пакета
    QString       cmd_name;
    int           ret_buf_size;
    int size_transfer;
    QString filename_data;
    ATMC_answerExtractor func;
};


  /**
  * Virtual Debbuger Class
  */
class ATMC_virtualDebbuger {
  public:
    ATMC_virtualDebbuger();
    ~ATMC_virtualDebbuger();
    QList<ATMC_obCodeLine> cmdSequence;
    int PC;
    void repaint();
    void add_dbg_line(ATMC_obCodeLine dbg);
    void set_exec();
    void set_num_cmd();
    void set_label();
    void set_cmd_type();
    void set_goto_cmd();
    void set_dump();
    void set_op1();
    void set_op2();
    void set_link_edit_line();
    void set_pack();
};

extern ATMC_virtualDebbuger virtualDebbuger;

#endif // AT_DEBUGER_H
