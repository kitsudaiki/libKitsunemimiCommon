QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.1.0

INCLUDEPATH += $$PWD \
            ../include/libKitsuneCommon

SOURCES += \
    threading/commonThread.cpp \
    testing/commonTest.cpp \
    buffering/commonDataBufferMethods.cpp

HEADERS += \
    ../include/libKitsuneCommon/buffering/commonDataBuffer.hpp \
    ../include/libKitsuneCommon/buffering/commonDataBufferMethods.hpp \
    ../include/libKitsuneCommon/commonMethods/stringMethods.hpp \
    ../include/libKitsuneCommon/commonMethods/vectorMethods.hpp \
    ../include/libKitsuneCommon/testing/commonTest.hpp \
    ../include/libKitsuneCommon/threading/commonThread.hpp
