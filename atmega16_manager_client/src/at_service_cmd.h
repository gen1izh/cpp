#ifndef AT_SERVICE_CMDS_H
#define AT_SERVICE_CMDS_H

#include <QRegExp>
#include <QString>
#include "at_debuger.h"



/* ========================================================================== */
/*                         Command interface                                  */
/* ========================================================================== */

class ICommand {
public :
  virtual void execute(QString input, ATMC_obCodeLine *output)=0;
  virtual bool execute(ATMC_obCodeLine current_exec_line)=0;
};


/* ========================================================================== */
/*        intermediate class pattern command                                  */
/* ========================================================================== */

class serviceCommandCollection {
  QList<ICommand*> slot;
public:
  serviceCommandCollection(){}

  void addCommand(ICommand *cmd) {
    slot.append( cmd );
  }

  void toInterpret( QString input, ATMC_obCodeLine *output ) {
    for ( int i = 0; i < slot.size(); i++ ){
        slot[i]->execute( input, output );
        qDebug()<<input;
      }
  }

  bool toPerform(ATMC_obCodeLine current_exec_line) {
     for ( int i = 0; i < slot.size(); i++ )
       if ( slot[i]->execute( current_exec_line ) ) return true;
     return false;
  }
};



/* ========================================================================== */
/*                         Services Routines                                  */
/* ========================================================================== */
class serviceRoutineADD {
public:
  serviceRoutineADD();
  ~serviceRoutineADD();
  void at_ADD_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_ADD_cmd(ATMC_obCodeLine current_exec_line);
  void at_ADD_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutineMOV {
public:
  serviceRoutineMOV();
  ~serviceRoutineMOV();
  void at_MOV_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_MOV_cmd(ATMC_obCodeLine current_exec_line);
  void at_MOV_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutineCMP {
public:
  serviceRoutineCMP();
  ~serviceRoutineCMP();
  void at_CMP_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_CMP_cmd(ATMC_obCodeLine current_exec_line);
  void at_CMP_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutineOR {
public:
  serviceRoutineOR();
  ~serviceRoutineOR();
  void at_OR_cmd( QString input, ATMC_obCodeLine *output);
  bool at_is_OR_cmd(ATMC_obCodeLine current_exec_line);
  void at_OR_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutineAND {
public:
  serviceRoutineAND();
  ~serviceRoutineAND();
  void at_AND_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_AND_cmd(ATMC_obCodeLine current_exec_line);
  void at_AND_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutineJE {
public:
  serviceRoutineJE();
  ~serviceRoutineJE();
  void at_JE_cmd( QString input, ATMC_obCodeLine *output);
  bool at_is_JE_cmd(ATMC_obCodeLine current_exec_line);
  void at_JE_exec_cmd(ATMC_obCodeLine current_exec_line);
};


class serviceRoutineJMP {
public:
  serviceRoutineJMP();
  ~serviceRoutineJMP();
  void at_JMP_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_JMP_cmd(ATMC_obCodeLine current_exec_line);
  void at_JMP_exec_cmd(ATMC_obCodeLine current_exec_line);
};


class serviceRoutineINC {
public:
  serviceRoutineINC();
  ~serviceRoutineINC();
  void at_INC_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_INC_cmd(ATMC_obCodeLine current_exec_line);
  void at_INC_exec_cmd(ATMC_obCodeLine current_exec_line);
};


class serviceRoutineDEC {
public:
  serviceRoutineDEC();
  ~serviceRoutineDEC();
  void at_DEC_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_DEC_cmd(ATMC_obCodeLine current_exec_line);
  void at_DEC_exec_cmd(ATMC_obCodeLine current_exec_line);
};


class serviceRoutineEXIT {
public:
  serviceRoutineEXIT();
  ~serviceRoutineEXIT();
  void at_EXIT_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_EXIT_cmd(ATMC_obCodeLine current_exec_line);
  void at_EXIT_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutinePRINT {
public:
  serviceRoutinePRINT();
  ~serviceRoutinePRINT();
  void at_PRINT_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_PRINT_cmd(ATMC_obCodeLine current_exec_line);
  void at_PRINT_exec_cmd(ATMC_obCodeLine current_exec_line);
};

class serviceRoutineSLEEP {
public:
  serviceRoutineSLEEP();
  ~serviceRoutineSLEEP();
  void at_SLEEP_cmd(QString input, ATMC_obCodeLine *output);
  bool at_is_SLEEP_cmd(ATMC_obCodeLine current_exec_line);
  void at_SLEEP_exec_cmd(ATMC_obCodeLine current_exec_line);
};

/* ========================================================================== */
/*                         Services Routines                                  */
/* ========================================================================== */

class interpretServiceRoutineADD : public ICommand {
public:
  serviceRoutineADD _add;

  interpretServiceRoutineADD(serviceRoutineADD _add) {
    this->_add = _add;
  }
  ~interpretServiceRoutineADD();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"add";
    _add.at_ADD_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line) {
    if ( _add.at_is_ADD_cmd( current_exec_line ) ) {
      _add.at_ADD_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};



class interpretServiceRoutineMOV : public ICommand {
public:
  serviceRoutineMOV _mov;

  interpretServiceRoutineMOV(serviceRoutineMOV _mov){
  this->_mov = _mov;
  }
  ~interpretServiceRoutineMOV();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"mov";
    _mov.at_MOV_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _mov.at_is_MOV_cmd( current_exec_line ) ) {
      _mov.at_MOV_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};



class interpretServiceRoutineCMP : public ICommand {
public:
  serviceRoutineCMP _cmp;

  interpretServiceRoutineCMP(serviceRoutineCMP _cmp) {
    this->_cmp = _cmp;
  }
  ~interpretServiceRoutineCMP();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"cmp";
    _cmp.at_CMP_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _cmp.at_is_CMP_cmd( current_exec_line ) ) {
      _cmp.at_CMP_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};



class interpretServiceRoutineOR : public ICommand {
public:
  serviceRoutineOR _or;

  interpretServiceRoutineOR(serviceRoutineOR _or) {
    this->_or = _or;
  }
  ~interpretServiceRoutineOR();

  void execute(QString input, ATMC_obCodeLine *output) {
    qDebug()<<"or";
    _or.at_OR_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _or.at_is_OR_cmd( current_exec_line ) ) {
      _or.at_OR_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }

};



class interpretServiceRoutineAND : public ICommand {
public:
  serviceRoutineAND _and;

  interpretServiceRoutineAND(serviceRoutineAND _and) {
    this->_and = _and;
  }
  ~interpretServiceRoutineAND();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"and";
    _and.at_AND_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _and.at_is_AND_cmd( current_exec_line ) ) {
      _and.at_AND_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};



class interpretServiceRoutineJE : public ICommand {
public:
  serviceRoutineJE _je;

  interpretServiceRoutineJE(serviceRoutineJE _je) {
    this->_je = _je;
  }
  ~interpretServiceRoutineJE();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"je";
    _je.at_JE_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _je.at_is_JE_cmd( current_exec_line ) ) {
      _je.at_JE_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};




class interpretServiceRoutineJMP : public ICommand {
public:
  serviceRoutineJMP _jmp;

  interpretServiceRoutineJMP(serviceRoutineJMP _jmp) {
    this->_jmp = _jmp;
  }
  ~interpretServiceRoutineJMP();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"jmp";
    _jmp.at_JMP_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _jmp.at_is_JMP_cmd( current_exec_line ) ) {
      _jmp.at_JMP_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};




class interpretServiceRoutineINC : public ICommand {
public:
  serviceRoutineINC _inc;

  interpretServiceRoutineINC(serviceRoutineINC _inc) {
    this->_inc = _inc;
  }
  ~interpretServiceRoutineINC();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"inc";
    _inc.at_INC_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _inc.at_is_INC_cmd( current_exec_line ) ) {
      _inc.at_INC_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};




class interpretServiceRoutineDEC : public ICommand {
public:
  serviceRoutineDEC _dec;

  interpretServiceRoutineDEC(serviceRoutineDEC _dec) {
    this->_dec = _dec;
  }
  ~interpretServiceRoutineDEC();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"dec";
    _dec.at_DEC_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _dec.at_is_DEC_cmd( current_exec_line ) ) {
      _dec.at_DEC_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};




class interpretServiceRoutineEXIT : public ICommand {
public:
  serviceRoutineEXIT _exit;

  interpretServiceRoutineEXIT(serviceRoutineEXIT _exit) {
    this->_exit = _exit;
  }
  ~interpretServiceRoutineEXIT();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"exit";
    _exit.at_EXIT_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _exit.at_is_EXIT_cmd( current_exec_line ) ) {
      _exit.at_EXIT_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};



class interpretServiceRoutinePRINT : public ICommand {
public:
  serviceRoutinePRINT _print;

  interpretServiceRoutinePRINT(serviceRoutinePRINT _print) {
    this->_print = _print;
  }
  ~interpretServiceRoutinePRINT();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"print";
    _print.at_PRINT_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _print.at_is_PRINT_cmd( current_exec_line ) ) {
      _print.at_PRINT_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};



class interpretServiceRoutineSLEEP : public ICommand {
public:
  serviceRoutineSLEEP _sleep;

  interpretServiceRoutineSLEEP(serviceRoutineSLEEP _sleep) {
    this->_sleep = _sleep;
  }
  ~interpretServiceRoutineSLEEP();

  void execute(QString input, ATMC_obCodeLine *output){
    qDebug()<<"sleep";
    _sleep.at_SLEEP_cmd( input, output );
  }

  bool execute(ATMC_obCodeLine current_exec_line){
    if ( _sleep.at_is_SLEEP_cmd( current_exec_line ) ) {
      _sleep.at_SLEEP_exec_cmd( current_exec_line );
      return true;
    }
    return false;
  }
};


extern serviceCommandCollection cmdCollection;

extern serviceRoutineADD   addCmd;
extern serviceRoutineMOV   movCmd;
extern serviceRoutineCMP   cmpCmd;
extern serviceRoutineOR    orCmd;
extern serviceRoutineAND   andCmd;
extern serviceRoutineJE    jeCmd;
extern serviceRoutineJMP   jmpCmd;
extern serviceRoutineINC   incCmd;
extern serviceRoutineDEC   decCmd;
extern serviceRoutineEXIT  exitCmd;
extern serviceRoutinePRINT printCmd;
extern serviceRoutineSLEEP sleepCmd;

extern interpretServiceRoutineADD   iterAddCmd;
extern interpretServiceRoutineMOV   iterMovCmd;
extern interpretServiceRoutineCMP   iterCmpCmd;
extern interpretServiceRoutineOR    iterOrCmd;
extern interpretServiceRoutineAND   iterAndCmd;
extern interpretServiceRoutineJE    iterJeCmd;
extern interpretServiceRoutineJMP   iterJmpCmd;
extern interpretServiceRoutineINC   iterIncCmd;
extern interpretServiceRoutineDEC   iterDecCmd;
extern interpretServiceRoutineEXIT  iterExitCmd;
extern interpretServiceRoutinePRINT iterPrintCmd;
extern interpretServiceRoutineSLEEP iterSleepCmd;
#endif // AT_SERVICE_CMDS_H
