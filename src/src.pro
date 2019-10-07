QT       -= qt core gui

TARGET = KitsuneCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.5.4

INCLUDEPATH += $$PWD \
            ../include

SOURCES += \
    threading/thread.cpp \
    statemachine/statemachine.cpp \
    buffering/data_buffer_methods.cpp \
    common_items/data_items.cpp \
    common_items/table_item.cpp \
    testing/unit_test.cpp

HEADERS += \
    ../include/libKitsuneCommon/buffering/data_buffer.h \
    ../include/libKitsuneCommon/buffering/data_buffer_methods.h \
    ../include/libKitsuneCommon/common_methods/string_methods.h \
    ../include/libKitsuneCommon/common_methods/vector_methods.h \
    ../include/libKitsuneCommon/common_items/data_items.h \
    ../include/libKitsuneCommon/statemachine/statemachine.h \
    ../include/libKitsuneCommon/threading/thread.h \
    statemachine/state.h \
    ../include/libKitsuneCommon/common_items/table_item.h \
    ../include/libKitsuneCommon/testing/unit_test.h
