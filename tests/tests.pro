include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsuneCommon

HEADERS += \
    buffering/commonDataBufferTest.h \
    commonMethods/stringMethodsTest.h \
    commonMethods/vectorMethodsTest.h

SOURCES += \
    buffering/commonDataBufferTest.cpp \
    main.cpp \
    commonMethods/stringMethodsTest.cpp \
    commonMethods/vectorMethodsTest.cpp
