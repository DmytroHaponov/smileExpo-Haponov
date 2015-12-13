/**
    physprocessthread.h

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#ifndef PHYSPROCESSTHREAD_H
#define PHYSPROCESSTHREAD_H

#include <QThread>

class PhysProcessThread : public QThread   //thread of physical process calculation
{
  Q_OBJECT
public:
  PhysProcessThread();
  ~PhysProcessThread();
  void run();             //thread function to override
  int y;                  //y coordinate for the ball
  bool down;              //direction (up or down)
  int takeCoord();        //part of constructor, used to initiaze 'y'(coordinates) from file
  bool Go;                //to end calculating of coordinates for ball
  void write();           //saving 'y' (coordinates) to file
signals:
  int showCoord(int);     //sending coordinates to thread2
  void cannotOpen();      //requesting main thread to create a window for cannot open file error
  void cannotWrite();     //requesting main thread to create a window for cannot write to file error
  void corruptCoord();    //requesting main thread to create a window for corrupt coordinates in file error
  void corruptDirection();//requesting main thread to create a window for corrupt direction in file error
};

#endif // PHYSPROCESSTHREAD_H
