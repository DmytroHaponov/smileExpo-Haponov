/**
    displaythread.cpp
    Purpose: create a thread to which displaying process will be moved (it is thread 2)

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#include "displaythread.h"
//#include <QDebug>

DisplayThread::DisplayThread()
{
}

DisplayThread::~DisplayThread()
{
  this->quit();
}

void DisplayThread::run()
{
  //qDebug() << "thread 2 started";
          exec();
}

