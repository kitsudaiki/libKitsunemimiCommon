#-------------------------------------------------
#
# Project created by QtCreator 2018-02-20T22:14:16
#
#-------------------------------------------------

QT       -= gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++17

INCLUDEPATH += $$PWD \
            include/libKitsuneCommon

DEFINES += LIBCRYPTO_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/commonThread.cpp \
    src/commonTest.cpp \
    src/commonDataBuffer.cpp

HEADERS += \
    include/libKitsuneCommon/commonThread.h \
    include/libKitsuneCommon/commonTest.h \
    include/libKitsuneCommon/commonDataBuffer.h
