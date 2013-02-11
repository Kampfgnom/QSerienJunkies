QSERIENJUNKIES_PATH = ..
include($$QSERIENJUNKIES_PATH/QSerienJunkies.pri)

### General config ###

TARGET          = $$QSERIENJUNKIES_TARGET
VERSION         = $$QSERIENJUNKIES_VERSION
TEMPLATE        = lib
QT              += network xml
QT              -= gui
CONFIG          += staticlib c++11
QMAKE_CXXFLAGS  += -Wall -ansi -pedantic -Wno-long-long
INCLUDEPATH     += $$QSERIENJUNKIES_INCLUDEPATH


### Files ###

HEADERS += \
    qserienjunkies.h \
    qserienjunkiesreply.h

SOURCES += \
    qserienjunkies.cpp \
    qserienjunkiesreply.cpp
