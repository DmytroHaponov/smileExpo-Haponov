/**
    gatefordisplay.cpp
    Purpose: display a ball according to coordinate that is received from physprocessthread.cpp

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#include "gatefordisplay.h"
//#include <QDebug>
#include <QPixmap>
#include <QMessageBox>

GateForDisplay::GateForDisplay()
{
}

QRectF GateForDisplay::boundingRect() const
{
  //not used in project, had to be implemented
  return QRectF(0, 0, 300, 300);
}

void GateForDisplay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  //===============displaying a ball jumping between 2 lines
  point.setX(125);
  point.setY(y);
  try
  {
    if (!pixmap.load("://pic//ball.jpg")) throw 404;
  }
  catch (int)
  {
    QMessageBox box;
    box.setText("no picture to display found");
    box.exec();
    // qDebug()<<error<<" no picture";
  }
  //2 lines just for ikebana
  painter->drawLine(100,4,200,4);
  painter->drawLine(100,295,200,295);
  painter->drawPixmap(point, pixmap);
}

void GateForDisplay::getCoord(int received)
{
  //receiving coordinates from thread 1
  y = received;
  // qDebug()<<y<<" received";
  emit requestForPaint();
}

