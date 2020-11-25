QT       -= qt core gui

TARGET = KitsunemimiCommon
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.16.0

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
    buffer/stack_buffer_reserve.cpp \
    common_methods/string_methods.cpp \
    common_methods/vector_methods.cpp \
    memory_counter.cpp \
    common_methods/object_methods.cpp \
    threading/event.cpp \
    threading/thread_handler.cpp \
    test_helper/memory_leak_test_helper.cpp \
    threading/cleanup_thread.cpp


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
    ../include/libKitsunemimiCommon/buffer/stack_buffer_reserve.h \
    ../include/libKitsunemimiCommon/memory_counter.h \
    ../include/libKitsunemimiCommon/common_methods/object_methods.h \
    ../include/libKitsunemimiCommon/threading/event.h \
    ../include/libKitsunemimiCommon/threading/thread_handler.h \
    ../include/libKitsunemimiCommon/test_helper/memory_leak_test_helper.h \
    ../include/libKitsunemimiCommon/threading/cleanup_thread.h
