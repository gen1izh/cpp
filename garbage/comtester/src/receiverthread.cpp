// ---------------------------------------------------------------------------

#pragma hdrstop

#include "receiverthread.h"
#include "ftdiapiwrapper.h"
#include "testcomport.h"
#include "datamodel.h"
#include <vcl.h>


#define SLEEP_DELAY 100
// ---------------------------------------------------------------------------

  /**
   * Body receiver thread
   */
DWORD __stdcall thread_body(LPVOID) {

  char    RxBuffer[256];
  int     data;
  int     iter = 0;

  while (true) {
    iter++;
  /**
   *  Receive 4 bytes by COM port
   */
    dev->device_read((char*) & RxBuffer[0], 2);

  /**
   *  Collect data to int
   */
    data = (int)( (int)(( 0xff & RxBuffer[0] ) << 8) |
                         (int)(0xff & RxBuffer[1]));


    point *np = new point();

    np->x         = (SLEEP_DELAY / 1000) * (double)iter;
    np->y         = (double)data;
    np->i         = (int)iter;
    np->draw_flag = false;

    dl_store(np);

    Sleep( SLEEP_DELAY );

    if ( thr->_isSuspend ) {
      WaitForSingleObject( thr->_Event, INFINITE);
    }

    if ( thr->_isExitThread ) {
      ExitThread(0);
    }

  }
}

/**
  *  Suspend thread
  */
int ThreadAdapter::_suspend() {
  _isSuspend = true;
  return 0;
}

/**
  *  Resume thread
  */
void ThreadAdapter::_resume() {
  _isSuspend = false;
  SetEvent(thr->_Event);
}

/**
  *  Exit thread
  */
void ThreadAdapter::_exit() {
  _isExitThread = true;
}

/**
  *  Create thread
  */
void ThreadAdapter::_create() {
  _isSuspend      = false;
  _isExitThread   = false;
  _HDL            = CreateThread(NULL, NULL, thread_body, NULL, NULL, &_ID);
  thr->_Event     = CreateEvent(NULL, false, false, NULL);
}

/**
  *  Initialize thread  state
  */
ThreadAdapter::ThreadAdapter() {
  _isSuspend      = false;
  _isExitThread   = false;
  _HDL            = CreateThread(NULL, NULL, thread_body, NULL, NULL, &_ID);
  thr->_Event     = CreateEvent(NULL, false, false, NULL);
}

/**
  *  Destroy thread
  */
ThreadAdapter::~ThreadAdapter() {
  CloseHandle(thr->_Event);
  if ( _HDL ) {
    TerminateThread( _HDL, 0 );
    CloseHandle( _HDL );
  }
}
#pragma package(smart_init)
