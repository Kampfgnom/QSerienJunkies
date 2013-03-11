### General config ###

TARGET          = QSerienJunkiesExample
VERSION         = 0.0.0
TEMPLATE        = app
QT              += network xml widgets
QT              -=
CONFIG          += c++11
QMAKE_CXXFLAGS  += -Wall -ansi -pedantic -Wno-long-long

### QSERIENJUNKIES ###

QSERIENJUNKIES_PATH = ..
include($$QSERIENJUNKIES_PATH/QSerienJunkies.pri)
LIBS            += $$QSERIENJUNKIES_LIBS
INCLUDEPATH     += $$QSERIENJUNKIES_INCLUDEPATH


### Files ###

HEADERS += \
    captchadialog.h

SOURCES += \
    main.cpp \
    captchadialog.cpp

FORMS += \
    captchadialog.ui
