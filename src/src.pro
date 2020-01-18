QT       -= qt core gui

TARGET = KitsunemimiCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.10.1

INCLUDEPATH += $$PWD \
            ../include

SOURCES += \
    threading/thread.cpp \
    statemachine.cpp \
    common_items/data_items.cpp \
    common_items/table_item.cpp \
    unit_test.cpp \
    threading/barrier.cpp \
    process_execution.cpp

HEADERS += \
    ../include/libKitsunemimiCommon/data_buffer.h \
    ../include/libKitsunemimiCommon/common_methods/string_methods.h \
    ../include/libKitsunemimiCommon/common_methods/vector_methods.h \
    ../include/libKitsunemimiCommon/common_items/data_items.h \
    ../include/libKitsunemimiCommon/statemachine.h \
    ../include/libKitsunemimiCommon/threading/thread.h \
    state.h \
    ../include/libKitsunemimiCommon/common_items/table_item.h \
    ../include/libKitsunemimiCommon/test.h \
    ../include/libKitsunemimiCommon/threading/barrier.h \
    ../include/libKitsunemimiCommon/process_execution.h
