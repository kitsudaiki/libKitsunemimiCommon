QT       -= qt core gui

TARGET = KitsunemimiCommon
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
    ../include/libKitsunemimiCommon/data_buffer.h \
    ../include/libKitsunemimiCommon/data_buffer_methods.h \
    ../include/libKitsunemimiCommon/common_methods/string_methods.h \
    ../include/libKitsunemimiCommon/common_methods/vector_methods.h \
    ../include/libKitsunemimiCommon/common_items/data_items.h \
    ../include/libKitsunemimiCommon/statemachine.h \
    ../include/libKitsunemimiCommon/thread.h \
    state.h \
    ../include/libKitsunemimiCommon/common_items/table_item.h \
    ../include/libKitsunemimiCommon/test.h
