/**
    physprocessthread.cpp
    Purpose: emulate ball jumping (it is thread 1)

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#include "physprocessthread.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>

using namespace std;

PhysProcessThread::PhysProcessThread()
{
  Go = 1;
}

PhysProcessThread::~PhysProcessThread()
{
  this->quit();
}

void PhysProcessThread::run()
{
    // qDebug()<<"thread 1 started";
  y = takeCoord();
  if(y>250 || y<0) {y=0; emit corruptCoord();}
  if(down!=0 && down!=1) {down=1;  emit corruptDirection();}
  while(Go)
    {
      if(down) {y+=5; /* qDebug()<<" down"<<endl; */ if(y>=250) down=0;}
      else {y-=5; /* qDebug()<<" up"<<endl; */ if(y<10) down=1;}

      emit showCoord(y);
      // qDebug()<<y<<" emmited";
      msleep(50);
    }
}

int PhysProcessThread::takeCoord()
{
  QString path = QDir::currentPath();
  QFile file(path + "/initial.txt");
  //-------------------------------------------------------------------
  try
  {
    if(!file.open(QFile::ReadOnly))
      {
        throw "ERROR - cannot open file!!";
      }
  }
  catch(const char *p)
  {
    //qDebug()<<"file could not be opened";
    emit cannotOpen();
    return 0;
  }
  //-------------------------------------------------------------------
  int temp=0;
  QTextStream in(&file);
  QString str = in.readLine();
  temp = str.toInt();
  str = in.readLine();
  down = str.toInt();
  file.close();
  return temp;
}

void PhysProcessThread::write()
{
  QString path = QDir::currentPath();
  QFile file(path + "/initial.txt");
  //-------------------------------------------------------------------
  try
  {
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
      {
        throw "ERROR - cannot write to file";
      }
  }
  catch(const char *p)
  {
    //qDebug()<<"could not write to file!";
    emit cannotWrite();
    return;
  }
  //-------------------------------------------------------------------
  QTextStream stream(&file);
  stream <<y<<'\n'<<down;
  file.close();
}

