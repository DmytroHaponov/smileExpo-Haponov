#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T15:20:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smileExpo-Haponov
TEMPLATE = app


SOURCES += main.cpp\
    physprocessthread.cpp \
    displaythread.cpp \
    gatefordisplay.cpp \
    dialog.cpp

HEADERS  += \
    physprocessthread.h \
    displaythread.h \
    gatefordisplay.h \
    dialog.h

FORMS    += \
    dialog.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
