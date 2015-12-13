/**
    gatefordisplay.h

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#ifndef GATEFORDISPLAY_H
#define GATEFORDISPLAY_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class GateForDisplay : public QObject, public QGraphicsItem    //displaying code
{
  Q_OBJECT
public:
  GateForDisplay();
  QRectF boundingRect() const;    //mandatory to implement, not used
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  int y;                          //coordinate of ball
  QPoint point;                   //coordinate for drawing a pixmap
  QPixmap pixmap;                 //image of ball
signals:
  void requestForPaint();         //request for updating view
public slots:
    void getCoord(int received);  //receiving coordinates from thread1
};

#endif // GATEFORDISPLAY_H
