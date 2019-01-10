#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T22:14:16
#
#-------------------------------------------------

QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++17

INCLUDEPATH += $$PWD \
            include/libKitsuneCommon

DEFINES += LIBCRYPTO_LIBRARY

SOURCES += \
    src/commonThread.cpp \
    src/commonTest.cpp \
    src/commonDataBuffer.cpp

HEADERS += \
    include/libKitsuneCommon/commonThread.h \
    include/libKitsuneCommon/commonTest.h \
    include/libKitsuneCommon/commonDataBuffer.h
