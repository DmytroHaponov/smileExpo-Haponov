/**
    displaythread.h

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#ifndef DISPLAYTHREAD_H
#define DISPLAYTHREAD_H

#include <QThread> //thread for displaying

class DisplayThread : public QThread
{
  Q_OBJECT
public:
  DisplayThread();
  ~DisplayThread();
void run();       //thread function to override
};

#endif // DISPLAYTHREAD_H
