#include "modulethread.h"
#include <frameWork/managers.h>
#include <frameWork/gui/klevergui.h>

ModuleThread::ModuleThread(QObject* parent) :
    QThread(parent)
{
  // Установка значений таймаута
  timeoutValHi = 500;
  timeoutValLo = 10;
  timeout = timeoutValHi;

  setObjectName("Поток команд");

  // Перевод потока в рабочее состояние
  setWorkingState();
}


ModuleThread::~ModuleThread(){}

/*
 * Признак того что поток работает
 * При закрытии программы необходимо выключить поток
 * и дождаться этого условия if (!isWorking()) {...}
 */
bool ModuleThread::isWorking() const {
  if(state == WORKING){
    return true;
  }
  return false;
}

/*
 * Перевод потока в рабочее состояние
 */
void ModuleThread::setWorkingState() {
  state = WORKING;
}

/*
 * Перевод потока в не рабочее состояние
 */
void ModuleThread::setTerminateState() {
  state = TERMINATE;

  /*
   * Эта операция нужна для того чтобы правильно завершить функцию run
   * до удаления объекта потока из памяти
   */
  if (!wait(1000)) {
    Library::LoggerApi::logWarning(this, QString("Таймаут отключения потока"));
  }
}

/*
 * Установка таймаута
 */
void ModuleThread::setTimeout(int timeoutValHi_, int timeoutValLo_) {
  timeoutValHi = timeoutValHi_;
  timeoutValLo = timeoutValLo_;
}

/*
 * Получение таймаута
 */
void ModuleThread::getTimeout(int *timeoutValHi_, int *timeoutValLo_) const {
  if(timeoutValHi_) {
    *timeoutValHi_ = timeoutValHi;
  }

  if(timeoutValLo_) {
    *timeoutValLo_ = timeoutValLo;
  }
}

/*
 * Проверка на наличие команд в списке команд
 */
bool ModuleThread::isCommandsListEmpty() const {
  if(commandsList.isEmpty()) {
    return true;
  }

  return false;
}

/*
 * Основное тело потока
 */
void ModuleThread::run() {

  while(isWorking()) {
    timeout = timeoutValHi;
    if(!commandsList.isEmpty()) {
      QUndoCommand* cmd = commandsList.first();
      cmd->redo();
      commandsList.removeAt(0);

      execBackgroundOperations();

      if(!commandsList.isEmpty()) {
        timeout = timeoutValLo;
      }
      else
      {
        timeout = timeoutValHi;
      }
    }
    else {
      execBackgroundOperations();
    }

    msleep( timeout );
  }

  /* terminated zone :)*/
  ;;;
}


