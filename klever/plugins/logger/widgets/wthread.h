#ifndef WTHREAD_H
#define WTHREAD_H

#include <QThread>

class WThread : public QThread
{

    Q_OBJECT

public:
    WThread();

    void run();
};

#endif // WTHREAD_H
