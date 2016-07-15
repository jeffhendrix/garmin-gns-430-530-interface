QT       += core gui
QT       += widgets

TARGET = gnsRemote
TEMPLATE = app

LIBS += -lWS2_32

INCLUDEPATH	+= ../libCommon
INCLUDEPATH	+= ../gnsinterface
INCLUDEPATH	+= ../libGnsProxy


SOURCES += main.cpp\
           mainwindow.cpp \
           remoteproxy.cpp

HEADERS  += mainwindow.h \
            remoteproxy.h

HEADERS   += ../libCommon/thread.h
HEADERS   += ../libCommon/udpsocket.h
HEADERS   += ../libCommon/udpsocketthread.h

SOURCES   += ../libCommon/udpsocket.cpp
SOURCES   += ../libCommon/udpsocketthread.cpp
SOURCES   += ../libCommon/thread.cpp

FORMS    += mainwindow.ui

