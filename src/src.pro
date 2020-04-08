QT       -= qt core gui

TARGET = KitsunemimiCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.12.1

INCLUDEPATH += $$PWD \
            ../include

SOURCES += \
    threading/thread.cpp \
    statemachine.cpp \
    common_items/data_items.cpp \
    common_items/table_item.cpp \
    threading/barrier.cpp \
    process_execution.cpp \
    test_helper/compare_test_helper.cpp \
    test_helper/speed_test_helper.cpp \
    buffer/stack_buffer_reserve.cpp


HEADERS += \
    state.h \
    ../include/libKitsunemimiCommon/buffer/ring_buffer.h \
    ../include/libKitsunemimiCommon/common_methods/string_methods.h \
    ../include/libKitsunemimiCommon/common_methods/vector_methods.h \
    ../include/libKitsunemimiCommon/common_items/data_items.h \
    ../include/libKitsunemimiCommon/statemachine.h \
    ../include/libKitsunemimiCommon/threading/thread.h \
    ../include/libKitsunemimiCommon/common_items/table_item.h \
    ../include/libKitsunemimiCommon/threading/barrier.h \
    ../include/libKitsunemimiCommon/process_execution.h \
    ../include/libKitsunemimiCommon/test_helper/compare_test_helper.h \
    ../include/libKitsunemimiCommon/test_helper/speed_test_helper.h \
    ../include/libKitsunemimiCommon/buffer/data_buffer.h \
    ../include/libKitsunemimiCommon/buffer/stack_buffer.h \
    ../include/libKitsunemimiCommon/buffer/stack_buffer_reserve.h
