#include "at_service_cmd.h"
#include "at_registers.h"
#include "at_manager_client.h"
#include "at_report.h"

extern at_reg_map_t reg_map[1000];


bool is_param_valid(QString param){
  int i = 0;
  bool ret_value = false;

   while(reg_map[i].reg_name!="0") {

      if (param==reg_map[i].reg_name)
        return true;
      i++;
    }

   QRegExp reg("[0-9]+");
   if (reg.indexIn(param) != -1)
    return true;

return ret_value;
}

/*
 * Бинарные команды ADD, CMP
 */
void detect_service_bcmd(QString input, ATMC_obCodeLine *output, QString cmd_name){
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
  if ( (tmpCodeLineList[0] == cmd_name) ||
       (tmpCodeLineList[1] == cmd_name)) {

      output->cmd_type = "CMD";
      output->dump = cmd_name;

      if (tmpCodeLineList[0] == cmd_name)
      if (is_param_valid(tmpCodeLineList[1])){
          output->op1 =tmpCodeLineList[1];
          output->op2 =tmpCodeLineList[2];
        }
      if (tmpCodeLineList[1] == cmd_name)
      if (is_param_valid(tmpCodeLineList[2])){
          output->op1 =tmpCodeLineList[2];
          output->op2 =tmpCodeLineList[3];
          output->label    = tmpCodeLineList[0];
        }

       /*
        * TODO Надо сделать проверку 2 параметра.
        * Он может быть как регистр так и число.
        * Надо узнать какая функция проверяет строку на то что она является
        * числом или нет.
        */

  }
  return ;
}

 /*
  * Унарные команды INC, DEC
  */
void detect_service_ucmd(QString input, ATMC_obCodeLine *output, QString cmd_name){
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
  if ( (tmpCodeLineList[0] == cmd_name) ||
       (tmpCodeLineList[1] == cmd_name)) {

      output->cmd_type = "CMD";
      output->dump = cmd_name;

      if (tmpCodeLineList[0] == cmd_name)
      if (is_param_valid(tmpCodeLineList[1])){
          output->op1 =tmpCodeLineList[1];
        }
      if (tmpCodeLineList[1] == cmd_name)
      if (is_param_valid(tmpCodeLineList[2])){
          output->op1 =tmpCodeLineList[2];
          output->label    = tmpCodeLineList[0];
        }

       /*
        * TODO Надо сделать проверку 2 параметра.
        * Он может быть как регистр так и число.
        * Надо узнать какая функция проверяет строку на то что она является
        * числом или нет.
        */

  }
  return ;
}


 /*
  * JMP команды перехода по коду
  */
void detect_service_jcmd(QString input, ATMC_obCodeLine *output, QString cmd_name){

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
  if ( (tmpCodeLineList[0] == cmd_name) ||
       (tmpCodeLineList[1] == cmd_name)) {

      output->cmd_type = "CMD";
      output->dump = cmd_name;

      if (tmpCodeLineList[0] == cmd_name)
      if (is_param_valid(tmpCodeLineList[1])){
          output->goto_cmd = tmpCodeLineList[1];
        }
      if (tmpCodeLineList[1] == cmd_name)
      if (is_param_valid(tmpCodeLineList[2])){
          output->goto_cmd = tmpCodeLineList[2];
          output->label    = tmpCodeLineList[0];
        }

       /*
        * TODO Надо сделать проверку 2 параметра.
        * Он может быть как регистр так и число.
        * Надо узнать какая функция проверяет строку на то что она является
        * числом или нет.
        */

  }
  return ;

}



serviceCommandCollection cmdCollection;

serviceRoutineADD   addCmd;
serviceRoutineMOV   movCmd;
serviceRoutineCMP   cmpCmd;
serviceRoutineOR    orCmd;
serviceRoutineAND   andCmd;
serviceRoutineJE    jeCmd;
serviceRoutineJMP   jmpCmd;
serviceRoutineINC   incCmd;
serviceRoutineDEC   decCmd;
serviceRoutineEXIT  exitCmd;
serviceRoutinePRINT printCmd;
serviceRoutineSLEEP sleepCmd;

