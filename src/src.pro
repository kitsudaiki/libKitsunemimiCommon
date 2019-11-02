QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.6.0

INCLUDEPATH += $$PWD \
            ../include

SOURCES += \
    thread.cpp \
    statemachine.cpp \
    data_buffer_methods.cpp \
    common_items/data_items.cpp \
    common_items/table_item.cpp \
    unit_test.cpp

HEADERS += \
    ../include/libKitsuneCommon/data_buffer.h \
    ../include/libKitsuneCommon/data_buffer_methods.h \
    ../include/libKitsuneCommon/common_methods/string_methods.h \
    ../include/libKitsuneCommon/common_methods/vector_methods.h \
    ../include/libKitsuneCommon/common_items/data_items.h \
    ../include/libKitsuneCommon/statemachine.h \
    ../include/libKitsuneCommon/thread.h \
    state.h \
    ../include/libKitsuneCommon/common_items/table_item.h \
    ../include/libKitsuneCommon/test.h
