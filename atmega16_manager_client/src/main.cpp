
#include "at_manager_client.h"
#include "at_thread.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include "drv_uart/ftd2xx.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  AvrClientApp w;

  w.show();

  at_thread_state = at_idle_state;
  AtThread t_receiver;
  t_receiver.start();

  return a.exec();
}