interpretServiceRoutineADD   iterAddCmd(addCmd);
interpretServiceRoutineMOV   iterMovCmd(movCmd);
interpretServiceRoutineCMP   iterCmpCmd(cmpCmd);
interpretServiceRoutineOR    iterOrCmd(orCmd);
interpretServiceRoutineAND   iterAndCmd(andCmd);
interpretServiceRoutineJE    iterJeCmd(jeCmd);
interpretServiceRoutineJMP   iterJmpCmd(jmpCmd);
interpretServiceRoutineINC   iterIncCmd(incCmd);
interpretServiceRoutineDEC   iterDecCmd(decCmd);
interpretServiceRoutineEXIT  iterExitCmd(exitCmd);
interpretServiceRoutinePRINT iterPrintCmd(printCmd);
interpretServiceRoutineSLEEP iterSleepCmd(sleepCmd);



void serviceRoutineADD::at_ADD_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_bcmd(input, output, "ADD");
}

bool serviceRoutineADD::at_is_ADD_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="ADD"))
    return true;

  return false;
}

void serviceRoutineADD::at_ADD_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int     op1_value, op2_value;
  bool    ok;
  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value)) {

    if (get_reg_value(current_exec_line.op2, &op2_value)){
        op1_value += op2_value;
      }
    else {
        op2_value = current_exec_line.op2.toInt(&ok,0);
        op1_value += op2_value;
      }
  }

  if (set_reg_value(current_exec_line.op1, op1_value)){}
}

void serviceRoutineMOV::at_MOV_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_bcmd(input, output, "MOV");
}

bool serviceRoutineMOV::at_is_MOV_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="MOV"))
    return true;

  return false;
}

void serviceRoutineMOV::at_MOV_exec_cmd(ATMC_obCodeLine current_exec_line)
{

  int     op1_value, op2_value;
  bool    ok;

  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value)) {

    if (get_reg_value(current_exec_line.op2, &op2_value)){
        op1_value = op2_value;
      }
    else {
        op2_value = current_exec_line.op2.toInt(&ok,0);
        op1_value = op2_value;
      }
  }

  if (set_reg_value(current_exec_line.op1, op1_value)){}
}

void serviceRoutineCMP::at_CMP_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_bcmd(input, output, "CMP");
}

bool serviceRoutineCMP::at_is_CMP_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="CMP"))
    return true;

  return false;
}

void serviceRoutineCMP::at_CMP_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int     op1_value, op2_value;
  int     FReg_value;
  bool    ok;

  get_reg_value("FReg", &FReg_value);

  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value))
    if (get_reg_value(current_exec_line.op2, &op2_value));
    else op2_value = current_exec_line.op2.toInt(&ok,0);

  if (op1_value <= op2_value) set_reg_value("FReg", FReg_value|0x2);
  else set_reg_value("FReg", FReg_value&(~0x2));

}

void serviceRoutineOR::at_OR_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_bcmd(input, output, "OR");
}

bool serviceRoutineOR::at_is_OR_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="OR"))
    return true;

  return false;
}

void serviceRoutineOR::at_OR_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int     op1_value, op2_value;
  bool    ok;

  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value)) {

    if (get_reg_value(current_exec_line.op2, &op2_value)){
        op1_value |= op2_value;
      }
    else {
        op2_value = current_exec_line.op2.toInt(&ok,0);
        op1_value |= op2_value;
      }
  }

  if (set_reg_value(current_exec_line.op1, op1_value)){}
}

void serviceRoutineAND::at_AND_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_bcmd(input, output, "AND");
}

bool serviceRoutineAND::at_is_AND_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="AND"))
    return true;

  return false;
}

void serviceRoutineAND::at_AND_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int     op1_value, op2_value;
  bool    ok;

  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value)) {

    if (get_reg_value(current_exec_line.op2, &op2_value)){
        op1_value &= op2_value;
      }
    else {
        op2_value = current_exec_line.op2.toInt(&ok,0);
        op1_value &= op2_value;
      }
  }

  if (set_reg_value(current_exec_line.op1, op1_value)){}
}

void serviceRoutineJE::at_JE_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_jcmd(input, output, "JE");
}

