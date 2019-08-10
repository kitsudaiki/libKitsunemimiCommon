QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.1.0

INCLUDEPATH += $$PWD \
            ../include/libKitsuneCommon

SOURCES += \
    buffering/dataBufferMethods.cpp \
    testing/test.cpp \
    threading/thread.cpp \
    statemachine/statemachine.cpp

HEADERS += \
    ../include/libKitsuneCommon/commonMethods/stringMethods.hpp \
    ../include/libKitsuneCommon/commonMethods/vectorMethods.hpp \
    ../include/libKitsuneCommon/buffering/dataBuffer.hpp \
    ../include/libKitsuneCommon/buffering/dataBufferMethods.hpp \
    ../include/libKitsuneCommon/testing/test.hpp \
    ../include/libKitsuneCommon/threading/thread.hpp \
    statemachine/state.hpp \
    ../include/libKitsuneCommon/statemachine/statemachine.hpp
