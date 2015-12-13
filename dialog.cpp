/**
    dialog.cpp
    Purpose: display 2 windows: main window with physical process being emulated + window with displaying

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);
  //set main window to be frameless
  setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

  //configure scene for displayThread
  scene.setSceneRect(0, 0, 300, 300);
  scene.addItem(&gate);
  view.setScene(&scene);

  //configure scene for displaying interaction between phisProcess and gateForDisplay
  count = 0; //imitating '\n' for adding text in physScene
  ui->graphicsView->setScene(&physScene);

  //connecting thread2 with thread1
  QObject::connect(&process, SIGNAL(showCoord(int)), &gate, SLOT(getCoord(int)));

  //updating view of displaying
  connect(&gate, SIGNAL(requestForPaint()), this, SLOT(repaint()));

  //==============connections for error messages from threads
  //create messageWindow if file cannot be opened
  connect(&process, SIGNAL(cannotOpen()), this, SLOT(msgForCannotOpen()));
  //create messageWindow if file cannot be written
  connect(&process, SIGNAL(cannotWrite()), this, SLOT(msgForCannotWrite()));
  //create messageWindow if file had corrupt coordinates
  connect(&process, SIGNAL(corruptCoord()), this, SLOT(msgForCorruptCoord()));
  //create messageWindow if file had corrupt direction
  connect(&process, SIGNAL(corruptDirection()), this, SLOT(msgForCorruptDirection()));

 //================launch the threads
  //launch thread2
  display.start();
  //move displaying to thread2
  gate.moveToThread(&display);
  //launch thread1 - physical process emulation
  process.start();
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::repaint()
{
  //updating display
  view.show();
  scene.update();

  //updating display of interaction between phisProcess and gateForDisplay
  count+=15;
  QGraphicsTextItem * io = new QGraphicsTextItem;
  io->setPos(10,count);
  io->setPlainText("coordinate to send" + QString::number(process.y));
  count+=10;
  QGraphicsTextItem * io1 = new QGraphicsTextItem;
  io1->setPos(10,count);
  io1->setPlainText("coordinate to receive" + QString::number(gate.y));
  physScene.addItem(io);
  physScene.addItem(io1);
}

void Dialog::msgForCannotOpen()
{
  QMessageBox boxNoFile; boxNoFile.setText("could not open db file,"
                                           " coordinate was initialized with 0"); boxNoFile.exec();
}

void Dialog::msgForCannotWrite()
{
  QMessageBox boxCannotWrite; boxCannotWrite.setText("can't write to db file"); boxCannotWrite.exec();
}

void Dialog::msgForCorruptCoord()
{
  QMessageBox box1; box1.setText("file had corrupt coordinate, replaced with 0"); box1.exec();
}

void Dialog::msgForCorruptDirection()
{
  QMessageBox box2; box2.setText("file had corrupt direction, replaced with down"); box2.exec();
}

void Dialog::on_stopButton_clicked()
{
  //stopping both threads + writing to db file
  process.Go = 0;
  process.write();
  process.exit();
  display.exit();
}

void Dialog::on_startButton_clicked()
{
  //starting both threads
  display.start();
  process.Go = 1;
  process.start();
}

void Dialog::on_exitButton_clicked()
{
  //exiting application
  process.Go = 0;
  process.write();
  process.exit();
  display.exit();
  exit(0);
}