bool serviceRoutineJE::at_is_JE_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="JE"))
    return true;

  return false;
}

void serviceRoutineJE::at_JE_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  QString goto_cmd;
  int FReg_value = 0;
  goto_cmd = current_exec_line.goto_cmd;
  get_reg_value("FReg", &FReg_value);

  if (FReg_value&0x2) {
      for (int i = 0; i < virtualDebbuger.cmdSequence.size(); i++) {
          if (virtualDebbuger.cmdSequence.at(i).label == goto_cmd) {
              virtualDebbuger.PC = i;
              break;
            }
          else
            virtualDebbuger.PC = virtualDebbuger.cmdSequence.size();
        }
    }
  else virtualDebbuger.PC++;
}

void serviceRoutineJMP::at_JMP_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_jcmd(input, output, "JMP");
}

bool serviceRoutineJMP::at_is_JMP_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="JMP"))
    return true;

  return false;
}

void serviceRoutineJMP::at_JMP_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  QString goto_cmd;
  goto_cmd = current_exec_line.goto_cmd;
  for (int i = 0; i < virtualDebbuger.cmdSequence.size(); i++) {
      if (virtualDebbuger.cmdSequence.at(i).label == goto_cmd) {
        virtualDebbuger.PC = i;
        break;
      }
      else
        virtualDebbuger.PC = virtualDebbuger.cmdSequence.size();
    }
}

void serviceRoutineINC::at_INC_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_ucmd(input, output, "INC");
}

bool serviceRoutineINC::at_is_INC_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="INC"))
    return true;

  return false;
}

void serviceRoutineINC::at_INC_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int     op1_value;

  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value)) {
       op1_value ++;
       if (set_reg_value(current_exec_line.op1, op1_value)){}
      }
}

void serviceRoutineDEC::at_DEC_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_ucmd(input, output, "DEC");
}

bool serviceRoutineDEC::at_is_DEC_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="DEC"))
    return true;

  return false;
}

void serviceRoutineDEC::at_DEC_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int     op1_value;

  /*TODO сделать валидаторы*/
  if (get_reg_value(current_exec_line.op1, &op1_value)){
      op1_value--;
       if (set_reg_value(current_exec_line.op1, op1_value)){}
  }
}

void serviceRoutineEXIT::at_EXIT_cmd(QString input, ATMC_obCodeLine *output)
{
  QString text = QString(input);
  QRegExp rx("EXIT");
  Qt::CaseSensitivity cs = Qt::CaseInsensitive;
  cs = Qt::CaseSensitive;
  rx.setCaseSensitivity(cs);
  if ( rx.indexIn(text) != -1){

      QStringList list = text.split(QRegExp("\\s+"));

      // Удаляем пустышки из списка строк
      for ( int i = 0; i < list.size(); i++ )
        if (list[i]=="") list.removeAt(i);

      if (list[1] == "EXIT"){
          output->label = list[0];
          output->dump = list[1];
        }
      else if (list[0] == "EXIT")
        output->dump = list[0];
      output->cmd_type = "CMD";
  }
}

bool serviceRoutineEXIT::at_is_EXIT_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="EXIT"))
    return true;

  return false;
}

void serviceRoutineEXIT::at_EXIT_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  /*
    PC = nPC;
  */
    virtualDebbuger.PC = virtualDebbuger.cmdSequence.size();
}

void serviceRoutinePRINT::at_PRINT_cmd(QString input, ATMC_obCodeLine *output)
{
  QString text = QString(input);
  QString y = "'";
  int value;
  QRegExp rx("PRINT");
  Qt::CaseSensitivity cs = Qt::CaseInsensitive;
  cs = Qt::CaseSensitive;
  rx.setCaseSensitivity(cs);
  if (text.indexOf(y)>=0) {
      if ( rx.indexIn(text) != -1){
          QStringList list = text.split("'");
          output->dump = list[1];
          list = text.split(QRegExp("\\s+"));
          // Удаляем пустышки из списка строк
          for ( int i = 0; i < list.size(); i++ )
            if (list[i]=="") list.removeAt(i);
          if (list[1] == "PRINT"){
              output->label = list[0];
            }
        }
    }
}

