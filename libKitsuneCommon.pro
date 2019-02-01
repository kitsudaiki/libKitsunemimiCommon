QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++14
CONFIG += staticlib

INCLUDEPATH += $$PWD \
            include/libKitsuneCommon

SOURCES += \
    src/commonThread.cpp \
    src/commonTest.cpp \
    src/commonDataBuffer.cpp

HEADERS += \
    include/libKitsuneCommon/commonThread.h \
    include/libKitsuneCommon/commonTest.h \
    include/libKitsuneCommon/commonDataBuffer.h
