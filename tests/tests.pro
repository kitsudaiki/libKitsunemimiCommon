include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    commonDataBufferTest.h

SOURCES += \
    commonDataBufferTest.cpp \
    main.cpp