bool serviceRoutinePRINT::at_is_PRINT_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "") &&
      (current_exec_line.dump !=""))
    return true;

  return false;
}

void serviceRoutinePRINT::at_PRINT_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  int value;
  ATMC_ReportItem report;
  //Use Report singlton
  ATMC_Report* Report = ATMC_Report::Instance();

  report.Command        = "NULL";
  report.DataTime  =  QDate::currentDate().toString("dd.MM.yy ")+
                       QTime::currentTime().toString("hh:mm:ss.zzz");


  if(get_reg_value(current_exec_line.dump, &value))
   report.Desc       = QString("0x%1").arg(value,8,16,QChar('0'));
  else
   report.Desc       = current_exec_line.dump;

  report.DevMinor  = "NULL";
  report.Dump       = "NULL";
  report.DevType   = "NULL";
  report.is_ok      = true;

  Report->AddItem(report);
}

void serviceRoutineSLEEP::at_SLEEP_cmd(QString input, ATMC_obCodeLine *output)
{
  detect_service_ucmd(input, output, "SLEEP");
}

bool serviceRoutineSLEEP::at_is_SLEEP_cmd(ATMC_obCodeLine current_exec_line)
{
  if ((current_exec_line.cmd_type == "CMD") &&
      (current_exec_line.dump =="SLEEP"))
    return true;

  return false;
}

void serviceRoutineSLEEP::at_SLEEP_exec_cmd(ATMC_obCodeLine current_exec_line)
{
  return;
}

/**
  * constructors
  */
serviceRoutineADD::serviceRoutineADD()
{
}

serviceRoutineADD::~serviceRoutineADD()
{
}

serviceRoutineMOV::serviceRoutineMOV()
{
}

serviceRoutineMOV::~serviceRoutineMOV()
{
}

serviceRoutineCMP::serviceRoutineCMP()
{
}

serviceRoutineCMP::~serviceRoutineCMP()
{
}

serviceRoutineOR::serviceRoutineOR()
{
}

serviceRoutineOR::~serviceRoutineOR()
{
}

serviceRoutineAND::serviceRoutineAND()
{
}

serviceRoutineAND::~serviceRoutineAND()
{
}

serviceRoutineJE::serviceRoutineJE()
{
}

serviceRoutineJE::~serviceRoutineJE()
{
}

serviceRoutineJMP::serviceRoutineJMP()
{
}

serviceRoutineJMP::~serviceRoutineJMP()
{
}

serviceRoutineINC::serviceRoutineINC()
{
}

serviceRoutineINC::~serviceRoutineINC()
{
}

serviceRoutineDEC::serviceRoutineDEC()
{
}

serviceRoutineDEC::~serviceRoutineDEC()
{
}

serviceRoutineEXIT::serviceRoutineEXIT()
{
}

serviceRoutineEXIT::~serviceRoutineEXIT()
{
}

serviceRoutinePRINT::serviceRoutinePRINT()
{
}

serviceRoutinePRINT::~serviceRoutinePRINT()
{
}

serviceRoutineSLEEP::serviceRoutineSLEEP()
{
}

serviceRoutineSLEEP::~serviceRoutineSLEEP()
{
}

interpretServiceRoutineADD::~interpretServiceRoutineADD()
{
}

interpretServiceRoutineMOV::~interpretServiceRoutineMOV()
{
}

interpretServiceRoutineCMP::~interpretServiceRoutineCMP()
{
}

interpretServiceRoutineOR::~interpretServiceRoutineOR()
{
}

interpretServiceRoutineAND::~interpretServiceRoutineAND()
{
}

interpretServiceRoutineJE::~interpretServiceRoutineJE()
{
}

interpretServiceRoutineJMP::~interpretServiceRoutineJMP()
{
}

interpretServiceRoutineINC::~interpretServiceRoutineINC()
{
}

interpretServiceRoutineDEC::~interpretServiceRoutineDEC()
{
}

interpretServiceRoutineEXIT::~interpretServiceRoutineEXIT()
{
}

interpretServiceRoutinePRINT::~interpretServiceRoutinePRINT()
{
}

interpretServiceRoutineSLEEP::~interpretServiceRoutineSLEEP()
{
}
