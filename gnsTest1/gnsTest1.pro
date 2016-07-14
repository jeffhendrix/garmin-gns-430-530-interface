TARGET		 = gnsTest1
QT          += opengl
QT          += widgets

LIBS += -lopengl32
LIBS += -luser32
LIBS += -lWS2_32
LIBS += -lAdvAPI32

CFLAGS      -= UNICODE
DESTDIR     = $(SolutionDir)/bin/$(PlatformName)/$(ConfigurationName)
DEFINES		+= _CRT_SECURE_NO_WARNINGS
DEFINES     -= UNICODE

RESOURCES	+= gnsTest1.qrc
RC_FILE 	+= icon.rc

INCLUDEPATH	+= ../libCommon
INCLUDEPATH	+= ../gnsinterface
INCLUDEPATH	+= ../libGnsProxy


#HEADERS  += main.h
SOURCES	 += main.cpp

HEADERS   += gnsViewWidget.h
SOURCES   += gnsViewWidget.cpp

FORMS     += mainWindow.ui
SOURCES   += mainWindow.cpp
HEADERS   += mainWindow.h

# /libCommon
HEADERS   += ../libCommon/crcfile.h
HEADERS   += ../libCommon/injector.h
HEADERS   += ../libCommon/log.h
HEADERS   += ../libCommon/sharedstruct.h
HEADERS   += ../libCommon/thread.h
HEADERS   += ../libCommon/udpsocket.h
HEADERS   += ../libCommon/udpsocketthread.h

SOURCES   += ../libCommon/crcfile.cpp
SOURCES   += ../libCommon/injector.cpp
SOURCES   += ../libCommon/log.cpp
SOURCES   += ../libCommon/thread.cpp
SOURCES   += ../libCommon/udpsocket.cpp
SOURCES   += ../libCommon/udpsocketthread.cpp

# /libGnsProxy
HEADERS   += ../libGnsProxy/gnsx30proxy.h
SOURCES   += ../libGnsProxy/gnsx30proxy.cpp


