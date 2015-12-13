/**
    dialog.h

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include <QtGui>
#include "physprocessthread.h"
#include "displaythread.h"
#include "gatefordisplay.h"

namespace Ui {
  class Dialog;
}

class Dialog : public QDialog     //base window, calls window for displaying
{
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();
public slots:
  void repaint();                 //updating display view
  void msgForCannotOpen();        //creating message for user about failure to open file
  void msgForCannotWrite();       //creating message for user about failure to write to file
  void msgForCorruptCoord();      //creating message for user about corrupt coordidates in file
  void msgForCorruptDirection();  //creating message for user about corrupt direction in file

private slots:
  void on_stopButton_clicked();
  void on_startButton_clicked();
  void on_exitButton_clicked();

private:
  Ui::Dialog *ui;
  QGraphicsScene scene, physScene;//a scene for display and for displaying interaction of 2 threads
  QGraphicsView view;             //a view for displaying interaction between threads
  PhysProcessThread process;      //thread for physical process
  DisplayThread display;          //thread for displaying
  GateForDisplay gate;            //object responsible for displaying

  int count;                      //emulating '\n' in physScene
};

#endif // DIALOG_H
