QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++17
CONFIG += staticlib

INCLUDEPATH += $$PWD \
            ../include/libKitsuneCommon

SOURCES += \
    threading/commonThread.cpp \
    testing/commonTest.cpp \
    buffering/commonDataBufferMethods.cpp

HEADERS += \
    ../include/libKitsuneCommon/threading/commonThread.h \
    ../include/libKitsuneCommon/testing/commonTest.h \
    ../include/libKitsuneCommon/buffering/commonDataBuffer.h \
    ../include/libKitsuneCommon/buffering/commonDataBufferMethods.h
