QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.3.0

INCLUDEPATH += $$PWD \
            ../include/libKitsuneCommon

SOURCES += \
    testing/test.cpp \
    threading/thread.cpp \
    statemachine/statemachine.cpp \
    buffering/data_buffer_methods.cpp \
    data_structure/data_items.cpp

HEADERS += \
    ../include/libKitsuneCommon/buffering/data_buffer.h \
    ../include/libKitsuneCommon/buffering/data_buffer_methods.h \
    ../include/libKitsuneCommon/commonMethods/string_methods.h \
    ../include/libKitsuneCommon/commonMethods/vector_methods.h \
    ../include/libKitsuneCommon/data_structure/data_items.h \
    ../include/libKitsuneCommon/statemachine/statemachine.h \
    ../include/libKitsuneCommon/testing/test.h \
    ../include/libKitsuneCommon/threading/thread.h \
    statemachine/state.h
