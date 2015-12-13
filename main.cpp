/**
    main.cpp
    Purpose: launch execution of program

    @author Dmytro Haponov
    @version 2.1 13/12/15
*/

#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Dialog w;
  w.show();

  return a.exec();
}
