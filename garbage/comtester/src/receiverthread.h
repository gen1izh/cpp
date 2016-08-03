// ---------------------------------------------------------------------------

#ifndef receiverthreadH
#define receiverthreadH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include "datamodel.h"


class ThreadAdapter {
public:
  HANDLE  _HDL;
  DWORD   _ID;
  bool    _isSuspend;
  bool    _isExitThread;
  HANDLE  _Event;

  int     _suspend();
  void    _resume();
  void    _exit();
  void    _create();

  ThreadAdapter();
  ~ThreadAdapter();
};
#endif
